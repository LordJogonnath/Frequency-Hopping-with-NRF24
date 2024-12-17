#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins
const byte address[6] = "00001"; // Address for communication

void setup() {
  Serial.begin(250000);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); // Set as receiver
}

void loop() {
  if (radio.available()) {
    int sensorValue = 0;
    radio.read(&sensorValue, sizeof(sensorValue));
    Serial.print("Received Sensor Value: ");
    Serial.println(sensorValue);
  } else{
    Serial.println("No data recieved.");
  }
}
