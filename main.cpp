/*
  Optical Heart Rate Detection (PBA Algorithm) using the MAX30105 Breakout
  By: Nathan Seidle @ SparkFun Electronics
  Date: October 2nd, 2016
  https://github.com/sparkfun/MAX30105_Breakout

  This is a demo to show the reading of heart rate or beats per minute (BPM) using
  a Penpheral Beat Amplitude (PBA) algorithm.

  It is best to attach the sensor to your finger using a rubber band or other tightening
  device. Humans are generally bad at applying constant pressure to a thing. When you
  press your finger against the sensor it varies enough to cause the blood in your
  finger to flow differently which causes the sensor readings to go wonky.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.
*/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "MAX30105.h"

#include "heartRate.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// On an arduino Esp32 C3:  Pin 2 (SDA), Pin 3 (SCK), ...

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C //0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59" // UUID do serviço
#define bleServerName "ESP32-C3-MINI"

bool deviceConnected = false;
// Cria uma característica BLE para enviar dados (ex: temperatura)

BLECharacteristic bpmCharacteristic("0ef55e7a-6234-4b1d-8ef1-0477c9c933d0", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bpmCharacteristicDescriptor(BLEUUID((uint16_t)0x2902));
BLECharacteristic oxiCharacteristic("0ef55e7a-6234-4b1d-8ef1-0477c9c933d1", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor oxiCharacteristicDescriptor(BLEUUID((uint16_t)0x2901));


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
MAX30105 particleSensor;
//BluetothSerial SerialBLE;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

class MyServerCallbacks: public BLEServerCallbacks {
void onConnect(BLEServer* pServer) {
  deviceConnected = true;
};
void onDisconnect(BLEServer* pServer) {
  deviceConnected = false;
}
};

void setup(){
  Serial.begin(115200);
  BLEDevice::init(bleServerName);
  
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  /*The callback function MyServerCallbacks() changes the boolean variable deviceConnected 
  to true or false according to the current state of the BLE device. 
  This means that if a client is connected to the server, the state is true. 
  If the client disconnects, the boolean variable changes to false. Here’s the part 
  of the code that defines the MyServerCallbacks() function.*/ 

  BLEService *bpmService = pServer->createService(SERVICE_UUID);


  //BLE.begin();

  bpmService->addCharacteristic(&bpmCharacteristic);
  bpmCharacteristicDescriptor.setValue("BPM");
  bpmCharacteristic.addDescriptor(&bpmCharacteristicDescriptor);



  Serial.println("Iniciando servidor BLE...");

  // Configura nome do dispositivo
  
  // Adiciona serviço e característica
  // Start the service
  bpmService->start();
  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

  // Initialize sensor
  Wire.begin(4,3);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

}

void loop(){
  if (deviceConnected) {//prossegue se o cliente conectou
    
    long irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true)
    {
      //We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20)
      {
        rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
        rateSpot %= RATE_SIZE; //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }

    //Serial.print("IR=");
    //Serial.print(irValue);
    //Serial.print(", BPM=");
    //Serial.print(beatsPerMinute);
    //Serial.print(", Avg BPM=");
    //Serial.println(beatAvg);

    display.display();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);//(0,0) usa o inicio da primeira linha

    if (irValue < 50000){
      //Serial.println(" No finger?");
      display.print("BPM: ");
      display.print("Dedo?");

    }else{
      display.print("BPM:");
      display.print(beatsPerMinute);
      static char beatsPerMinuteBus[6];//crio o bus
      dtostrf(beatsPerMinute, 6, 2, beatsPerMinuteBus);//tranformo o conteudo em string
      bpmCharacteristic.setValue(beatsPerMinuteBus);
      bpmCharacteristic.notify();
    }
  }
}

