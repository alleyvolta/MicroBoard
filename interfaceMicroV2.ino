//
//
//

//lib includes

//constants: pin variable decleration
const int switchUp = 2;   //(OFF) Acts to switch between Off/Standby mode
const int switchDown = 4; //(ON)  Acts to switch between Off/Standby mode
const int buttonOne = 5;  //Acts to switch between Start/Stop
const int buttonTwo = 6;  //Acts to switch between Emulate/Record mode
const int blueLED = 7;    //Standby indicator light
const int whiteLED = 8;   //Start indicator light 
const int buzzer = 9;     //Button press audio element 
const int redLED = 10;    //Record indicator light
const int greenLED = 13;  //Emulate indicator light

//variable decleration
int lagTime = 250;
int delayTime = 5000;
int buzzerDuration = 100;
int keyValueIndex = 0;
int pos = 0;
unsigned int buzzerOffFrequency = 5000;
unsigned int buzzerOnFrequency = 3000;
unsigned int buzzerEmulateFrequency = 4000;
unsigned int buzzerRecordFrequency = 6000;
long startTime = 0;
long endTime = 0;
char keyValue[12];
char inChar;
boolean modeState = false;
boolean runState = false;
boolean buttonState =false;

//
void insertValue(char inChar,int pos);

void setup() {
  pinMode(buttonOne,INPUT);
  pinMode(buttonTwo,INPUT);
  pinMode(switchUp,INPUT);
  pinMode(switchDown,INPUT);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(whiteLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}

void loop() {
    //On tone
    if(digitalRead(switchDown)==HIGH){
    digitalWrite(blueLED, HIGH);  
    tone(buzzer,buzzerOnFrequency,buzzerDuration); 
    Serial.println("System is standing by.");
    }
  
    //On loop
    while(digitalRead(switchDown)==HIGH){
    
    //Check button One
    if(digitalRead(buttonOne)==LOW){
    buttonState=true;  
    //State change between Emulate and Record
    if(modeState == true){
    tone(buzzer,buzzerRecordFrequency,buzzerDuration);
    modeState=false;
    runState=false;
    digitalWrite(whiteLED, LOW);
    Serial.println("System is in Recording mode.");
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW); 
    delay(lagTime);
    }else if(modeState == false){
    tone(buzzer,buzzerEmulateFrequency,buzzerDuration);
    modeState=true;    
    runState=false;
    digitalWrite(whiteLED, LOW);
    Serial.println("System is in Emulation mode.");  
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    delay(lagTime);
    }     
    }
    
    //Check button Two
    if(digitalRead(buttonTwo)==LOW&&buttonState==true){
    //State change between Start and Stop
    if(runState == true){
    tone(buzzer,buzzerOffFrequency,buzzerDuration);
    runState=false;
    if(pos!=0){
    Serial.println("Data Recorded.");  
    }
    pos = 0;
    digitalWrite(whiteLED, LOW);
    Serial.println("System Stop.");
    delay(lagTime);
    }else if(runState == false){
    tone(buzzer,buzzerOnFrequency,buzzerDuration);
    runState=true;    
    digitalWrite(whiteLED, HIGH);
    Serial.println("System Start.");  
    delay(lagTime);
    }     
    }  
    // /*
    //initializes keyboard read/write
    // 
    if(runState==true&&modeState==true){
      //begins keyboard emulation
      Keyboard.begin();
      //keyboard write loop
      for(keyValueIndex = 0;keyValueIndex<12;keyValueIndex++){
      //presses the next key in the keyValue list
      Keyboard.write(keyValue[keyValueIndex]);
      }
      //ends keyboard emulation
      Keyboard.end();
      //
    
    }
    else if(runState==true&&modeState==false){
      
      // check for incoming serial data:
      if (Serial.available() > 0) {  
        // read incoming serial data:
        inChar = Serial.read();
        delay(25);
        if(pos<12){
        // 
        insertValue(inChar,pos); 
        pos++;   
        delay(5);  
        } else if (pos=12){
        //  
        pos=0; 
        insertValue(inChar,pos);      
        pos++;
        delay(5);
        }  
    
    } 
      
    }
    // */
    
    }
    //END of while loop
      

    //Off tone
    if(digitalRead(switchUp)==HIGH){
    tone(buzzer,buzzerOffFrequency,buzzerDuration); 
    Serial.println("System Off.");
    digitalWrite(blueLED, LOW); 
    digitalWrite(redLED, LOW); 
    digitalWrite(greenLED, LOW); 
    digitalWrite(whiteLED, LOW); 
    modeState = false;
    runState = false;
    buttonState = false;
    delay(lagTime);
    }
    
    //Off loop
    while(digitalRead(switchUp)==HIGH){
    delay(100);  
    }
}

void insertValue(char inChar,int pos){
  keyValue[pos] = inChar;
  
}

//OUTPUT
/*
System is standing by.

System is in Emulation mode.

System is in Recording mode.

System Start.

System is in Emulation mode.

System Start.

System Off.

System is standing by.

System is in Emulation mode.

System is in Recording mode.

System is in Emulation mode.

System Start.

System Stop.

System is in Recording mode.

System Start.

System Stop.

System Start.

System is in Emulation mode.

System Start.

System Off.
*/

