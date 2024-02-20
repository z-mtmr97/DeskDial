#include <HID-Project.h>
#include <HID-Settings.h>
#include <JC_Button.h>
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
#include <FastLED.h>
//#include <Keyboard.h>
//#include <Mouse.h>
#define outputA 9
#define outputB 10
#define touch 3
#define button 2
#define NUM_LEDS 5
#define DATA_PIN 18


Encoder myEnc(outputA, outputB);
Button mb(button);
Button t(touch, 25, false, false);

boolean tlong;
boolean blong;
boolean playing = true;
boolean paused = false;
CRGB leds[NUM_LEDS];
long position  = -999;
long newPos;
int juna = -999;

 void setup() 
 { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   //pinMode (button, INPUT_PULLUP);
   
   //Serial.begin (9600);
   Keyboard.begin();
   Consumer.begin();
   Mouse.begin();
   //Remote.begin();
   mb.begin();
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
     for (int i=0; i<=4; i++ )
     {  leds[i] = CRGB::White;  FastLED.show(); }
   
 }//end Setup
 
 
 void msl()
 {
   int n = 0, nava; 
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
   
   switch(n)
   {
     case 1:
     //Serial.println("Mode 1");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB::White; FastLED.show(); }
     delay(50);
     mode1();
     break;
     
     case 2:
     //Serial.println("Mode 2");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(0,229,255); FastLED.show(); }
     delay(50);
     mode2();
     break;
     
     case 3:
     //Serial.println("Mode 3");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(124,252,0); FastLED.show(); }
     delay(50);
     mode3();
     break;
     
     case 4:
     //Serial.println("Mode 4");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(72,45,20); FastLED.show(); }
     delay(50);
     mode4();
     break;
     
     case 5:
     //Serial.println("Mode 5");
     for(int i = 0; i <= 4; i++)
     { leds[i] = CRGB(245,0,87); FastLED.show(); }
     delay(50);
     mode5();
     break; 
   }
 }//end msl

 
 void loop()
{ 
  mode1();
}//end loop




void readTouch(int a)
{ 
  t.read();
  if(t.isPressed())
  { 
    if(t.pressedFor(250))
    { 
      tlong = true;
      //Serial.println("Long Press");
      while(1)
        {
         t.read(); 
         long newPos = myEnc.read();
         if (newPos != position) 
         {
           if(newPos>position)
           {  
               Consumer.write(MEDIA_VOLUME_DOWN);
              /* Remote.decrease();
               Remote.clear();*/
               //Serial.println(" VI");
           }
       
           else if(newPos<position)
           {
              Consumer.write(MEDIA_VOLUME_UP);
               /*Remote.increase();
               Remote.clear();*/
               //Serial.println(" VD");
           }
   
          position = newPos;
          
         }//end roll
         
         mb.read();
         if(mb.wasPressed())    //Press While LongTouch (Touch+Press)
         {  switch(a)
            {
              case 1:
              break;

              case 2:
                Keyboard.press(KEY_LEFT_CTRL);
                Keyboard.press('/');
                Keyboard.releaseAll();
                //Serial.println("ctrl+Slash");
              break;

              case 3:
                Keyboard.press(KEY_LEFT_CTRL);
                Keyboard.press('.');
                Keyboard.releaseAll();
                //Serial.println("Ctrl+.");
              break;
            }
           //Serial.println("PresswhileTouched");
         }//end button press while touch
                  
         if (!t.isPressed())
         break;

      }//while
      
    }
  }
  
  else  //Single Touch
  {
  
    if(t.wasReleased())
    {
      switch(a)
      { 
        case 1:
          Mouse.click();
          break;
         
        case 2: 
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('s');
          Keyboard.releaseAll();	
          //Serial.println("Save");  
          break;
          
        case 3:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('/');
          Keyboard.releaseAll();  
          //Serial.println("slash");
          break;

         
      }//end switch        
    }
  } //end SingleTouch
}//end readtouch



/******************
Functions For Modes
*******************/



void mode1()
{ 
  while(1)
  {
   mb.read();
   if(mb.isPressed())
   {
     if(mb.pressedFor(500))
     {
       msl();    
     }
   }
   
   else if(mb.wasReleased())
   {
     //Single Press
   }
      
   else
   { 
     newPos = myEnc.read();
     if (newPos != position) 
     {  
      //Serial.println(position);
       if(newPos>position)
       { 
         Mouse.move(0, 0, -1);
         Mouse.release();
         /*Keyboard.press(KEY_DOWN_ARROW); 
         Keyboard.releaseAll();*/
       }
   
       else if(newPos<position)
       {
          Mouse.move(0, 0, 1);
          Mouse.release();
         /*Keyboard.press(KEY_UP_ARROW); 
         Keyboard.releaseAll();*/
       }  
      position = newPos;
     }
   
     readTouch(1);
   }
   
  }
  
}//end mode1


void mode2()  //PS
{ 
   while(1)
  {
   mb.read();
   if(mb.isPressed())
   {
     if(mb.pressedFor(500))
     {
       msl();    
     }
   }
   
   else if(mb.wasReleased())  //SinglePress
   {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('.');
    Keyboard.releaseAll(); 
    //Serial.println("Brightness");   
    }
      
   else  //Simple Scroll
   { 
     newPos = myEnc.read();
     if (newPos != position) 
     {  
      //Serial.println(position);
       if(newPos>position)
       { 
         Keyboard.press(KEY_RIGHT_ALT);
         Mouse.move(0, 0, 1);
         Mouse.release();
         Keyboard.releaseAll();
         //Serial.println("Zoom Out");
       }
   
       else if(newPos<position)
       {
         Keyboard.press(KEY_RIGHT_ALT);
         Mouse.move(0, 0, -1);
         Mouse.release();
         Keyboard.releaseAll();
         //Serial.println("Zoom in");
       }  
      position = newPos;
     }
   
     readTouch(2);
   }
   
  }
  
}//end mode2


void mode3()  //CorelDraw
{
  //Serial.println("Mode 3");
 while(1)
  {
   mb.read();
   if(mb.isPressed())
   {
     if(mb.pressedFor(500))
     {
       msl();    
     }
   }
   
   else if(mb.wasReleased())  //Simple Press
   {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('s');
    Keyboard.releaseAll(); 
    //Serial.println("Save");   
   }
      
   else   //Simple Scroll
   {  
     newPos = myEnc.read();
     if (newPos != position) 
     {  
      //Serial.println(position);
       if(newPos>position)
       { 
         //Keyboard.press(KEY_RIGHT_ALT);
         Mouse.move(0, 0, 1);
         Mouse.release();
         //Keyboard.releaseAll();
         //Serial.println("Z Out");
       }
   
       else if(newPos<position)
       {
         //Keyboard.press(KEY_RIGHT_ALT);
         Mouse.move(0, 0, -1);
         Mouse.release();
         //Keyboard.releaseAll();
         Serial.println("Z in");
       }  
      position = newPos;
     }
   
     readTouch(3);
   }
   
  } 
}//end mode3


void mode4()
{
}//end mode4


void mode5()
{
}//end mode5
