/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Henrik EKblad
 * Contribution by a-lurker and Anticimex,
 * Contribution by Norbert Truchsess <norbert.truchsess@t-online.de>
 * Contribution by Tomas Hozza <thozza@gmail.com>
 *
 *
 * DESCRIPTION
 * The EthernetGateway sends data received from sensors to the ethernet link.
 * The gateway also accepts input on ethernet interface, which is then sent out to the radio network.
 *
 * The GW code is designed for Arduino 328p / 16MHz.  ATmega168 does not have enough memory to run this program.
 *
 * LED purposes:
 * - To use the feature, uncomment WITH_LEDS_BLINKING in MyConfig.h
 * - RX (green) - blink fast on radio message recieved. In inclusion mode will blink fast only on presentation recieved
 * - TX (yellow) - blink fast on radio message transmitted. In inclusion mode will blink slowly
 * - ERR (red) - fast blink on error during transmission error or recieve crc error
 *
 * See http://www.mysensors.org/build/ethernet_gateway for wiring instructions.
 *
 */
 
#define MY_DEBUG 
#define MY_RADIO_NRF24
#define MY_RF24_CE_PIN 5
#define MY_RF24_CS_PIN 6
#define MY_GATEWAY_ENC28J60
#define MY_IP_ADDRESS 10,0,7,11  
#define MY_PORT 5003   
//#define MY_CONTROLLER_IP_ADDRESS 192, 168, 178, 254   
#define MY_MAC_ADDRESS 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAA
#define MY_LEDS_BLINKING_FEATURE
#define MY_DEFAULT_LED_BLINK_PERIOD 300

// Enable inclusion mode
#define MY_INCLUSION_MODE_FEATURE
#define MY_INCLUSION_BUTTON_FEATURE
#define MY_INCLUSION_MODE_DURATION 60 
#define MY_INCLUSION_MODE_BUTTON_PIN  3 
#define MY_DEFAULT_ERR_LED_PIN 7  // Error led pin
#define MY_DEFAULT_RX_LED_PIN  8  // Receive led pin
#define MY_DEFAULT_TX_LED_PIN  9  // the PCB, on board LED

#include <SPI.h>
#include <UIPEthernet.h>
#include <MySensors.h>


void setup()
{
}

void loop() {
}
