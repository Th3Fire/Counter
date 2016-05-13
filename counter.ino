#include "TM1636.h"
#include <EEPROM.h>
TM1636 tm1636(7, 8);
int8_t disp[4];
int addr[3];
int counter;
int reset = 0;
int value[4];
boolean check = false;
void setup()
{ Serial.begin(9600);

  if (check == false) {
    for (int i = 0; i <= 3; i++) {
      value[i] = EEPROM.read(i);
      disp[i] = value[i];
    }
    counter = value[0] * 1000 + value[1] * 100 + value[2] * 10 + value[3];
    check = true;
  }
  tm1636.init();
  pinMode(11, INPUT_PULLUP); //Menu
  pinMode(10, INPUT_PULLUP); //Up
  pinMode(9, INPUT_PULLUP); //Down
  pinMode(6, OUTPUT);
}
void loop()
{
  int temp = counter;
  disp[0] = temp / 1000; temp = counter % 1000;
  disp[1] = temp / 100; temp = counter % 100;
  disp[2] = temp / 10; temp = counter % 10;
  disp[3] = temp;

  if (digitalRead(10) == LOW) { // Up
    if (counter == 9999) {
      counter = 0;
    }
    else
      counter++;
    Serial.print("counter = ");
    Serial.println(counter);
    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(6, LOW);
    delay(100);
  }

  if (digitalRead(9) == LOW) { // Down
    if (counter == 0) {
      counter = 9999;
    }
    else
      counter--;

    Serial.print("counter = ");
    Serial.println(counter);
    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(6, LOW);
    delay(100);

  }
  if (digitalRead(11) == LOW) // Reset
  {
    counter = 0;
    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(6, LOW);
    delay(100);
  }

  for (int i = 0; i <= 3; i++) {
    EEPROM.write(i , disp[i]);
  }
  tm1636.display(disp);
  Serial.write(counter);
  delay(10);

}

