#include <SPI.h>
#include <RF24.h>

//For manually assigning the CE and CSN pins:
RF24 radio(8,10); //CE is 8, CSN is 10

//Array of available frequencies (channels):
const uint8_t channels[] = {1, 50, 100, 124};
uint8_t current = 0; //Index to keep track of current channel

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin(); //Iniitalzing the radio
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
  radio.openWritingPipe(0xF0F0F0F0E1LL); //setting address for the transmitter

  changeChannel(); 
}

void loop() {
  // put your main code here, to run repeatedly:
    changeChannel();
    sendMessage();
    delay(100);
}

void changeChannel(){
  current = (current + 1) % 4;
  radio.setChannel(channels[current]);
  Serial.print("Switched to channel: ");
  Serial.println(channels[current]);
}

void sendMessage(){
  const char text[] = "hey partner!";
  radio.stopListening();
  bool result = radio.write(&text, sizeof(text));

  delay(500);
}

