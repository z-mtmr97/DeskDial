#include <Keyboard.h>
#define outputA 2
#define outputB 3
 int i = 0;
 int flagf;
 int flagr;
 int counter = 0; 
 int nc = 0;
 int aState; int bState;
 int aLastState;  
 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   
   Serial.begin (9600);
   Keyboard.begin();
   aLastState = digitalRead(outputA); 
     
 } 
 void loop() { 
   int seq[3]; 
 
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

    if(counter > nc)
    {
      Remote.increase();
      Remote.clear();
    }
    
    else if (counter < nc)
    {
      Remote.decrease();
      Remote.clear();
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
    
    nc = counter;
    aLastState = aState; // Updates the previous state of the outputA with the current state
    
/* if (flagf)
    { 
     Keyboard.press(KEY_DOWN_ARROW);
     //delay(10);
     Keyboard.releaseAll();  
     //flagf = 0; 
    }

   else if(flagr)
   {
    Keyboard.press(KEY_UP_ARROW);
    //delay(10);
    Keyboard.releaseAll(); 
    //flagr = 0;
    
   }*/

   
} //end aState

} //end loop
