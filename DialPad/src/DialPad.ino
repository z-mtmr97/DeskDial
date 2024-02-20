#include <HID-Project.h>
#include <HID-Settings.h>

#include <Encoder.h>
#define ENCODER_DO_NOT_USE_INTERRUPTS


#define outputA 14
#define outputB 16
long position  = -999;
long newPos;
Encoder myEnc(outputA, outputB);

#include <ButtonEvents.h> 
const byte b1 = 7; 
const byte b2 = 9; 
const byte b3 = 18; 
//const byte enc_b = 15; Reserved for Encoder Press button
ButtonEvents mb1;
ButtonEvents mb2;
ButtonEvents mb3;

#include <FastLED.h>
#define NUM_LEDS 3
#define DATA_PIN 21
CRGB leds[NUM_LEDS];




void setup() 
{
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT); 
   
  mb1.attach(b1);
  mb2.attach(b2);
  mb3.attach(b3);
  
  mb1.activeLow();
  mb2.activeLow();
  mb3.activeLow();
  
  mb1.debounceTime(15);
  mb2.debounceTime(15);
  mb3.debounceTime(15);
  
  mb1.doubleTapTime(150);
  mb2.doubleTapTime(150);
  mb3.doubleTapTime(150);
   
  mb1.holdTime(400);
  mb2.holdTime(400);
  mb3.holdTime(300); 
  
  Serial.begin(115200);
  Keyboard.begin();
  Consumer.begin();
  Mouse.begin();

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}//end setup



void loop()
{
  m1();
}









/******************
 * ===============
 * Mode Functions
 * ===============
 *****************/




 /*================
 * Mode 1 Function
===================*/

void m1()
{
  led(1);
  while(1)
  {
    if (mb1.update() == true)
      { 
        switch(mb1.event())
        { 
          case (tap) :
          Mouse.click();
          //Serial.println("1s");
          //Serial.println("Click");
          break;
    
          case (doubleTap):
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('c');
          Keyboard.releaseAll();
          //Serial.println("1d");
          //Serial.println("Double");
          break;
    
          case (hold):
          { //Serial.println("Hold On");
            //Serial.println("1h");
           while(mb1.read() == 0)
           {
            //Serial.println(mb1.read());   
            newPos = myEnc.read();
            if (newPos != position) 
            {  
          
              if(newPos>position)
              { 
                Consumer.write(MEDIA_VOLUME_DOWN);
              }
       
              else if(newPos<position)
              {
                Consumer.write(MEDIA_VOLUME_UP);
              }  
              position = newPos;
            }
            
            mb1.update();
          }//while held
         }//hold
        }//switch
       }//if mb1


     else if(mb2.update() == true)
       {
        switch(mb2.event())
        {
          case (tap) :
          //Serial.println("2s");
          break;
    
          case (doubleTap):
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('v');
          Keyboard.releaseAll();
          //Serial.println("2d");
          break;
    
          case (hold):
          { //Serial.println("2h");
            while(mb3.read() == 0)
           {
            
              mb2.update();
           }//while held
          }//hold
          
        }//switch
       } //elif mb2


     else if(mb3.update() == true)
       {
        switch(mb3.event())
        {
          case (tap) :
          //Serial.println("3s");
          break;
    
          case (doubleTap):
          //Serial.println("3d");
          break;
    
          case (hold):
          {//Serial.println("3h");
            while(mb3.read() == 0)
           {
              if(mb1.update() == true && mb1.event() == (tap))
              {
                m2();
              }
              else if(mb2.update() == true && mb2.event() == (tap))
              {
                m3();
              }
              mb3.update();
           }//while held
          }//hold
          
        }//switch
       } //elif mb3



  
    else  //Simple Scroll
    {
       newPos = myEnc.read();
       if (newPos != position) 
       {  
   
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
         position = newPos;
       }
     
    }//end else
 
 }//end while
}//end m1










/*================
 * Mode 2 Function
===================*/

void m2()
{
  led(2);
  while(1)
  {
    if (mb1.update() == true)
      { 
        switch(mb1.event())
        { 
          case (tap) :
          //Serial.println("Click");
          break;
    
          case (doubleTap):
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('s');
          Keyboard.releaseAll();
          //Serial.println("Double");
          break;
    
          case (hold):
          { //Serial.println("Hold On");
           while(mb1.read() == 0)
           {
            //Serial.println(mb1.read());   
            newPos = myEnc.read();
            if (newPos != position) 
            {  
          
              if(newPos>position)
              { 
                Consumer.write(MEDIA_VOLUME_DOWN);
              }
       
              else if(newPos<position)
              {
                Consumer.write(MEDIA_VOLUME_UP);
              }  
              position = newPos;
            }
            
            mb1.update();
          }//while held
         }//hold
        }//switch
       }//if mb1


     else if(mb2.update() == true)
       {
        switch(mb2.event())
        {
          case (tap) :
          break;
    
          case (doubleTap):
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('s');
          Keyboard.releaseAll();
          break;
    
          case (hold):
          {
            while(mb2.read() == 0)
           {
              Keyboard.press(KEY_LEFT_ALT);
              mb2.update();
           }//while held
          }//hold
          Keyboard.releaseAll();
          
        }//switch
       } //elif mb2


     else if(mb3.update() == true)
       {
        switch(mb3.event())
        {
          case (tap) :
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('.');
          Keyboard.releaseAll();
          break;
    
          case (doubleTap):
          m1();
          break;
    
          case (hold):
          {
            while(mb3.read() == 0)
           {
            
              mb3.update();
           }//while held
          }//hold
          
        }//switch
       } //elif mb3
  
    else  //Simple Scroll
    {
       newPos = myEnc.read();
       if (newPos != position) 
       {  
   
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
         position = newPos;
       }
     
    }//end else
 
 }//end while
}//end m2












/*================
 * Mode 3 Function
===================*/

void m3()
{
  led(3);
  while(1)
  {
    if (mb1.update() == true)
      { 
        switch(mb1.event())
        { 
          case (tap) :
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('.');
          Keyboard.releaseAll();
          //Serial.println("Click");
          break;
    
          case (doubleTap):
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('s');
          Keyboard.releaseAll();
          //Serial.println("Double");
          break;
    
          case (hold):
          { //Serial.println("Hold On");
           while(mb1.read() == 0)
           {
            //Serial.println(mb1.read());   
            newPos = myEnc.read();
            if (newPos != position) 
            {  
          
              if(newPos>position)
              { 
                Consumer.write(MEDIA_VOLUME_DOWN);
              }
       
              else if(newPos<position)
              {
                Consumer.write(MEDIA_VOLUME_UP);
              }  
              position = newPos;
            }
            
            mb1.update();
          }//while held
         }//hold
        }//switch
       }//if mb1


     else if(mb2.update() == true)
       {
        switch(mb2.event())
        {
          case (tap) :
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('u');
          Keyboard.releaseAll();
          break;
    
          case (doubleTap):
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('s');
          Keyboard.releaseAll();
          break;
    
          case (hold):
          {
            while(mb2.read() == 0)
           {
              mb2.update();
           }//while held

            Keyboard.press(KEY_LEFT_CTRL);   
            Keyboard.press('g');
            Keyboard.releaseAll();
          }//hold
          
        }//switch
       } //elif mb2


     else if(mb3.update() == true)
       {
        switch(mb3.event())
        {
          case (tap) :
          Keyboard.press(KEY_LEFT_CTRL);   
          Keyboard.press('/');
          Keyboard.releaseAll();
          break;
    
          case (doubleTap):
          m1();
          break;
    
          case (hold):
          {
            while(mb3.read() == 0)
           {
            
              mb3.update();
           }//while held
          }//hold
          
        }//switch
       } //elif mb3
  
    else  //Simple Scroll
    {
       newPos = myEnc.read();
       if (newPos != position) 
       {  
   
         if(newPos>position)
         { 
            Mouse.move(0, 0, -1);
            Mouse.release();
         }
     
         else if(newPos<position)
         {
            Mouse.move(0, 0, 1);
            Mouse.release();
         }  
         position = newPos;
       }
     
    }//end else
 
 }//end while
}//end m3



void led(int a)
{ Serial.println(a);
  switch(a)
  {
    case 1:
      for(int i = 0; i <= 2; i++)
       { leds[i] = CRGB(255,200,170); FastLED.show(); }
       delay(10);
       break;

    case 2:
      for(int i = 0; i <= 2; i++)
        { leds[i] = CRGB(0,229,255); FastLED.show(); }
        delay(10);
        break;

    case 3:
      for(int i = 0; i <= 2; i++)
       { leds[i] = CRGB(124,252,0); FastLED.show(); }
       delay(10); 
       break;  
  }//end switch
}//end led
