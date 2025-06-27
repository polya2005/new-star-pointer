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

#include <Arduino.h>
#include <AstroCalculator.h>
#include <Datatypes.h>
#include <MovementController.h>
#include <Sensors.h>
#include <StarDatabase.h>
#include <TempDebug.h>
#include <Wire.h>
#include <lvgl.h>

#include "ui.h"

AstroCalculator& astroCalculator = AstroCalculator::GetInstance();
MovementController& movementController = MovementController::GetInstance();
Sensors& sensors = Sensors::GetInstance();
StarDatabase& starDatabase = StarDatabase::GetInstance();

void setup_movement() {
  movementController.AttachAzimuthMotor(10, 11, 4000 / TWO_PI);
  movementController.AttachAltitudeMotor(12, 13, 4000 / TWO_PI);
  movementController.SetJogStepAngle(0.1 * PI / 180);
  // TODO(polya2005): Home the motors such that the pointer points eastward
  movementController.SetCurrentPosition(HALF_PI, 0);
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
#ifdef DEBUG
  Serial.begin(115200);
  delay(1000);  // delay for the serial monitor to open
#endif
  // sensors.Init();
  // ObserverLocation observer_location = sensors.ReadObserverLocation();
  // astroCalculator.SetObserverLocation(observer_location.latitude,
  //                                     observer_location.longitude);
  // setup_movement();
  debugln("Starting StarPointer Pico...");
  starDatabase.Init();

  // setup user interface
  setup_screen();
  lv_obj_t* tabview = lv_tabview_create(lv_screen_active());
  lv_obj_t* tab_goto = lv_tabview_add_tab(tabview, "Goto");
  lv_obj_t* tab_identify = lv_tabview_add_tab(tabview, "Identify");

  populate_tab_identify(tab_identify, btnm_jog_value_changed_handler);
}

void loop(void) {
  lv_tick_inc(10);  // Increment LVGL tick count
  delay(10);

  lv_task_handler();  // Process LVGL tasks
}
