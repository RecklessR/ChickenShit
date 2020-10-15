// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT_Particle.h>

/*

Chicken Shit V4.6 - Automated coop automation using a particle photon. 
Code Creator: Joshua Hancock (RecklessRanch.net) 
GitHub URL:

Current Features:
  - (Chicke_Coop_Door) Operation of acuator by using 2 relays to flip polarity.
  - (Chicken_Coop_Heat) Single relay to be used to control power for a heat or lamp. 
  - (getsensorCall) Ability to pull sensor data from a DHT11.
  - (Photosensor) Ability to pull the light sensor data.
  - (Acuator Button) ability to have a button with one push to open coop dore and push and hold for 5 seconds to close door
  - (Acuator 911 Button) Button to emergency stop the acuator. 
  - (Chicken Shit WWW) web interface to exicute functions and pull sensor data for mobile. 

10/15/2020 - bug fixes
  - Enabled push and hold feature to close door. 
  - clean up code. 
  - Added this section for tracking. 

*/


//We need to track how long the momentary pushbutton is held in order to execute different commands
//This value will be recorded in seconds
float pressLength_milliSeconds = 0;

// Define the *minimum* length of time, in milli-seconds, that the button must be pressed for a particular option to occur
int optionOne_milliSeconds = 100;
int optionTwo_milliSeconds = 2000;  

//Assign names to relays pins
int relayPin = D5;                 // choose the pin for the relay to flip polarity 
int relayPin2 = D6;                 // choose the pin for the relay to flip polarity 
int relayPin5 = D2;                 // choose the pin for the the heat switch.

//Assign names to LED's pins
int led1 = A2;                 // choose the pin for the LED when gate is open
int led2 = A3;                 // choose the pin for the LED when gate is closed
int led5 = A4;                 // choose the pin for the LED when heat is on.

//Assign names to Buttons pins
int button =A5;                //This is the button to OPEN the coop door (soon to close also)
int button2 =A0;                //This is the button to button emergency stop the coop door

//Assign name to photocell pins
int photosensor = A1;               //Pick the analog pin for the photocell(Daylight sensor)
int analogvalue;               //used to store the value of the photosensor

//Assign names to pins for the temp sensor and allow DHT to settings. 
#define DHTPIN D1               //Set DHT pin for temp data
#define DHTTYPE DHT11               //set the type of senor being used DHT11 / DHT22
DHT dht(DHTPIN, DHTTYPE);               //set names being pulled from Adafruit_DHT_Particle.h

int openCall(String extra) {                //this is the Call to set palarity to open (up) It also sets the LED correctly and pushes the event to the event viewer
    digitalWrite(relayPin, LOW);                //set the relaypin to LOW
    digitalWrite(relayPin2, HIGH);                //set the relaypin to HIGH
    digitalWrite(led2, HIGH);                //set LED2 as HIGN
    digitalWrite(led1, LOW);                //set LED1 to LOW
    Particle.publish("Chicken_Coop_Door_Open", "OPEN");                // send event name to particle event
    return 1;                //This sends back an Argument for you know the function was recieved by the particle photon
}
int closeCall(String extra) {                //this is the Call to set palarity to Close (down) It also sets the LED correctly and pushes the event to the event viewer
    digitalWrite(relayPin, HIGH);                //set the relaypin to HIGH
    digitalWrite(relayPin2, LOW);                //set the relaypin to LOW
    digitalWrite(led2, LOW);                //set LED1 to LOW
    digitalWrite(led1, HIGH);                //set LED2 as HIGN
    Particle.publish("Chicken_Coop_Door_Close", "Closed");                // send event name to particle event
    return 0;                //This sends back an Argument for you know the function was recieved by the particle photon
}

int stopCall(String extra) {                //this is the Call to set palarity so both relays are negitive to STOP the acuator in pace,  It also tuns on both LED's and pushes the event to the event viewer
    digitalWrite(relayPin, LOW);
    digitalWrite(relayPin2, LOW);                //set the relaypin to LOW
    digitalWrite(led2, HIGH);                //set LED2 as HIGN
    digitalWrite(led1, HIGH);                //set LED2 as HIGN
    Particle.publish("Chicken_Coop_Door_STOP", "STOP");                // send event name to particle event
    return 3;                //This sends back an Argument for you to know the function was recieved by the particle photon
}
int heatonCall(String extra) {                //this is the call to turn the relay on for the heat lamp,  It also tuns on an LED and pushes the event to the event viewer
    digitalWrite(relayPin5, HIGH);                //set the relaypin to LOW
    digitalWrite(led5, HIGH);                //set LED2 as HIGN
    Particle.publish("Chicken_Coop_Heat_On", "ON");                // send event name to particle event
    return 4;                //This sends back an Argument for you to know the function was recieved by the particle photon
}
int heatoffCall(String extra) {                //this is the call to turn the relay on for the heat lamp,  It also tuns on an LED and pushes the event to the event viewer
    digitalWrite(relayPin5, LOW);                //set the relaypin to HIGH
    digitalWrite(led5, LOW);                //set LED1 to LOW
    Particle.publish("Chicken_Coop_Heat_Off", "OFF");                // send event name to particle event
    return 5;                //This sends back an Argument for you to know the function was recieved by the particle photon
}

//Get temperature
int getsensorCall(String extra) {

analogvalue = analogRead(photosensor);                  //Get Value from the PHOTOSENSOR and save it in memory
float h = dht.getHumidity();                //Get Humidity from the sensor and save it in memory under H
float t = dht.getTempCelcius();                //Get Humidity from the sensor and save it in memory under T
float f = dht.getTempFarenheit();                //Get Humidity from the sensor and save it in memory under F
Particle.publish("Humidity", String(h) + "%");                //Get value of H and send as data to Particle events  
Particle.publish("Temp Celcius", String(t) + " °C");                //Get value of T and send as data to Particle events 
Particle.publish("Temp_Fahrenheit", String(f) + " °F");                //Get value of F and send as data to Particle events 
Particle.publish("Photosensor", String(analogvalue) + " %");                //Get value of PHOTOSENSOR and send as data to Particle events 
return 10;                //This sends back an Argument for you to know the function was recieved by the particle photon
}


void setup()                //This is the start up area where you put your functions to be recieved and set the configuration up on boot. On boot both LED's will be off showing power cycle. 
{
  Particle.function("open", openCall);                // This is the call you send in a URL to Particle from the web site to Open the Coop (Up)
  Particle.function("close", closeCall);                //This is the call you send in a URL to Particle from the web site to Close the Coop (Down)
  Particle.function("stop", stopCall);                //This is the call you send in a URL to Particle from the web site to close the coop (STOP)
  Particle.function("heat_on", heatonCall);                //This is the call you send in a URL to Particle from the web site to Turn the coop heat line on
  Particle.function("heat_off", heatoffCall);                //This is the call you send in a URL to Particle from the web site to Turn the coop heat line off
  Particle.function("Get_Sensor_Data", getsensorCall);
  
//Particle starting. 
  Particle.publish("Status", "Particle on after power cycle");                 //send text to Particle event showing that particle is on after power cycle
  delay(1000);
  Particle.publish("Code Credit", "RECKLESSRANCH.NET");                 //send text to Particle event giving credit to code creator.   

//Set up pin's
  pinMode(relayPin, OUTPUT);                // Set Pin Mode as output for coop door
  pinMode(relayPin2, OUTPUT);                // Set Pin Mode as output for coop door
  pinMode(relayPin5, OUTPUT);                // Set Pin Mode as output for switch on heat lamp
  pinMode(led1, OUTPUT);                // Set Pin Mode as output for when door is open
  pinMode(led2, OUTPUT);                // Set Pin Mode as output for when door is closed
  pinMode(led5, OUTPUT);                // Set Pin Mode as output for when heat is on
  pinMode(photosensor, INPUT);                // Set Pin Mode as INPUT pins (at start up all pins are input unless otherwise called out)
  pinMode(button, INPUT_PULLUP);                // Set up button pressed. 
  pinMode(button2, INPUT_PULLUP);

//Set up relays on start up
  digitalWrite(relayPin, LOW);                //Set relay as LOW to to ensure polarity is set to open the chicken coop during power on sequence
  digitalWrite(relayPin2, HIGH);                //Set relay as HIGH to to ensure polarity is set to open the chicken coop during power on sequence
  Particle.publish("Coop Open", "OPEN");                //sent particle event showing the Coop Door is OPEN
  delay(1000);
  digitalWrite(relayPin5, HIGH);                //Set relay so that the heat/light does not turn on during power on sequence
  Particle.publish("Heat/Light off", "OFF");                //Send particle event showing that the heat power is OFF
  digitalWrite(led1, LOW);                //Set LED1&LED2 as LOW to show power cycle and that system is in power on sequence 
  digitalWrite(led2, LOW);                //Set LED1&LED2 as LOW to show power cycle and that system is in power on sequence 
  digitalWrite(led5, LOW);                //Set LED5 as LOW to show that heat/light is off after power on sequence
  delay(1000);

//temperature Code to start DHT and reference the Adafruit_DHT_Particle.h library 
  Particle.publish("state", "DHT11 starting up");{                //send command to Particle event showing that DHT11 is starting up. 
    dht.begin();                //DHT starting up sequence
//delay(2000);                //Delay to ensure DHT is up and reading before it goes on to the next thing
}
  delay(1000);
  Particle.publish("Status", "Photon Online!");                //Send particle event showing that the particle is up and running. 
//  Serial.begin(9600); 
}



void loop() {                //This is the loop that repeats to exicute something over and over or watch for an input.


while (digitalRead(button) ==LOW){
    delay(100);
    pressLength_milliSeconds = pressLength_milliSeconds + 100;                  //Math to know if the buton was pushed once or held.

}
if(pressLength_milliSeconds >= optionTwo_milliSeconds){                  //Watch for push and hold button press to clsoe the coop door 
     closeCall("closeCall");                 //this is the call that escutes the open function fron above ("closeCall")
     Particle.publish("Button", "close");                 //Send particle event showing that button was helad to open the coop door
}
else if(pressLength_milliSeconds >= optionOne_milliSeconds){                  //Watch for single button press to open the coop door. 
     openCall("openCall");                 //this is the call that escutes the open function fron above ("openCall")
     Particle.publish("Button", "open");                 //Send particle event showing that the button was pushed to be open the coop door.
}
pressLength_milliSeconds=0;                 //reset the timing to watch for button press. 


int button2State = digitalRead(button2);                 //Watch for button press to emergency STOP the coop door. 
if(button2State == LOW){                 //If button state reads LOW that means that the button is being pressed, If HIGH do nothing 
    Particle.publish("Button", "911 STOP");                 //Send Particle event telling it that the button for the door has been pushed.
    stopCall("stopCall");                 //this is the call that escutes the open function fron above ("stopCall")

}
}
//avoid useing delays in the loop as that makes the buttions not respond currectly as the button needs to be pressed after the delay but before the next delay. 
// delay(60000);   // Wait 60 seconds
//  delay(300000);  // Wait 5 min

