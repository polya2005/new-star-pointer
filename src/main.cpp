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
#include <DFRobot_QMC5883.h>
#include <Wire.h>

DFRobot_QMC5883 compass(&Wire, QMC5883_ADDRESS);

void setup(void) {
  Serial.begin(9600);
  delay(1000);  // delay for the serial monitor to open
  while (!compass.begin()) {
    Serial.println("Could not find a valid 5883 sensor, check wiring!");
    delay(500);
  }
}

void loop(void) {
  sVector_t mag = compass.readRaw();
  Serial.print("X: ");
  Serial.print(mag.XAxis);
  Serial.print(" Y: ");
  Serial.print(mag.YAxis);
  Serial.print(" Z: ");
  Serial.println(mag.ZAxis);
  delay(1000);
}
