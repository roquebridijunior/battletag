#include <EEPROM.h>
#include <cc1101.h>
#include <Wire.h>  // I2C arduino library ( comes with arduino )
#include <string>

CC1101 cc1101;

// counter to get increment in each loop
byte counter;
byte b;
byte syncWord[2] = {199, 0};   // sender and reciever must have same!!! like ip address?

//LCD SCREEN SETUP

// SETUP HERE
void setup()
{
  // reset the counter
  counter = 0;

  // initialize the RF Chip
  cc1101.init();
  cc1101.setSyncWord(syncWord);
  cc1101.setCarrierFreq(CFREQ_433);
  cc1101.disableAddressCheck();
  cc1101.setTxPowerAmp(PA_LongDistance);  // if you want HIGH POWER
  delay(500);
}
/// end void setup

// send_data() becomes a function to be used in void loop()

void send_data()
{

  std::string mensagem ("Roque bixao da goiaba!");

  cc1101.flushTxFifo ();  // is this needed???

  CCPACKET packet;
  packet.length = mensagem.length();

  strcpy((char *) packet.data, mensagem.c_str());

  if (cc1101.sendData(packet)) {

    delay(1000);
    Serial.println("Pacote na caixa de correio.");

  } else {
    Serial.println("Correios não conseguiu entregar o pacote!");
  }
}

// send data ( does this send all the data in state machine?? )

void loop()
{
  send_data();
  delay(2000);
}
