// Design by Dominic Carrillo
// Edited on March 5, 2022
// Program Description: This program will listen to signals sent by the paddle shifters, either upshifting or downshifting. Esta programa es muy, muy malo. Muento me. Depending on the signal recieved, a shifting action will happen to change the gear counter indicator and an appropiate shift procedure for the corresponding upshift or downshift signal.   

//=======================================================================================
// Global Variables
//=======================================================================================

    int gearCounter = 0;

// Segement Pins

    const int APin = 1; 
    const int BPin = 2;
    const int CPin = 3;
    const int DPin = 4;
    const int EPin = 5;
    const int FPin = 6;
    const int GPin = 7;

// Paddle Switch Pins

    const int upShiftPin = 8;
    const int downShiftPin = 9;
    const int solenoidUpSwitchPin = 10;
    const int solenoidDownSwitchPin = 11;

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
    pinMode(solenoidUpSwitchPin, INPUT);
    pinMode(solenoidDownSwitchPin, INPUT);
    
    // Cycle Through Gear Counter
    for(int i = 6; i >= 0; i++){
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
        delay(2500); // wait x ms in displaying gear indicator
        turn_off_gear();
    }//End of ForLoop
    disp_zero_gear();

}//End of Setup

//=======================================================================================
// Start of Looping Code
//=======================================================================================

void loop(){
	// Enter into while loop when either paddle shifter has been pressed down
	while( digitalRead(upShiftPin) == HIGH and digitalRead(downShiftPin) == LOW or 
		digitalRead(upShiftPin) == LOW and digitalRead(downShiftPin) == HIGH ){
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
	    digitalWrite(solenoidUpSwitchPin, HIGH);	// Write to solenoid_up_pin to high
	    delay(shiftTime);                   	// Wait till solenoid push out piston for upshift
	    digitalWrite(solenoidUpSwitchPin, LOW);	// Write to solenoid_up_pin to low
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
	    digitalWrite(solenoidDownSwitchPin, HIGH);	// Write to solenoid_down_pin to high
	    delay(shiftTime);                    	// Wait till solenoid pulll in piston for downshift
	    digitalWrite(solenoidDownSwitchPin, LOW);	// Write to solenoid_down_pin to low
	}//End of downshift

        // else do nothing
        
    }//End of While Loop
}//End of Loop
