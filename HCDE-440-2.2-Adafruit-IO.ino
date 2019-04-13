//ICE 2

// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials  X
// and any additional configuration needed for WiFi, cellular,  X
// or ethernet clients.
#include "config.h"0


/************************ Example Starts Here *******************************/

// digital pin 5
#define BUTTON_PIN 5
#define PHOTOCELL_PIN A0

// button state
bool currentbut = false;
bool lastbut = false;

// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("button");

// photocell state
int current = 0;
int last = -1;
 
// set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("lightboi");

void setup() {

  // set button pin as an input
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // start the serial connection
  Serial.begin(115200);
  Serial.print("This board is running: ");
  Serial.println(F(__FILE__));
  Serial.print("Compiled: ");
  Serial.println(F(__DATE__ " " __TIME__));

  delay(2000);
  
  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // grab the current state of the button.
  // we have to flip the logic because we are
  // using a pullup resistor.
  if(digitalRead(BUTTON_PIN) == LOW)
    currentbut = true;
  else
    currentbut = false;

  // return if the value hasn't changed
  if(currentbut == lastbut)
    //return;

  // save the current state to the 'digital' feed on adafruit io
  Serial.print("sending button -> ");
  Serial.println(currentbut);
  digital->save(currentbut);

  // store last button state
  lastbut = currentbut;

  // grab the current state of the photocell
  current = analogRead(PHOTOCELL_PIN);
  Serial.println(current);
  Serial.println(last);
 
  // return if the value hasn't changed
  if(current == last) {
    Serial.println("same tbh");
    delay(500);
    return;
  }

  // save the current state to the analog feed
  Serial.print("sending -> ");
  Serial.println(current);
  analog->save(current);
 
  // store last photocell state
  last = current;
 
  // wait one second (1000 milliseconds == 1 second)
  delay(500);

}
