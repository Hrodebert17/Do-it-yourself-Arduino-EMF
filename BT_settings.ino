#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

#define baudrate 38400

SoftwareSerial bluetooth(rxPin, txPin);

void setup() {
  Serial.begin(baudrate);
  bluetooth.begin(baudrate);
}

void loop() {
  if(bluetooth.available()){
    Serial.write(bluetooth.read());
  }
  if(Serial.available()){
    bluetooth.write(Serial.read());
  }
}
