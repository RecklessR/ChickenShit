# ChickenShit
Chicken Automation with a particle photon, control an acuator to open/close your cool door, turn heat on and off, monitor sensor data in your coop. Control from a web page.

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


Particle Physical Configuration:


Required Libraries:
- Adafruit_DHT_Particle.h
