#include <dht.h> //For Temperature and Humididty Sensor
#include <LiquidCrystal.h> //LCD Screenhttps://github.com/NathanKong06/Arduino-Fan-with-Speed-Adjustment/blob/main/MainProject.ino

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const int setTemp = 23; //Set Temperature

LiquidCrystal lcd(8,9,10,11,12,13); //LCD
dht DHT; //For Temperature and Humididty Sensor
const unsigned short tasksNum = 2; // Number of Tasks
task tasks[tasksNum];
unsigned int fanSpeed = 170;
const unsigned long fanPeriod = 1000;
//const unsigned long buzzerPeriod = 1000;
const unsigned long buttonPeriod = 100;
unsigned int fanFlag;

enum States {start, FanOff, FanOn} state;
enum BuzzerStates {bstart, NoTune, PlayTune, Hold} bstate;
enum ButtonStates {buttonStart,noButton, button, buttonHold} buttonState;

void setup() {
  pinMode(3, OUTPUT); //Fan
  pinMode(4, OUTPUT); //Fan
  pinMode(5, OUTPUT); //Fan (Enable)
  //pinMode(8, OUTPUT); //Buzzer
  pinMode(2, OUTPUT); //Button 1
  pinMode(6, OUTPUT); //Button 2
  digitalWrite(2, HIGH); //Set up Button
  digitalWrite(6, HIGH); //Set up Button
  Serial.begin(9600); //Temperature
  fanFlag = 0;
  lcd.begin(16,2); //Set up LCD

  unsigned char i = 0;
  tasks[i].state = start;
  tasks[i].period = fanPeriod;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Fan;
  ++i;
  /*tasks[i].state = bstart;
  tasks[i].period = buzzerPeriod;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Buzzer; 
  ++i;*/
  tasks[i].state = buttonStart;
  tasks[i].period = buttonPeriod;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Buttons;
}

int Fan(int state) {
  int chk = DHT.read11(7); //Initialize Sensor
  switch (state) {
    case start:
      state = FanOff;
      break;
    case FanOff:
      Serial.print("FanOff:");
      Serial.println(DHT.temperature);
      lcd.setCursor(0,0);
      lcd.print("Temp:");
      lcd.print(static_cast<int>(DHT.temperature));
      lcd.print("C Fan:Off");
      lcd.setCursor(0,1);
      lcd.print("Humidity:");
      lcd.print(static_cast<int>(DHT.humidity));
      lcd.print("%");
      if (DHT.temperature >= setTemp) {
        delay(250);
        lcd.clear();
        state = FanOn;
      }
      else
        state = FanOff;
      break;
    case FanOn:
      Serial.print("FanOn: ");
      Serial.println(DHT.temperature);
      lcd.setCursor(0,0);
      lcd.print("Temp:");
      lcd.print(static_cast<int>(DHT.temperature));
      lcd.print("C Fan:On");
      lcd.setCursor(0,1);
      lcd.print("Fan Speed:");
      lcd.print(fanSpeed);
      if (DHT.temperature >= setTemp)
        state = FanOn;
      else {
        state = FanOff;
        delay(250);
        lcd.clear();
      }
      break;
    default:
      break;
  }

  switch (state) {
    case FanOff:
      analogWrite(5, LOW); //Enable Off
      fanFlag = 0;
      break;
    case FanOn:
      analogWrite(5, fanSpeed); //Enable On
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      fanFlag = 1; // Indicates Fan is On
      break;
    default:
      break;
  }
  return state;
}

/*int Buzzer(int bstate) {
  switch (bstate) {
    case bstart:
      bstate = NoTune;
      break;
    case NoTune:
    if (fanFlag)
      bstate = PlayTune;
    else
      bstate = NoTune;
    break;
    case PlayTune:
    if (fanFlag)
     bstate = Hold;
    else
      bstate = NoTune;
    break;
    case Hold:
      if (fanFlag)
        bstate = Hold;
      else {
        bstate = NoTune;
        tone(8, 392); //Play Melody (Hz) 
        delay(250); //Holds Tone for this duration
        tone(8, 349); 
        delay(250);
        tone(8, 329); 
        delay(250);
        tone(8, 293); 
        delay(250);
        tone(8, 261); 
        delay(250); 
      }
      break;
    default:
      break;

}
switch (bstate) {
    case NoTune:
      noTone(8);
      break;
    case PlayTune:
      tone(8, 261); //Play Melody (Hz) (Middle C)
      delay(250); //Holds Tone for this duration
      tone(8, 293); 
      delay(250);
      tone(8, 329); 
      delay(250);
      tone(8, 349); 
      delay(250);
      tone(8, 392); 
      delay(250);  
      break;
     case Hold:
      noTone(8); // Stop Buzzer
      break;
    default:
      break;
  }
  return bstate;
}*/

int Buttons(int buttonState) {
  switch(buttonState){
    case buttonStart:
      buttonState = noButton;
      break;
     case noButton:
      if (fanFlag)
        buttonState = button;
      else
        buttonState = noButton;
      break;
      case button:
        Serial.println(fanSpeed);
        if (!fanFlag)
          buttonState = noButton;
        else if (!digitalRead(6) || !digitalRead(2))// Button is pressed
          buttonState = buttonHold;
        else
          buttonState = button;
          
        if (!digitalRead(2)){ //If first button is pressed
          if (fanSpeed <= 240)
            fanSpeed += 10;
        }
        else if (!digitalRead(6)) {// If second button is pressed
          if (fanSpeed >= 110)
            fanSpeed -= 10;
        }
        
        break;
       case buttonHold:
       Serial.println(fanSpeed);
       if (!fanFlag)
        buttonState = noButton;
       else if (!digitalRead(6) || !digitalRead(2)) //Button is held
        buttonState = buttonHold;
       else
        buttonState = button;
       break;
    default:
      break;
  }
  return buttonState;
}
/*switch (buttonState) {
  case button:

     break;
    default:
      break;
  }
  return buttonState;
}*/



void loop() {
  unsigned char i;
  unsigned long currentTime;
  currentTime = millis();
  for (i = 0; i < tasksNum; ++i) {
    if ( (currentTime - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = currentTime; 
    }
  }
}
