#include <EEPROM.h>
#include <cc1101.h>
#include <Wire.h>  // I2C arduino library ( comes with arduino )


// The connection to the hardware chip CC1101 the RF Chip
CC1101 cc1101;

byte b;
byte i;
byte syncWord[2] = {199, 0};
long counter = 0;
byte chan = 0;

// a flag that a wireless packet has been received
boolean packetAvailable = false;


/* Handle interrupt from CC1101 (INT0) gdo0 on pin2 */
void cc1101signalsInterrupt(void) {
  // set the flag that a package is available
  packetAvailable = true;
}

// SETUP HERE

void setup()
{

  // initialize the RF Chip
  cc1101.init();
  cc1101.setSyncWord(syncWord);
  cc1101.setCarrierFreq(CFREQ_433);
  cc1101.disableAddressCheck(); //if not specified, will only display "packet received"
  //cc1101.setTxPowerAmp(PA_LowPower);


  attachInterrupt(0, cc1101signalsInterrupt, FALLING);   // need to find out what this does !! BB, initialise rf?
  delay(800);
}

void loop()
{
  // BLINK Packet Recieved if wanted
  if (packetAvailable) {
    detachInterrupt(0);
    // clear the flag
    packetAvailable = false;

    CCPACKET packet;

    if (cc1101.receiveData(&packet) > 0) {
      if (!packet.crc_ok) {
        Serial.println("crc not ok");
        delay(200);
        Serial.println("          ");
      }

      if (packet.length > 0) {
        Serial.println((char *) packet.data);
      }
    }
  }
  // Enable wireless reception interrupt
  attachInterrupt(0, cc1101signalsInterrupt, FALLING);
}
