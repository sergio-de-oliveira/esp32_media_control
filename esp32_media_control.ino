/* Read Quadrature Encoder
* Connect Encoder to Pins encoder0PinA, encoder0PinB, and +5V.
*
* Sketch by max wolf / www.meso.net
* v. 0.1 - very basic functions - mw 20061220
*
*/  

// https://github.com/T-vK/ESP32-BLE-Keyboard

#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

int val; 
int encoder0PinA = 15;
int encoder0PinB = 2;
int encoder0Pos = 0;
int oldencoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

void setup()
{ 
  pinMode (encoder0PinA,INPUT);
  pinMode (encoder0PinB,INPUT);
  Serial.begin (115200);
  bleKeyboard.begin();
} 
 
void loop()
{ 
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH))
  {
      if (digitalRead(encoder0PinB) == LOW)
      {
          encoder0Pos++;
      } else {
          encoder0Pos--;
      }
      Serial.println(encoder0Pos);
      Serial.println ("/");
  } 
  set_volume();
  encoder0PinALast = n;
    
}

void set_volume(void)
{  
  if (encoder0Pos != oldencoder0Pos)
  {
    if(encoder0Pos > oldencoder0Pos)
    {
      oldencoder0Pos = encoder0Pos;
      if(bleKeyboard.isConnected())
      {
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
        delay(100);
        bleKeyboard.releaseAll();
      }
    }
    else
    {
      oldencoder0Pos = encoder0Pos;
      if(bleKeyboard.isConnected())
      {
        bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
        delay(100);
        bleKeyboard.releaseAll();
      }
    }
  }
}

