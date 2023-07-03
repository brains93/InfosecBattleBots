//libs

#include <Stepper.h>

//Control pins
const int Button_Start = 53;
const int Button_Stop = 52;
const int Button_Pit_up = 51;
const int Button_Pit_Down = 50;
const int Button_spinner_1 = 49;
const int Button_spinner_1_counter = 48;
const int Button_Spinner_1_Low = 47;
const int Button_Spinner_1_High = 46;
const int Button_spinner_2 = 45;
const int Button_spinner_2_counter = 44;
const int Button_Spinner_2_Low = 43;
const int Button_Spinner_2_High = 42;
const int Button_spinner_3 = 41;
const int Button_spinner_3_counter = 40;
const int Button_Spinner_3_Low = 39;
const int Button_Spinner_3_High = 38;
const int Button_Flipper = 7;


//Outputs 
const int Spinner_1_out = 22;
const int Spinner_1_out_counter = 23;                                                        
const int Spinner_2_out = 24;
const int Spinner_2_out_counter = 25;
const int Spinner_3_out = 26;
const int Spinner_3_out_counter = 27;
const int FLipper_Out = 28;
const int CS1 = 29;
const int UD1 = 30;
const int INC1 = 31;
const int CS2 = 32;
const int UD2 = 33;
const int INC2 = 33; 
const int CS3 = 35,
const int UD3 = 36;
const int INC3 = 37;

// variables 
byte Active = LOW; //has the start button been hit 
byte Weapons_Enabled = LOW; //whether the weapons are on 
byte Flipper_Fire = LOW; //Whether to fire the flipper  

int StepsRequired  =  2048 ; // 2048 per 360 this is the movemet for the pit 

unsigned long Start_millis = 0; // start time when the start button is prossed 

const float STEPS_PER_REV = 32; //steps per rev 
const float GEAR_RED = 64; // gear reduction 
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED; //output steps 

Stepper Pit_Stepper = Stepper(STEPS_PER_REV, 8, 10, 9, 11);


void setup() {
  // Inputs
  pinMode(Button_Start, INPUT_PULLUP);
  pinMode(Button_Stop, INPUT_PULLUP);
  pinMode(Button_Pit_up, INPUT_PULLUP);
  pinMode(Button_Pit_Down, INPUT_PULLUP);
  pinMode(Button_spinner_1, INPUT_PULLUP);
  pinMode(Button_spinner_1_counter, INPUT_PULLUP);
  pinMode(Button_spinner_1_Low, INPUT_PULLUP);
  pinMode(Button_spinner_1_High, INPUT_PULLUP);
  pinMode(Button_spinner_2, INPUT_PULLUP);
  pinMode(Button_spinner_2_counter, INPUT_PULLUP);
  pinMode(Button_spinner_2_Low, INPUT_PULLUP);
  pinMode(Button_spinner_2_High, INPUT_PULLUP);
  pinMode(Button_spinner_3, INPUT_PULLUP);
  pinMode(Button_spinner_3_counter, INPUT_PULLUP);
  pinMode(Button_spinner_3_Low, INPUT_PULLUP);
  pinMode(Button_spinner_3_High, INPUT_PULLUP);
  pinMode(Button_Flipper, INPUT_PULLUP);
  pinMode(Limit_up, INPUT_PULLUP);
  pinMode(Limit_down, INPUT_PULLUP);

  //outputs 
  pinMode(Spinner_1_out, OUTPUT);
  pinMode(Spinner_1_out_counter, OUTPUT);
  pinMode(Spinner_2_out, OUTPUT);
  pinMode(Spinner_2_out_counter, OUTPUT);
  pinMode(Spinner_3_out, OUTPUT);
  pinMode(Spinner_3_out_counter, OUTPUT);
  pinMode(FLipper_Out, OUTPUT);
  pinMode(CS1, OUTPUT);
  pinMode(UD1, OUTPUT);
  pinMode(INC1, OUTPUT);
  pinMode(CS2, OUTPUT);
  pinMode(UD2, OUTPUT);
  pinMode(INC2, OUTPUT); 
  pinMode(CS3, OUTPUT);
  pinMode(UD3, OUTPUT);
  pinMode(INC3, OUTPUT); 
}  

void loop() {

  Serial.begin(9600);
  
  // Functions go here 

  readButton();               
  Timer();
  Flipper();
  Pit();
}

void readButton() {
  if (digitalRead(Button_Start) == HIGH) {  // Start button fires the 
    Active = HIGH;
    Start_millis = millis();   // capture the latest value of millis()
  }
  if (digitalRead(Button_Stop) == HIGH) {  // Start button fires the 
    Active = LOW;
    Weapons_Enabled = LOW; 
    Start_millis = 0;
    digitalWrite(Spinner_1_out,LOW);
    digitalWrite(Spinner_1_out_counter,LOW);
    digitalWrite(Spinner_2_out,LOW);
    digitalWrite(Spinner_2_out_counter,LOW);
    digitalWrite(Spinner_3_out,LOW);
    digitalWrite(Spinner_3_out_counter,LOW);
  }
  if (digitalRead(Button_Pit_up ) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      steppermotor.setSpeed(1);    
      steppermotor.step(StepsRequired); 
    }
  } 
  if (digitalRead(Button_Pit_Down ) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      steppermotor.setSpeed(1);    
      steppermotor.step(-StepsRequired); 
    }
  } 
  if (digitalRead(Button_spinner_1) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(Spinner_1_out_counter,LOW);
      digitalWrite(Spinner_1_out,HIGH);
    }
  } 
  if (digitalRead(Button_spinner_1_counter) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(Spinner_1_out,LOW);
      digitalWrite(Spinner_1_out_counter,HIGH);
    }
  } 
  if (digitalRead(Button_Spinner_1_Low) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(CS1,LOW);
      digitalWrite(UD1,LOW);
      digitalWrite(INC1,HIGH);

      delay(50);
      digitalWrite(INC1,LOW);
    }
  }
  if (digitalRead(Button_Spinner_1_High) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(CS1,LOW);
      digitalWrite(UD1,HIGH);
      digitalWrite(INC1,HIGH);

      delay(50);
      digitalWrite(INC1,LOW);
    }
  } 
  if (digitalRead(Button_spinner_2) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(Spinner_2_out_counter,LOW);
      digitalWrite(Spinner_2_out,HIGH);
    }
  }
  if (digitalRead(Button_spinner_2_counter) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(Spinner_2_out,LOW);
      digitalWrite(Spinner_2_out_counter,HIGH);
    }
  }
  if (digitalRead(Button_Spinner_2_Low) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(CS2,LOW);
      digitalWrite(UD2,LOW);
      digitalWrite(INC2,HIGH);

      delay(50);
      digitalWrite(INC2,LOW);
    }
  }
  if (digitalRead(Button_Spinner_2_High) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(CS2,LOW);
      digitalWrite(UD2,HIGH);
      digitalWrite(INC2,HIGH);

      delay(50);
      digitalWrite(INC2,LOW);
    }
  }
  if (digitalRead(Button_spinner_3) == HIGH) {  // Start button fires the 
    if (Weapons_Enabled == HIGH) {
      digitalWrite(Spinner_3_out_counter,LOW);
      digitalWrite(Spinner_3_out,HIGH);    }
  }  
  if (digitalRead(Button_spinner_3_counter) == HIGH) {  //  
    if (Weapons_Enabled == HIGH) {
      digitalWrite(Spinner_3_out,LOW);
      digitalWrite(Spinner_3_out_counter,HIGH); 
    } 
  }
  if (digitalRead(Button_Spinner_3_Low) == HIGH) {  
    if (Weapons_Enabled == HIGH) {
      digitalWrite(CS3,LOW);
      digitalWrite(UD3,LOW);
      digitalWrite(INC3,HIGH);

      delay(50);
      digitalWrite(INC3,LOW);
    }
  }
  if (digitalRead(Button_Spinner_3_High) == HIGH) {  
    if (Weapons_Enabled == HIGH) {
      digitalWrite(CS3,LOW);
      digitalWrite(UD3,HIGH);
      digitalWrite(INC3,HIGH);

      delay(50);
      digitalWrite(INC3,LOW);
    }
  }
  if (digitalRead(Button_spinner_3_counter) == HIGH) { 
    if (Weapons_Enabled == HIGH) {
    Flipper_Fire = High;   
    } 
  }
}

void Timer() {
  if (Active == High) {         
    if (currentMillis != 0) {    
      if (currentMillis - millis() >= 33000) {
        Weapons_Enabled = HIGH;
      }
      if (currentMillis - millis() >= 183000) {
        Weapons_Enabled = LOW;
        Active = LOW 
      }
   }
  }
}

void Flipper() {
   if (Flipper_Fire == HIGH) {
        if (Weapons_Enabled == HIGH) {
        digitalWrite(FLipper_Out,HIGH);
        delay(50);
        digitalWrite(FLipper_Out,LOW);
      }
    }
  }





