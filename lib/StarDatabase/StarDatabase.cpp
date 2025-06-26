/**
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#include "StarDatabase.h"

#include <LittleFS.h>
#include <TempDebug.h>
#include <math.h>

#include <algorithm>

StarDatabase& StarDatabase::GetInstance() {
  static StarDatabase instance;  // Guaranteed to be destroyed.
  return instance;               // Instantiated on first use.
}

void StarDatabase::Init() {
  if (!LittleFS.begin()) {
    debugln(F("Failed to mount LittleFS"));
    while (true) continue;  // Halt the program if LittleFS fails to mount
  }
  File ball_tree_file = LittleFS.open(kBallTreeFileName_, "rb");
  if (!ball_tree_file) {
    debugln(F("Failed to open ball tree file"));
    while (true) continue;  // Halt the program if the file cannot be opened
  }
  ball_tree_file.seek(1, SeekEnd);
  if (ball_tree_file.read(reinterpret_cast<uint8_t*>(&ball_root_),
                          sizeof(ball_root_)) != sizeof(ball_root_)) {
    debugln(F("Failed to read ball tree root index"));
    while (true) continue;  // Halt the program if reading fails
  }
}

void StarDatabase::BallTreeSearch(File ball_tree_file, int16_t node_index,
                                  const Vector3& query) {
  BallNode node = ReadAtRecord<BallNode>(ball_tree_file, node_index);
  if (node.index == 0 && node.left == 0 && node.right == 0) {
    // Fail to read file
    debugln(F("Failed to read ball tree node"));
    return;
  }
  double sim = node.center.Dot(query);

  if (node.is_leaf) {
    if (sim > ball_best_sim_) {
      ball_best_sim_ = sim;
      ball_best_index_ = node.index;
    }
    return;
  }

  double angle = acos(std::clamp(sim, -1.0, 1.0));
  if (angle > node.radius && sim < ball_best_sim_) return;

  double sim_left =
      ReadAtRecord<BallNode>(ball_tree_file, node.left).center.Dot(query);
  double sim_right =
      ReadAtRecord<BallNode>(ball_tree_file, node.right).center.Dot(query);

  if (sim_left > sim_right) {
    BallTreeSearch(ball_tree_file, node.left, query);
    BallTreeSearch(ball_tree_file, node.right, query);
  } else {
    BallTreeSearch(ball_tree_file, node.right, query);
    BallTreeSearch(ball_tree_file, node.left, query);
  }
}

int16_t StarDatabase::SearchByPosition(double ra, double dec) {
  File ball_tree_file = LittleFS.open(kBallTreeFileName_, "rb");
  if (!ball_tree_file) {
    debugln(F("Failed to open ball tree file"));
    return STARDATABASE_FAIL_TO_OPEN_FILE;
  }
  Vector3 query = Vector3(cos(dec) * cos(ra), cos(dec) * sin(ra), sin(dec));
  ball_best_index_ = -1;
  ball_best_sim_ = -2.0;
  BallTreeSearch(ball_tree_file, ball_root_, query);
  return ball_best_index_ >= 0 ? ball_best_index_
                               : STARDATABASE_FAIL_TO_READ_FILE;
}
