/* ==========================================================================

Amateur Radio Satellite Tracking System using Arduino by Umesh Ghodke
https://sites.google.com/site/k6vugdiary/

Copyright (C) 2012 Umesh Ghodke, Amateur Call Sign K6VUG

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software 
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
MA 02110-1301, USA.

The content is covered under the Creative Commons Attribution-ShareAlike 3.0 
License (http://creativecommons.org/licenses/by-sa/3.0/)

========================================================================== */

// Includes for CnC Shield V3 with DRV8825 Drivers and common NEMA 17 Stepper Motors
#include <AccelStepper.h>

// Constants for CnC Shield v3.0 with X=Az and Y=El Stepper Motors
#define SPEED_DEFAULT 500.0
#define ACCEL_DEFAULT 250.0
#define STEPS_360 1600  // currently 8825 drivers on board are jumpered for 1/8 - full is 200, 1/2 is 400, 1/4 is 800, 1/8 is 1600
#define CCW_MOTOR_AZ false // set this to true if clockwise command moves rotor anti-clockwise
#define CCW_MOTOR_EL false // set this to true if clockwise command moves rotor anti-clockwise

// Setup Steppers
AccelStepper stepper1(AccelStepper::DRIVER, 2, 5);  // Type, Step Pin, Direction Pin
AccelStepper stepper2(AccelStepper::DRIVER, 3, 6);  // Type, Step Pin, Direction Pin

// ----------------------------------------------------------------------------------------

void setupSteppers()  // initialize motor shield
{
  initMotors();
  pinMode(8, OUTPUT);  // initialize the CnC Shield Motors. Required Output and Low.
  digitalWrite(8, LOW);
  // initialize current position based on stepper data (defined with step settings)
  curAz = stepper1.currentPosition() * 360 / STEPS_360;
  curEl = stepper2.currentPosition() * 360 / STEPS_360;
}

void loopSteppers()  // move the motors one step towards target position (defined with step settings)
{
  if ((stepper1.distanceToGo() != 0))
  {
    stepper1.run();
    curAz = stepper1.currentPosition() * 360 / STEPS_360;
  }
  if ((stepper2.distanceToGo() != 0))
  {
    stepper2.run();
    curEl = stepper2.currentPosition() * 360 / STEPS_360;
  }
}

void initMotors()
{
  stepper1.setMaxSpeed(SPEED_DEFAULT);
  stepper1.setAcceleration(ACCEL_DEFAULT);
  stepper2.setMaxSpeed(SPEED_DEFAULT);
  stepper2.setAcceleration(ACCEL_DEFAULT);
}

void setNewAz(int pos)  // set new target for stepper motor
{
  long newAzStep = ((long)pos) * STEPS_360 / 360;
  stepper1.moveTo(newAzStep);
}

void setNewEl(int pos)  // set new target for stepper motor
{
  long newElStep = ((long)pos) * STEPS_360 / 360;
  stepper2.moveTo(newElStep);
}

void stopMotorAz()  // calculate current position from stepper data (defined with step settings)
{
  delay(200);
  curAz = stepper1.currentPosition() * 360 / STEPS_360;
}

void stopMotorEl()  // calculate current position from stepper data (defined with step settings)
{
  delay(200);
  curEl = stepper2.currentPosition() * 360 / STEPS_360;
}

void setZeroPositions()
{
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  curAz = 0; newAz = curAz;
  curEl = 0; newEl = curEl;
  initMotors();
}

void printMotorParameters()  // Sends the current parameters of the azimuth servo back to the PC
{
  Serial.print("Stepper Speed: ");
  Serial.println(SPEED_DEFAULT);
  Serial.print("Stepper Accel: ");
  Serial.println(ACCEL_DEFAULT);
  Serial.print("Current Azimuth: ");
  Serial.println(curAz);
  Serial.print("Current Elevation: ");
  Serial.println(curEl);
}
//////////////////////////////////////////////////////////////////////////////////////
