#include <Wire.h>
#include <StateMachine.h>
#include <OneShot.h>
#include <PushButton.h>
#include <Pulse.h>

#include "SwitchMachineCommands.h"

// GPIO pin assignments
const byte pinLED     = 13;   // LED, output
const byte pinRefresh = 12;   // "refresh" pushbutton, input
const byte pinReset   = 11;   // "reset" pushbutton, input

// I2C address of attached SwitchMachineController
const byte I2C_ADDR = 0x30;

// A randomly selected direction/channel command byte
// will be transmitted every 5 seconds.
StateMachine pacer(5000, true);   // 5 sec

// The onboard LED, when triggered, will flash for 200 msec.
Pulse led(pinLED, HIGH, 200);           // 0.2 sec

// Berrett Hill Momentary Touch Toggles are connected
// to the input pins.  Multiple presses are locked out
// if they occur within 500 msec after the first.
PushButton pbRefresh(pinRefresh, LOW, 500);
PushButton pbReset(pinReset, LOW, 500);

// Command bytes to be randomly transmitted.
const byte cmds[] = {
  eDiv  | eChan0,
  eDiv  | eChan1,
  eMain | eChan0,
  eMain | eChan1
};
const byte num_cmds = sizeof cmds / sizeof *cmds;

// Transmit byte to specific I2C address.
void send(const byte addr, const byte b)
{
  Wire.beginTransmission(addr);
  Wire.write(b);
  Wire.endTransmission();
}

void setup()
{
  // Enable I2C.
  Wire.begin();
}

void loop()
{
  // If it's time to transmit a random command byte...
  if (pacer.update()) {
    // ... do it...
    send(I2C_ADDR, cmds[random(num_cmds)]);
    // ... and trigger the LED to flash.
    led.trigger();
  }
  // Update the LED's Pulse object.
  led.update();
  
  // If the "refresh" button is pressed,
  // transmit the refresh command code.
  if (pbRefresh.update()) {
    send(I2C_ADDR, eRefresh);
  }
  
  // If the "reset" button is pressed,
  // transmit the reset command code.
  if (pbReset.update()) {
    send(I2C_ADDR, eReset);
  }
}
