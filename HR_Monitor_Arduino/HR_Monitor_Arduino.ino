#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <EEPROM.h>

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                             

int fatburnPoints;
int finalfatburnPoints;
int a = 0;
                          
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() 
{   

  Serial.begin(9600);                   // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);  
   
 
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) 
   {
     Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
   }
    finalfatburnPoints = EEPROM.read(a);
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".                                             
 int i=0;
 
if (pulseSensor.sawStartOfBeat())               //Constantly test to see if "a beat happened"
{           
  while(myBPM > 60 && myBPM < 85 && i<10)     //adds points while in fat burn HR. 
  {
    fatburnPoints++;
    i++;                                      //i++ is needed to leave the loop and recheck if HR is still in zone.
    //should add the new FBP to the previous then update the number.
    EEPROM.update(a, fatburnPoints);          //Saves the data at address a
  } 
}

  delay(20);                                  //delay 0.02 seconds.
             
  Serial.println(EEPROM.read(a));             //prints the points in address A (this is what is used in UE4)
}

  
