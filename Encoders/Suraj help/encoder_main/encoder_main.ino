#include "encoder.h"
#include <stdio.h>


void setup() {
  encoder_init();
  Serial.begin(9600);
  Serial.println("Initialized encoder and serial lines");
  
}

void loop() {
  long pulses = 0;
  if (isChanged()) {
    pulses = getPulses();
    Serial.println(pulses);
  }
  // send pulses value over serial
  
  delay(1);
  
}
