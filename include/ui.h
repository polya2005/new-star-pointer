/**
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */

#ifndef UI_H_
#define UI_H_

#include <lvgl.h>

void setup_screen();
/**
 * @brief Populates the Identify tab with a button matrix for jogging controls.
 *
 * @param tab_identify
 * @return lv_obj_t* The pointer to the button matrix object.
 */
lv_obj_t* populate_tab_identify(lv_obj_t* tab_identify,
                                lv_event_cb_t event_handler);

/**
 * @brief Creates a screen displaying a star's information.
 *
 * This function creates a screen that displays detailed information about a
 * star, including its name, right ascension, declination, magnitude, spectral
 * type, constellation, and B-V color index. It also includes a button to return
 * to the previous screen.
 *
 * @param star_index The index of the star in the database.
 *
 * @return lv_obj_t* A pointer to the created screen object.
 */
lv_obj_t* create_star_info_screen(int16_t star_index,
                                  lv_event_cb_t ok_button_cb);

#endif  // UI_H_
