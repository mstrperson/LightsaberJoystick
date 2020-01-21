#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Joystick.h"

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);
Joystick_ Joystick;

bool state[3] = { false, false, false };

void setup() {
  // put your setup code here, to run once:
  Joystick.setRxAxisRange(0,360);
  Joystick.setRyAxisRange(-90,90);
  Joystick.setRzAxisRange(-180,180);
  
  Joystick.begin();

  bno.begin();
  bno.setExtCrystalUse(true);

  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  Joystick.setRxAxis(euler.x());
  Joystick.setRyAxis(euler.y());
  Joystick.setRzAxis(euler.z());

  for(int b = 0; b < 3; b++)
  {
    if(digitalRead(b+10) != state[b])
    {
      if(state[b]) Joystick.pressButton(b);
      else Joystick.releaseButton(b);

      state[b] = !state[b];
    }
  }
  
}
