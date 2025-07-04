/**
 * Copyright (c) 2025, Boonyakorn Thanpanit
 */

#include <StarDatabase.h>
#include <lvgl.h>
#include <stdio.h>

#include "ui.h"

const char* make_ra_string(double ra) {
  // Convert right ascension from radians to hours
  double hours = ra * 12.0 / PI;
  int h = static_cast<int>(hours);
  int m = static_cast<int>((hours - h) * 60);
  double s = ((hours - h) * 60 - m) * 60;

  static char ra_string[17];
  snprintf(ra_string, sizeof(ra_string), "%02dʰ%02dᵐ%4.1fˢ", h, m, s);
  return ra_string;
}

const char* make_dec_string(double dec) {
  // Convert declination from radians to degrees
  double degrees = dec * 180.0 / PI;
  char sign;
  if (degrees < 0) {
    sign = '-';
    degrees = -degrees;  // Make it positive for formatting
  } else {
    sign = '+';
  }
  int d = static_cast<int>(degrees);
  int m = static_cast<int>((degrees - d) * 60);
  int s = static_cast<int>(((degrees - d) * 60 - m) * 60);

  static char dec_string[12];
  snprintf(dec_string, sizeof(dec_string), "%c%02d°%02d'%02d\"", sign, d, m, s);
  return dec_string;
}

lv_obj_t* create_star_info_screen(int16_t star_index,
                                  lv_event_cb_t ok_button_cb) {
  StarDatabase& star_database = StarDatabase::GetInstance();
  StarDatabaseEntry star_entry = star_database.ReadStarEntry(star_index);

  // Create a new screen for displaying star information
  lv_obj_t* screen = lv_obj_create(NULL);
  lv_obj_set_layout(screen, LV_LAYOUT_FLEX);
  lv_obj_set_size(screen, LV_PCT(100), LV_PCT(100));
  lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(screen, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_SPACE_AROUND);

  // Create a label for the star name
  lv_obj_t* title = lv_label_create(screen);
  lv_label_set_text(title, star_entry.name);

  // Create a table for displaying star information
  lv_obj_t* table = lv_table_create(screen);
  lv_table_set_column_count(table, 2);
  lv_obj_set_style_text_font(table, &notosans_12, LV_PART_ITEMS);
  lv_obj_set_style_pad_all(table, 4, LV_PART_ITEMS);

  lv_table_set_cell_value(table, 0, 0, "Other Names");
  lv_table_set_cell_value(table, 0, 1, star_entry.other_names);

  lv_table_set_cell_value(table, 1, 0, "Constellation");
  lv_table_set_cell_value(table, 1, 1, star_entry.constellation);

  lv_table_set_cell_value(table, 2, 0, "Right Ascension");
  lv_table_set_cell_value(table, 2, 1, make_ra_string(star_entry.ra));

  lv_table_set_cell_value(table, 3, 0, "Declination");
  lv_table_set_cell_value(table, 3, 1, make_dec_string(star_entry.dec));

  lv_table_set_cell_value(table, 4, 0, "Magnitude");
  char mag_str[6];
  snprintf(mag_str, sizeof(mag_str), "%.2f", star_entry.mag);
  lv_table_set_cell_value(table, 4, 1, mag_str);

  lv_table_set_cell_value(table, 5, 0, "Spectral Type");
  lv_table_set_cell_value(table, 5, 1, star_entry.spectral_type);

  lv_table_set_cell_value(table, 6, 0, "B-V Color Index");
  char bv_str[6];
  snprintf(bv_str, sizeof(bv_str), "%.2f", star_entry.b_v);
  lv_table_set_cell_value(table, 6, 1, bv_str);

  lv_obj_t* ok_button = lv_button_create(screen);
  lv_obj_t* ok_button_label = lv_label_create(ok_button);
  lv_label_set_text(ok_button_label, "OK");
  lv_obj_add_event_cb(ok_button, ok_button_cb, LV_EVENT_CLICKED, NULL);

  return screen;
}
