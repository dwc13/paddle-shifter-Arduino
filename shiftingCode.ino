// Design by Dominic Carrillo and used by ya boi
// Edited on April 16th, 2022
// Program Description: This program will listen to signals sent by the paddle shifters, either upshifting or downshifting. Esta programa es muy, muy malo. Muento me. Depending on the signal recieved, a shifting action will happen to change the gear counter indicator and an appropiate shift procedure for the corresponding upshift or downshift signal.   

//=======================================================================================
// Global Variables
//=======================================================================================

  int gearCounter = 0;

// Segement Pins

  int APin = 22; 
  int BPin = 24;
  int CPin = 26;
  int DPin = 28;
  int EPin = 30;
  int FPin = 32;
  int GPin = 34;

// Paddle Switch Pins

  int upShiftPin = 23;
  int downShiftPin = 25;
  int solenoidUpSwitchPin = 8;
  int solenoidDownSwitchPin = 9;

// Configurable Variables

  // Delay time for when the solenoid will engage then to disengage 
  int shiftTime = 500; // in ms

//=======================================================================================
// Helper Functions
//=======================================================================================

// Gear Counter Functions
//---------------------------------------------------------------------------------------
// Display 0 on Segment Display from Truth Table
void disp_zero_gear(){
  digitalWrite(APin, HIGH);
  digitalWrite(BPin, HIGH);
  digitalWrite(CPin, HIGH);
  digitalWrite(DPin, HIGH);
  digitalWrite(EPin, HIGH);
  digitalWrite(FPin, HIGH);
  digitalWrite(GPin, LOW);
}
// Display 1 on Segment Display from Truth Table
void disp_first_gear(){
  digitalWrite(APin, LOW);
  digitalWrite(BPin, HIGH);
  digitalWrite(CPin, HIGH);
  digitalWrite(DPin, LOW);
  digitalWrite(EPin, LOW);
  digitalWrite(FPin, LOW);
  digitalWrite(GPin, LOW);
}
// Display 2 on Segment Display from Truth Table
void disp_second_gear(){
  digitalWrite(APin, HIGH);
  digitalWrite(BPin, HIGH);
  digitalWrite(CPin, LOW);
  digitalWrite(DPin, HIGH);
  digitalWrite(EPin, HIGH);
  digitalWrite(FPin, LOW);
  digitalWrite(GPin, HIGH);
}
// Display 3 on Segment Display from Truth Table
void disp_third_gear(){
  digitalWrite(APin, HIGH);
  digitalWrite(BPin, HIGH);
  digitalWrite(CPin, HIGH);
  digitalWrite(DPin, HIGH);
  digitalWrite(EPin, LOW);
  digitalWrite(FPin, LOW);
  digitalWrite(GPin, HIGH);
}
// Display 4 on Segment Display from Truth Table
void disp_fourth_gear(){
  digitalWrite(APin, LOW);
  digitalWrite(BPin, HIGH);
  digitalWrite(CPin, HIGH);
  digitalWrite(DPin, LOW);
  digitalWrite(EPin, LOW);
  digitalWrite(FPin, HIGH);
  digitalWrite(GPin, HIGH);
}
// Display 5 on Segment Display from Truth Table
void disp_fifth_gear(){
  digitalWrite(APin, HIGH);
  digitalWrite(BPin, LOW);
  digitalWrite(CPin, HIGH);
  digitalWrite(DPin, HIGH);
  digitalWrite(EPin, LOW);
  digitalWrite(FPin, HIGH);
  digitalWrite(GPin, HIGH);
}
// Display 6 on Segment Display from Truth Table
void disp_sixth_gear(){
  digitalWrite(APin, HIGH);
  digitalWrite(BPin, LOW);
  digitalWrite(CPin, HIGH);
  digitalWrite(DPin, HIGH);
  digitalWrite(EPin, HIGH);
  digitalWrite(FPin, HIGH);
  digitalWrite(GPin, HIGH);
}
// Turn Off Segment Display from Truth Table
void turn_off_gear(){
  digitalWrite(APin, LOW);
  digitalWrite(BPin, LOW);
  digitalWrite(CPin, LOW);
  digitalWrite(DPin, LOW);
  digitalWrite(EPin, LOW);
  digitalWrite(FPin, LOW);
  digitalWrite(GPin, LOW);
}
// Turn Off Segment Display from Truth Table
void disp_f_gear(){
  digitalWrite(APin, HIGH);
  digitalWrite(BPin, LOW);
  digitalWrite(CPin, LOW);
  digitalWrite(DPin, LOW);
  digitalWrite(EPin, HIGH);
  digitalWrite(FPin, HIGH);
  digitalWrite(GPin, HIGH);
}
//=======================================================================================
// Initializing of all pins on Arduino Board
//=======================================================================================

void setup(){ 
  // Segment Pin Mode
  pinMode(APin, OUTPUT); 
  pinMode(BPin, OUTPUT); 
  pinMode(CPin, OUTPUT); 
  pinMode(DPin, OUTPUT); 
  pinMode(EPin, OUTPUT); 
  pinMode(FPin, OUTPUT); 
  pinMode(GPin, OUTPUT);

  // Gear Switch Pin Mode
  pinMode(upShiftPin, INPUT); 
  pinMode(downShiftPin, INPUT); 
  pinMode(solenoidUpSwitchPin, OUTPUT);
  pinMode(solenoidDownSwitchPin, OUTPUT);
    
  // Cycle Through Gear Counter
  for(int i = 0; i < 7; ++i){
      switch(i){
          case 0:
              disp_zero_gear();
              break;
          case 1:
              disp_first_gear();
              break;
          case 2:
              disp_second_gear();
              break;
          case 3:
              disp_third_gear();
              break;
          case 4:
              disp_fourth_gear();
              break;
          case 5:
              disp_fifth_gear();
              break;
          case 6:
              disp_sixth_gear();
              break;
      }//End of Switch Case
      delay(500); // wait x ms in displaying gear indicator
      turn_off_gear();
  }//End of ForLoop

  // F for respect
  for(int i = 0; i < 8; i++){
      disp_f_gear();
      delay(500);
      turn_off_gear();
      delay(500);
  }
  disp_f_gear();
  delay(1500);
  turn_off_gear();
  delay(500); 
  disp_zero_gear();
  
}//End of Setup

//=======================================================================================
// Start of Looping Code
//=======================================================================================

void loop(){
  // When the user pressed down the up shift paddle
  if ( digitalRead(upShiftPin) == HIGH ){
    // Increase Gear Counter
    switch(gearCounter+1){
      case 1:
        disp_first_gear();
        gearCounter++;
        break;
      case 2:
        disp_second_gear();
        gearCounter++;
        break;
      case 3:
        disp_third_gear();
        gearCounter++;
        break;
      case 4:
        disp_fourth_gear();
        gearCounter++;
        break;
      case 5:
       disp_fifth_gear();
       gearCounter++;
       break;
      case 6:
        disp_sixth_gear();
        gearCounter++;
        break;
    }//End of Switch Case

    // Engage Solenoid to UpShift
    digitalWrite(solenoidUpSwitchPin, HIGH);  // Write to solenoid_up_pin to high
    delay(shiftTime);                         // Wait till solenoid push out piston for upshift
    digitalWrite(solenoidUpSwitchPin, LOW);   // Write to solenoid_up_pin to low

    // While loop till button has been released
    while ( digitalRead(upShiftPin) == HIGH)
    {
        // Do nothing till release
    }
  }//End of upshift

  // When the user pressed down the down shift paddle
  else if ( digitalRead(downShiftPin) == HIGH ){
    // Decrease Gear Counter
    switch(gearCounter-1){
      case 0:
        disp_zero_gear();
        gearCounter--;
        break;
      case 1:
        disp_first_gear();
        gearCounter--;
        break;
      case 2:
        disp_second_gear();
        gearCounter--;
        break;
      case 3:
        disp_third_gear();
        gearCounter--;
        break;
      case 4:
        disp_fourth_gear();
        gearCounter--;
        break;
      case 5:
        disp_fifth_gear();
        gearCounter--;
        break;
      }//End of Switch Case

      // Engage Solenoid to Downshift
      digitalWrite(solenoidDownSwitchPin, HIGH);  // Write to solenoid_down_pin to high
      delay(shiftTime);                    	      // Wait till solenoid pulll in piston for downshift
      digitalWrite(solenoidDownSwitchPin, LOW);	  // Write to solenoid_down_pin to low

      // While loop till button has been released
      while ( digitalRead(downShiftPin) == HIGH)
      {
          // Do nothing till release
      }
  }//End of downshift
}//End of Loop
