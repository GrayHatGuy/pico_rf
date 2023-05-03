/*

Add library https://github.com/adafruit/RadioHead
*/

#include <SPI.h>
#include <RH_RF95.h>
#include <pins_arduino.h>
#include <RH_ASK.h>

// Master clock frequency
#define VARIANT_MCK     (62500000ul)

// Frequency of the board main oscillator
#define VARIANT_MAINOSC (12000ul) 
//#define bitOrder BitOrderMSBFirst

//In this instructable I don't use a sensor to generate data. If you wan't to
//send sensordata you need to attach a sensor and write this to a variable
//Set the temp variable.
float variable = 5.0;

//Pin 11 on the arduino is het MOSI pin master out slave in for data from arduino to radio
//Pin 12 on the arduino is the MISO pin master in slave out for data from radio to the arduino 
//Pin 13 on the arduino is the sck pin is the clock pin

//Assign to any open digital pin 
#define RESET 9
#define DIO0 7
#define NSS 8

//RP2040 SPI_0 bus see Pins_Arduino.h move to RH_ASK.h 
#define MISO 16
#define MOSI 19
#define SCK 18

#define FREQ 915.0 //433.0 //915.0

//define the ledpin
//#define LED 13

//construct the lora connection
RH_RF95 rf95(NSS, DIO0);



void setup()
{
  //pinMode(LED, OUTPUT);
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);

  while(!Serial);
  Serial.begin(9600);
  delay(100);

  digitalWrite(RESET, LOW);
  delay(10);
  digitalWrite(RESET, HIGH);
  delay(10);

  //initialize the lora connection
  while(!rf95.init()) {
  Serial.println("Initializing actuator...");
  while (1);
  }
  Serial.println("Succeeded");

  //set the lora frequency
  if (!rf95.setFrequency(FREQ)) {
    Serial.println("Cant set frequency");
    while (1);
  }
  Serial.print("Set freq to: "); Serial.println(FREQ);
  //set the transmission power from 5 to 23
  rf95.setTxPower(5, false);
}

void loop()
{
  if (rf95.available())
  {
    //read the message())
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      //receive message
//      digitalWrite(LED, HIGH);
      RH_RF95::printBuffer("Trigger Received: " , buf, len);
      Serial.print("Got: ");
      Serial.println((char*)buf);

      //Send reply
      uint8_t data[] = "ACK";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Serial.println("ACK Sent");
      //digitalWrite(LED, LOW);
    }
    else
    {
      //if receive failed
      Serial.println("recieve failed");
    }
  }
}
