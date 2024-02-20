#include <JC_Button.h>
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
#include <FastLED.h>
#include <Keyboard.h>
#include <Mouse.h>
#define outputA 9
#define outputB 10
#define touch 3
#define button 2 
#define NUM_LEDS 5
#define DATA_PIN 18


Encoder myEnc(outputA, outputB);
Button mb(button);

long buttonTimer = 0;
long longPressTime = 250;
boolean buttonActive = false;
boolean longPressActive = false; 
CRGB leds[NUM_LEDS];
long position  = -999;


 void setup() 
 { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   //pinMode (button, INPUT_PULLUP);
   
   Serial.begin (9600);
   Keyboard.begin();
   Mouse.begin();
   mb.begin();
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
     leds[0] = CRGB::Red;
     FastLED.show();
     leds[4] = CRGB::Red;
     FastLED.show();
     leds[1] = CRGB(0,229,255);
     FastLED.show();
     leds[2] = CRGB(0,229,255);
     FastLED.show();
     leds[3] = CRGB(0,229,255);
     FastLED.show();   
 } 
 
 
 int msl()
 {
   int juna = -999, n = 0, nava; 
   for(int i = 0; i<=4; i++)
   {
     leds[i] = CRGB::White;
   }
   while(1)
   { 
     mb.read();
     if(mb.isPressed())
     {
       nava = myEnc.read();
       
       if(nava != juna)
       {
         if(nava > juna) n++;
         else if(nava < juna) n--;
         
         juna = nava;
         
         if(n > 5 ) n = 1;
         else if(n < 1) n = 5; 
       }
       
       for(int i = 1; i <= 5; i++)
       {
         if(i == n)
         { leds[i-1] = CRGB::Red; FastLED.show(); }
         else
         { leds[i-1] = CRGB::White; FastLED.show(); }
       }
     }
     
     else  break;
   }
   //Serial.println(n);
   return n;
 }
 
 
 void loop()
 { 
   int x; 
   mb.read();
   if(mb.pressedFor(500))
   {
     x = msl();
   }
   
   switch(x)
   {
     case 1:
     Serial.println("Mode 1");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(0,229,255); FastLED.show(); }
     delay(200);
     break;
     
     case 2:
     Serial.println("Mode 2");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(118,255,3); FastLED.show(); }
     delay(200);
     break;
     
     case 3:
     Serial.println("Mode 3");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(255,145,0); FastLED.show(); }
     delay(200);
     break;
     
     case 4:
     Serial.println("Mode 4");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(245,0,87); FastLED.show(); }
     delay(200);
     break;
     
     case 5:
     Serial.println("Mode 5");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(156,39,176); FastLED.show(); }
     delay(200);
     break; 
   }
   
   
   
   long newPos = myEnc.read();
   if (newPos != position) 
   {
    
    //Serial.println(position);
   
   
     if(newPos>position)
     {  
     Keyboard.press(KEY_DOWN_ARROW);
     Keyboard.releaseAll();
     }
   
     else if(newPos<position)
     {
     Keyboard.press(KEY_UP_ARROW);
     Keyboard.releaseAll();
     }
    Serial.println(position);
    position = newPos;
   }
 
 
   
//---------------------------------------//
//-------------Read Touch----------------//
//-------------------------------------- //



  if (digitalRead(touch) == HIGH)
  {  
      if (buttonActive == false) 
      {

      buttonActive = true;
      buttonTimer = millis();

      }

      if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) 
      {

        longPressActive = true;
        Serial.println("Long Press");
        while(1)
        { 
         long newPos = myEnc.read();
         if (newPos != position) 
         {
           if(newPos>position)
           {  
              // Remote.decrease();
              // Remote.clear();
               Serial.println(" VI");
           }
       
           else if(newPos<position)
           {
              // Remote.increase();
             //  Remote.clear();
               Serial.println(" VD");
           }
   
          position = newPos;
         }
         
         if (digitalRead(touch) == LOW)
         break;

      }//while

     }//if millis
      
  } //if button
  
  else

  {
     
      if (buttonActive == true) 
      {
         
          if (longPressActive == true) 
          {
            longPressActive = false;
            Serial.println("Press End");
          } 

          else 
          {
            Mouse.click();
            Mouse.release();	
            Serial.println("Click");
          }
    
       buttonActive = false;

     }

  } //else*/

 
}//end loop
