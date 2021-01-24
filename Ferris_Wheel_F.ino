

# include <Stepper.h>
# include <LiquidCrystal.h>

const int pin_RS = 8;  //lcd pins 8 thru 10
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;
int buttons = 0; //buttons valued at zero
int passnum;  //number of passengers
int ticknum;  //number of tickets
int select;     // controls select button
float rides;    // number of rides 
int motorun = 1;  // motor will run while positive

LiquidCrystal lcd ( pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);  // assign lcd pins

const int stepsPerRevolution = 2038;  //One revolution of motor equals 2038 steps

Stepper myStepper(stepsPerRevolution,22,24,26,28);  //assigns stepper



void setup() {
  // put your setup code here, to run once:
  myStepper.setSpeed(6);  //set speed 6 rev per minute
lcd.begin(16,2);          //activate lcd screen
lcd.setCursor(0,0);       //set cursor 
lcd.print ("   Plahn   ");  //print welcome
lcd.setCursor(0,1);
lcd.print (" Entertainments ");

delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  {

  while (select != 1) {      //user information is retrieved while select does not equal one


  lcd.clear();

  buttons = analogRead(0);    //read the a0 pin
  lcd.setCursor (0,0);  //set lcd cursor
  lcd.print ("Tickets? ");   //ask user for information tickets
  lcd.setCursor (14,0);
  lcd.print ( ticknum);  //number of tickets
  lcd.setCursor (0,1);
  lcd.print ("Passengers? ");  //number of passengers?
  lcd.setCursor (14,1);
  lcd.print ( passnum);  
  

  if (buttons < 60) {    //right button
    ticknum = ticknum + 1;
  } 
  else if (buttons < 200) {  //up button
    passnum = passnum + 1;
  }
  else if (buttons < 400) {  //down button
    passnum = passnum - 1;
  }
  else if (buttons < 600) {  //left button
    ticknum = ticknum - 1;
  }
  else if (buttons < 800) {  //select button ends while loop when pushed
    select = 1;
  }
  
    delay(250);
  }
  }
    
  lcd.clear();  //clears lcd screen used to test rides output

  while (motorun == 1){  //motor should run during while loop
    lcd.setCursor(0,0);  //lcd for test of rides output
  
    rides = (ticknum / passnum * 2038);  //rides determined by dividing tickets by passengers
    round(rides);  //cannot have a fraction of a ride therefor round rides number
    lcd.print(rides);  //test print
 
    myStepper.step(rides);  //this turns the motor equal to the number of rides

    motorun = motorun - 1;  //shuts down motor loop

  }
  

     delay(200);  //probably not necessary may be removed later

   
    }
    
    
    
     
   
    
