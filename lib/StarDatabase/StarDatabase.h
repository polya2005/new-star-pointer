/**
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef LIB_STARDATABASE_STARDATABASE_H_
#define LIB_STARDATABASE_STARDATABASE_H_

#include <LittleFS.h>
#include <TempDebug.h>
#include <Vectors.h>
#include <stdint.h>

#define STARDATABASE_FAIL_TO_OPEN_FILE -1
#define STARDATABASE_FAIL_TO_READ_FILE -2

struct StarDatabaseEntry {
  uint8_t n_names;  // Number of names (up to 5)
  char names[5]
            [23];  // Names of the star, up to 5 names, each up to 22 characters
  char constellation[20];  // Constellation name, up to 19 characters
  double ra;               // Right Ascension in radians
  double dec;              // Declination in radians
  float mag;               // Magnitude of the star
  char spectral_type[18];
  float b_v;  // B-V color index
};

/**
 * @brief A class that provides access to a database of stars.
 *
 * The class provides functions to search for stars by name, right ascension,
 * and declination. It uses a ball tree data structure to efficiently search for
 * stars within a certain radius, and it uses a trie data structure to search
 * for stars by name.
 *
 * The database is stored on the flash memory of the device as binary files:
 * - `db.bin`: Contains the star database entries.
 * - `ball_tree.bin`: Contains the ball tree nodes.
 *
 * The class is a singleton class.
 */
class StarDatabase {
 private:
  StarDatabase() {}
  StarDatabase(const StarDatabase& other) = delete;
  void operator=(const StarDatabase& other) = delete;

  const char* kStarsFileName_ = "/db.bin";  // File name for the star database
  const char* kBallTreeFileName_ =
      "/ball_tree.bin";  // File name for the ball tree

  int16_t ball_best_index_ = -1;
  double ball_best_sim_ = -2.0;
  int16_t ball_root_ = -1;  // Root index of the ball tree

  void BallTreeSearch(File& ball_tree_file, int16_t node_index,
                      const Vector3& query);

  struct BallNode {
    Vector3 center;                 // Center of the ball
    double radius;                  // Radius of the ball
    int16_t left = -1, right = -1;  // Indices of left and right child nodes
    int16_t index = -1;  // Index of the star in the database (for leaf nodes)
    uint8_t is_leaf = false;  // True if this node is a leaf node
    void print() const {
      debugln(F("BallNode:"));
      debug(F("  Center: "));
      debug(center.x);
      debug(F(", "));
      debug(center.y);
      debug(F(", "));
      debugln(center.z);
      debug(F("  Radius: "));
      debugln(radius);
      debug(F("  Left: "));
      debugln(left);
      debug(F("  Right: "));
      debugln(right);
      debug(F("  Index: "));
      debugln(index);
      debug(F("  Is Leaf: "));
      debugln(is_leaf);
    }
  };

  template <typename T>
  static T ReadAtRecord(File& file, int16_t index) {
    T record;
    const size_t record_position =
        static_cast<size_t>(index) * sizeof(record);
    file.seek(record_position, SeekSet);  // Move to the record position
    if (file.read(reinterpret_cast<uint8_t*>(&record), sizeof(T)) !=
        sizeof(T)) {
      debugln(F("Failed to read record from file"));
      return T();  // Return default value if read fails
    }
    return record;
  }

 public:
  /**
   * @brief Gets the singleton instance of the StarDatabase class.
   *
   * This function returns a reference to the singleton instance of the
   * StarDatabase class. If the instance has not been created yet, it will be
   * created on the first call to this function.
   *
   * @return StarDatabase& A reference to the singleton instance of the
   * StarDatabase class.
   */
  static StarDatabase& GetInstance();

  /**
   * @brief Initializes the star database.
   *
   */
  void Init();

  /**
   * @brief Searches for a star by its position in the sky.
   *
   * @param ra Right Ascension of the star in radians.
   * @param dec Declination of the star in radians.
   *
   * @return int16_t The index of the closest star in the database or a negative
   * error code.
   */
  int16_t SearchByPosition(double ra, double dec);

};

#endif  // LIB_STARDATABASE_STARDATABASE_H_
