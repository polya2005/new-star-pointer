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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displaySensorDetails(void) {
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Driver Ver:   ");
  Serial.println(sensor.version);
  Serial.print("Unique ID:    ");
  Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    ");
  Serial.print(sensor.max_value);
  Serial.println(" m/s^2");
  Serial.print("Min Value:    ");
  Serial.print(sensor.min_value);
  Serial.println(" m/s^2");
  Serial.print("Resolution:   ");
  Serial.print(sensor.resolution);
  Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void) {
  Serial.print("Data Rate:    ");

  switch (accel.getDataRate()) {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print("3200 ");
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print("1600 ");
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print("800 ");
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print("400 ");
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print("200 ");
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print("100 ");
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print("50 ");
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print("25 ");
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print("12.5 ");
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print("6.25 ");
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print("3.13 ");
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print("1.56 ");
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print("0.78 ");
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print("0.39 ");
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print("0.20 ");
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print("0.10 ");
      break;
    default:
      Serial.print("???? ");
      break;
  }
  Serial.println(" Hz");
}

void displayRange(void) {
  Serial.print("Range:         +/- ");

  switch (accel.getRange()) {
    case ADXL345_RANGE_16_G:
      Serial.print("16 ");
      break;
    case ADXL345_RANGE_8_G:
      Serial.print("8 ");
      break;
    case ADXL345_RANGE_4_G:
      Serial.print("4 ");
      break;
    case ADXL345_RANGE_2_G:
      Serial.print("2 ");
      break;
    default:
      Serial.print("?? ");
      break;
  }
  Serial.println(" g");
}

void setup(void) {
  Serial.begin(9600);
  delay(1000);  // delay for the serial monitor to open
  Serial.println("Accelerometer Test");
  Serial.println("");

  /* Initialise the sensor */
  if (!accel.begin()) {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1) {
    }
  }

  /* Set the range to whatever is appropriate for your project */
  // accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  accel.setRange(ADXL345_RANGE_2_G);

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");
}

void loop(void) {
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: ");
  Serial.print(event.acceleration.x);
  Serial.print("  ");
  Serial.print("Y: ");
  Serial.print(event.acceleration.y);
  Serial.print("  ");
  Serial.print("Z: ");
  Serial.print(event.acceleration.z);
  Serial.print("  ");
  Serial.println("m/s^2 ");
  delay(500);
}
