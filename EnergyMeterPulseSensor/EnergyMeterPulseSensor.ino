/**
 * REVISION HISTORY
 * Version 1.0.2 - Hans Pellikaan
 * (Based on Version 1.0 - Henrik EKblad)
 * 
 * DESCRIPTION
 * This sketch provides an example how to implement a distance sensor using HC-SR04 
 * Use this sensor to measure KWH and Watt of your house meeter
 * You need to set the correct pulsefactor of your meeter (blinks per KWH).
 * The sensor starts by fetching current KWH value from gateway.
 * Reports both KWH and Watt back to gateway.
 * 
 * NOTE:
 * Adjustment made for a Ferraris meter instead of the original LED-(blink)-meter 
 * A Ferrris meter provides a inverted pulse.
 *
 * http://www.mysensors.org/build/pulse_power
 */

#define MY_DEBUG
#define MY_RADIO_NRF24

#include <SPI.h>
#include <MySensors.h>  

#define DIGITAL_INPUT_SENSOR 3  // The digital input you attached your light sensor.  (Only 2 and 3 generates interrupt!)
#define PULSE_FACTOR 600        // Nummber of blinks per KWH of your meeter
#define SLEEP_MODE false        // Watt-value can only be reported when sleep mode is false.
#define MAX_WATT 10000          // Max watt value to report. This filetrs outliers.
#define CHILD_ID 1              // Id of the sensor child

unsigned long SEND_FREQUENCY = 20000;       
double ppwh = ((double)PULSE_FACTOR)/1000;  // Pulses per watt hour
boolean pcReceived = false;
volatile unsigned long pulseCount = 0;   
volatile unsigned long lastBlink = 0;
volatile unsigned long watt = 0;
unsigned long oldPulseCount = 0;   
unsigned long oldWatt = 0;
double oldKwh;
unsigned long lastSend;
MyMessage wattMsg(CHILD_ID,V_WATT);
MyMessage kwhMsg(CHILD_ID,V_KWH);
MyMessage pcMsg(CHILD_ID,V_VAR1);


void setup()  
{  
  request(CHILD_ID, V_VAR1);
  pinMode(DIGITAL_INPUT_SENSOR,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DIGITAL_INPUT_SENSOR), onPulse, FALLING);   // Adjusted for Ferraris meter on old fashion meter instead of blinking LED on smartmwatteter
  lastSend=millis();
}

void presentation() {
  sendSketchInfo("Energy Meter", "1.0.2");
  present(CHILD_ID, S_POWER);
}

void loop()     
{ 
  unsigned long now = millis();
  bool sendTime = now - lastSend > SEND_FREQUENCY;
  if (pcReceived && (SLEEP_MODE || sendTime)) {
    if (!SLEEP_MODE && watt != oldWatt) {
      if (watt<((unsigned long)MAX_WATT)) {
        send(wattMsg.set(watt));  // Send watt value to gateway
      }  
      Serial.print("Watt:");
      Serial.println(watt);
      oldWatt = watt;
    }
  
    // Pulse count has changed
    if (pulseCount != oldPulseCount) {
      send(pcMsg.set(pulseCount));  // Send pulse count value to gateway
      double kwh = ((double)pulseCount/((double)PULSE_FACTOR));     
      oldPulseCount = pulseCount;
      if (kwh != oldKwh) {
        send(kwhMsg.set(kwh, 4));  // Send kwh value to gw 
        oldKwh = kwh;
      }
    }    
    lastSend = now;
  } else if (sendTime && !pcReceived) {
    request(CHILD_ID, V_VAR1);
    lastSend=now;
  }
  
  if (SLEEP_MODE) {
    sleep(SEND_FREQUENCY);
  }
}

void receive(const MyMessage &message) {
  if (message.type==V_VAR1) {  
    pulseCount = oldPulseCount = message.getLong();
    Serial.print("Received last pulse count from gw:");
    Serial.println(pulseCount);
    pcReceived = true;
  }
}

void onPulse()     
{ 
  if (!SLEEP_MODE) {
    unsigned long newBlink = micros();  
    unsigned long interval = newBlink-lastBlink;
    if (interval<10000L) { // Sometimes we get interrupt on RISING
     return;
    }
    watt = (3600000000.0 /interval) / ppwh;
    lastBlink = newBlink;
  } 
  pulseCount++;
}



