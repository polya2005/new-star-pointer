/**
 * Copyright (c) 2025 Boonyakorn Thanpanit
 */
#include <lvgl.h>

#include "ui.h"

lv_obj_t* populate_tab_identify(lv_obj_t* tab_identify,
                                lv_event_cb_t event_handler) {
  lv_obj_remove_flag(tab_identify, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_t* btnm_jog = lv_buttonmatrix_create(tab_identify);
  static const char* btnm_map[] = {" ",
                                   LV_SYMBOL_UP,
                                   " ",
                                   "\n",
                                   LV_SYMBOL_LEFT,
                                   "OK",
                                   LV_SYMBOL_RIGHT,
                                   "\n",
                                   " ",
                                   LV_SYMBOL_DOWN,
                                   " ",
                                   ""};
  lv_buttonmatrix_set_map(btnm_jog, btnm_map);
  lv_buttonmatrix_set_button_ctrl(btnm_jog, 0, LV_BUTTONMATRIX_CTRL_HIDDEN);
  lv_buttonmatrix_set_button_ctrl(btnm_jog, 2, LV_BUTTONMATRIX_CTRL_HIDDEN);
  lv_buttonmatrix_set_button_ctrl(btnm_jog, 6, LV_BUTTONMATRIX_CTRL_HIDDEN);
  lv_buttonmatrix_set_button_ctrl(btnm_jog, 8, LV_BUTTONMATRIX_CTRL_HIDDEN);

  lv_obj_set_size(btnm_jog, 150, 150);
  lv_obj_align(btnm_jog, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_bg_opa(btnm_jog, LV_OPA_TRANSP, LV_PART_MAIN);
  lv_obj_set_style_border_width(btnm_jog, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_all(btnm_jog, 0, LV_PART_MAIN);

  lv_obj_add_event_cb(btnm_jog, event_handler, LV_EVENT_VALUE_CHANGED, NULL);

  return btnm_jog;
}
