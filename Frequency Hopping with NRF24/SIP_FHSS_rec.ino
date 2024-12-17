#include <SPI.h>
#include <RF24.h>

//Manually assigning the CE and CSN pins:
RF24 radio(7,10); //Setting CE to 7 and CSN to 10

//Array of available channels (frequencies)
const uint8_t channels[] = {1, 50, 100, 124};
uint8_t current = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  radio.startListening();

  changeChannel();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(radio.available()){
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Revceived message: ");
    Serial.println(text);
  }
  
  delay(100);
  changeChannel();

}

void changeChannel(){
  current = (current+1) % 4;
  radio.setChannel(channels[current]);
  Serial.print("Switched to channel: ");
  Serial.println(channels[current]);
  delay(500);
}
