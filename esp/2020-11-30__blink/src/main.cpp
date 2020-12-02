#include <Arduino.h>

int LED = 5;
int LED1 = 2;      // Assign LED1 to pin GPIO2
int LED2 = 16;     // Assign LED1 to pin GPIO16


void setup() {
  // put your setup code here, to run once:

  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED, LOW);     // turn the LED off
  digitalWrite(LED1, LOW);     // turn the LED off
  digitalWrite(LED2, HIGH);
  delay(1000);                // wait for a second

  digitalWrite(LED, HIGH);  // turn the LED on
  digitalWrite(LED1, HIGH);  // turn the LED on
  digitalWrite(LED2, LOW);
  delay(1000);               // wait for a second
}
