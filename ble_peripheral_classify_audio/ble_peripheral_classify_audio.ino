#include <ArduinoBLE.h>
#include <Servo.h>

#include "Mic.h"
#include "classifier_randomForest.h"

#define SAMPLES 64
#define GAIN (1.0f/50)
#define SOUND_THRESHOLD 1000

// for light keyword
#define RED 22     
#define BLUE 24     
#define GREEN 23
#define LED_PWR 25

// for sound keyword
#define PIEZO 9

// for fan keyword
Servo myservo;
int pos = 0;

// for audio sampling
float features[SAMPLES];
String keyword = " ";
Mic mic;
Eloquent::ML::Port::RandomForest clf; // classifier object

// for BLE based Security
const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
int gesture = -1;
BLEService securityService(deviceServiceUuid); 
BLEByteCharacteristic securityCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);


void setup() 
{
    // for light
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(LED_PWR, OUTPUT);
    
    // for sound
    pinMode(PIEZO, OUTPUT);
    
    // for fan
    myservo.attach(9);
    
    // BLE security setup
    if (!BLE.begin()) 
    {
      Serial.println("Starting Bluetooth® Low Energy module failed!");
      while (1);
    }
    BLE.setLocalName("Arduino Nano 33 BLE (Peripheral Device)");
    BLE.setAdvertisedService(securityService);
    securityService.addCharacteristic(securityCharacteristic);
    BLE.addService(securityService);
    securityCharacteristic.writeValue(-1);
    BLE.advertise();
    
    Serial.begin(115200);
    PDM.onReceive(onAudio);
    mic.begin();
    delay(3000);
}


void loop() 
{
    keyword = " ";
    BLEDevice central = BLE.central();
    Serial.println("Discovering central device...");
    delay(500);

  if (central) 
  {
    Serial.println("Connected to central device!");
    Serial.print("Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    while (central.connected()) 
    {
      
      if (recordAudioSample()) 
      {
          Serial.print("You said: ");
          keyword = clf.predictLabel(features);
          Serial.println(keyword);
          if(keyword != " ")
          {
            if(keyword == "light")
            {
              light();
            }
            else if(keyword == "sound")
            {
              sound();
            }
            else if (keyword == "fan")
            {
              fan();
            }
          }
          delay(1000);

      }
      delay(20);
    }
    Serial.println("Disconnected to central device!");
  }
}


// PDM callback to update mic object
void onAudio() 
{
    mic.update();
}


// Read given number of samples from mic
bool recordAudioSample() 
{
    if (mic.hasData() && mic.data() > SOUND_THRESHOLD) 
    {
        for (int i = 0; i < SAMPLES; i++) 
        {
            while (!mic.hasData())
                delay(1);

            features[i] = mic.pop() * GAIN;
        }

        return true;
    }

    return false;
}

void light()
{
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(RED, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(50);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    delay(50);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
    delay(50);  
    digitalWrite(BLUE, LOW);
    digitalWrite(LED_PWR, HIGH);
    delay(50);  
    digitalWrite(LED_PWR, LOW);
    delay(500);
  }
}

void sound()
{
  for (int i = 0; i < 5; i++) 
  {
    tone(PIEZO, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(PIEZO);     // Stop sound...
    delay(1000);        // ...for 1sec
  }
}

void fan()
{
  for (pos = 0; pos <= 180; pos += 1) 
  {
    myservo.write(pos);              // tell servo motor to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo motor to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) 
  {
    myservo.write(pos);              // tell servo motor to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo motor to reach the position
  }
}