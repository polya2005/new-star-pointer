/*
 * Copyright (c) 2025 Boonyakorn Thanpanit
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define DEBUG

#include <Arduino.h>
#include <MovementController.h>
#include <TempDebug.h>
#include <Wire.h>
#include <lvgl.h>

#include "ui.h"

MovementController& movementController = MovementController::GetInstance();

void setup_movement() {
  movementController.AttachAzimuthMotor(10, 11, 4000 / TWO_PI);
  movementController.AttachAltitudeMotor(12, 13, 4000 / TWO_PI);
}

void btnm_jog_value_changed_handler(lv_event_t* e) {
  lv_obj_t* btnm = reinterpret_cast<lv_obj_t*>(lv_event_get_target(e));
  int32_t id = lv_buttonmatrix_get_selected_button(btnm);

  switch (id) {
    case 1:  // Up
      movementController.JogUp();
      break;
    case 3:  // Left
      movementController.JogEast();
      break;
    case 4:  // OK
      // Implement OK action if needed
      debugln("OK button pressed");
      break;
    case 5:  // Right
      movementController.JogWest();
      break;
    case 7:  // Down
      movementController.JogDown();
      break;
    default:
      break;
  }
}

void setup(void) {
  Serial.begin(9600);
  delay(1000);  // delay for the serial monitor to open
  setup_movement();

  setup_screen();
  lv_obj_t* tabview = lv_tabview_create(lv_screen_active());
  lv_obj_t* tab_goto = lv_tabview_add_tab(tabview, "Goto");
  lv_obj_t* tab_identify = lv_tabview_add_tab(tabview, "Identify");

  populate_tab_identify(tab_identify, btnm_jog_value_changed_handler);
}

void loop(void) {
  lv_task_handler();
  movementController.Run();
  lv_tick_inc(5);
  delay(5);
}
