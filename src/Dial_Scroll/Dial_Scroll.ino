#include <Keyboard.h>
#include <Mouse.h>
#define outputA 10
#define outputB 9
#define lclick 3
 int i = 0;
 int nc = 0;
 int flagf;
 int flagr;
 int seq[3];
 int counter = 0; 
 int aState; int bState;
 int aLastState;  
 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   
   //Serial.begin (9600);
   Keyboard.begin();
   Mouse.begin();
   aLastState = digitalRead(outputA); 
     
 } 
 void loop() { 
 
   //flagf = 0;
   //flagr = 0;
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   bState = digitalRead(outputB);

   

   if (aState != aLastState){    

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
    
     // Updates the previous state of the outputA with the current state
 //Serial.println(counter); 
 if (counter > nc)
    { 
     Keyboard.press(KEY_DOWN_ARROW);
     Keyboard.releaseAll();  
     //flagf = 0; 
    }

   else if(counter < nc)
   {
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.releaseAll(); 
    //flagr = 0;
    
   }

   nc = counter;
   aLastState = aState;
} //end aState

if (digitalRead(lclick) == HIGH)
{  
  Mouse.click();
  Mouse.release();
  delay(1000);
}

} //end loop
