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

#endif  // UI_H_
