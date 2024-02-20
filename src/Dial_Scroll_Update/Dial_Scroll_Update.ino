#include <FastLED.h>
#include <Keyboard.h>
#include <Mouse.h>
#define outputA 7 
#define outputB 16
#define button 5
#define dub 4 
#define NUM_LEDS 5
#define DATA_PIN 3

 int i = 0;
 int nc = 0;
 int flagf;
 int flagr;
 int seq[3];
 int counter = 0; 
 int ctr = 0;
 int nctr = 0;
 int aState; int bState;
 int aLastState; 
 long buttonTimer = 0;
 long longPressTime = 250;
 boolean buttonActive = false;
 boolean longPressActive = false; 
 CRGB leds[NUM_LEDS];

 
 void setup() 
 { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   pinMode (dub, INPUT_PULLUP);
   
   Serial.begin (9600);
   Keyboard.begin();
   Mouse.begin();
   aLastState = digitalRead(outputA);
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);    
 } 
 
 
 void loop() 
{  
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
   //flagf = 0;
   //flagr = 0;
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   bState = digitalRead(outputB);

   if (aState != aLastState)
   {    

     if (digitalRead(outputB) != aState) 
     { 
       counter ++;  
       //Serial.print("F - "); Serial.print(counter); Serial.println("");
       seq[i] = 1; 
      
     } 
     
     else
     {
       counter --; 
       //Serial.print("::::R"); Serial.print(counter);Serial.println(""); //Serial.println(aLastState);
       seq[i] = 0;  
     }

    
    /*if(i<3)
    { 
      Serial.print(i);  Serial.print("--");
      Serial.print(seq[i]);  Serial.println();
      i++;
    } 
     
     else
    {   i = 0;
    
        if((seq[0] == 1) && (seq[1] == 1) && (seq[2] == 1))
        {
          Serial.print("F");  Serial.println();
          flagr = 0;
          flagf = 1;
          //Keyboard.press(KEY_DOWN_ARROW);
          //Keyboard.releaseAll(); 
        }
   
        if((seq[0] == 0) && (seq[1] == 0) && (seq[2] == 0))
        {
          Serial.println("----R");  Serial.println();
          flagf = 0;
          flagr = 1; 
          //Keyboard.press(KEY_UP_ARROW);
          //Keyboard.releaseAll();
        }
     
    }*/

   if (counter > nc)
    { 
     Keyboard.press(KEY_DOWN_ARROW);
     Keyboard.releaseAll();  
     //Serial.println("Scrol U");
     //flagf = 0; 
    //Serial.println(counter);
    }

   else if(counter < nc)
   {
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.releaseAll();
    //Serial.println("Scrol ------D");
    //flagr = 0;
    //Serial.println(counter);
    
   }

   nc = counter;
   aLastState = aState;
} //end aState



//----------------------------------------//
//-------------Read Button----------------//
//----------------------------------------//



if (digitalRead(button) == HIGH)
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
        aState = digitalRead(outputA); 
        bState = digitalRead(outputB);
        if (aState != aLastState)
        {
              if (digitalRead(outputB) != aState) 
             { 
               ctr ++;  
             } 
     
             else
             {  
                ctr --; 
             }
         
             if (ctr > nctr)
             {
               Remote.decrease();
               Remote.clear();
               Serial.println(" VI");
             }
           
             else if (ctr < nctr)
             {
               Remote.increase();
               Remote.clear();
               Serial.println(" VU");
             }
         
        }
       
       nctr = ctr;
       aLastState = aState;
       
       
       if (digitalRead(button) == LOW)
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

} //else


/*if(digitalRead(dub) == LOW)
{

    Keyboard.press(KEY_LEFT_GUI);
    //Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('F');
    Keyboard.releaseAll();
    delay(100);

}*/

} //end loop
