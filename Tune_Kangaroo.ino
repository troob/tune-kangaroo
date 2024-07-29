// Programmatic Tune Sample for Kangaroo
// Copyright (c) 2013 Dimension Engineering LLC
// See license.txt for license details.

#include <SoftwareSerial.h>
#include <Kangaroo.h>

// Arduino TX (pin 1) goes to Kangaroo S1
// Arduino RX (pin 0) goes to Kangaroo S2
// Arduino GND         goes to Kangaroo 0V
// Arduino 5V          goes to Kangaroo 5V (OPTIONAL, if you want Kangaroo to power the Arduino)
#define TX_PIN 11
#define RX_PIN 10

// Tune with Mode 1 (Teach Tune).
#define TUNE_MODE_NUMBER 1

// Independent mode channels on Kangaroo are, by default, '1' and '2'.
// Mixed mode channels on Kangaroo are, by default, 'D' and 'T'.
SoftwareSerial  SerialPort(RX_PIN, TX_PIN);
KangarooSerial  K(SerialPort);
KangarooChannel K1(K, 'D');
KangarooChannel K2(K, 'T');

void setup()
{
  SerialPort.begin(9600);
  SerialPort.listen();
  
  // Give the Kangaroo some time to power up.
  delay(2000);

  // Enter the desired tune mode.
  long enterModeParams[1] = { TUNE_MODE_NUMBER };
  K1.systemCommand(KANGAROO_SYS_TUNE_ENTER_MODE, false, enterModeParams, 1);

  // Set the disabled channel bitmask to 0 (tune all channels).
  long disableChannelsParams[1] = { 0 };
  K1.systemCommand(KANGAROO_SYS_TUNE_SET_DISABLED_CHANNELS, false, disableChannelsParams, 1);
  
  // Begin the tune.
  long goParams[0];
  K1.systemCommand(KANGAROO_SYS_TUNE_GO, false, goParams, 0);
}

void loop()
{
  // Tuning has an automatic serial timeout for safety reasons.
  // You must continually send packets or it will abort. getP() in a loop does the job.
  K1.getP();
}
