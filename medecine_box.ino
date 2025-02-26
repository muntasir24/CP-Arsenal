#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <NewPing.h>
#include <Servo.h>

Servo myServo; //  Servo object
Servo myServo2;

const int trigPin = 12; 
const int echoPin = 11; 


const int thresholdDistance = 15;


bool flag = false;

RTC_DS3231 rtc;  
LiquidCrystal_I2C lcd(0x27, 16, 2);  

const byte ROWS = 4; 
const byte COLS = 3; 

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};


byte rowPins[ROWS] = {2, 3, 4, 5};  
byte colPins[COLS] = {6, 7, 8};     

// Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// slot 1
int hour = 0, minute = 0;  
int inputCount = 0;  
bool alarmTriggered = false; 
int savedHour = 0, savedMinute = 0;  

//  slot 2
int hour2 = 0, minute2 = 0;  
int inputCount2 = 0;  
bool alarmTriggered2 = false; 
int savedHour2 = 0, savedMinute2 = 0;  



void setup() {

  Serial.begin(9600);
 myServo.attach(9); 
  myServo.write(0);  
  myServo2.attach(10); 
  myServo2.write(110); 
  delay(1000);  
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  Serial.println("System Initialized");




  lcd.begin(16, 2);  
 lcd.backlight();   
  lcd.clear();     
  
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    lcd.setCursor(0, 1);
    lcd.print("RTC ERROR!");
    while (1); 
  }

 
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  }

 //led pin
  pinMode(13, OUTPUT);

}

void loop() {

  long duration, distance;


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

 
  duration = pulseIn(echoPin, HIGH);

  
  distance = duration * 0.034 / 2;

  
  if (distance <thresholdDistance and distance>1) {
    flag = true;
  } else {
    flag = false;
  }

 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Flag: ");
  Serial.println(flag ? "true" : "false");
  
///set alarm through esp32
// Check if there is any data available from the ESP32
  if (Serial.available() > 0) {
    // Read the hour for Slot 1
    int slot = Serial.parseInt();
    
    // Read the minute for Slot 1
    int sloth = Serial.parseInt();
    
    // Read the hour for Slot 2
    int slotm = Serial.parseInt();
    
    // Read the minute for Slot 2
  
    if(slot==1){
 Serial.print("Received Slot 1: ");
    Serial.print(sloth);
    Serial.print(":");
    Serial.println(slotm);
hour=sloth;
minute=slotm;
    }
    else if(slot==2){
  Serial.print("Received Slot 2: ");
      Serial.print(sloth);
    Serial.print(":");
    Serial.println(slotm);

    hour2=sloth;
minute2=slotm;
    }
  
  }







//end
  

  char key = keypad.getKey(); 
  
 // for slot 1
  if (key == '*') {
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set for slot 1:");
    
    lcd.setCursor(0, 1);
    lcd.print(savedHour < 10 ? "0" : "");
    lcd.print(savedHour);
    lcd.print(":");
    lcd.print(savedMinute < 10 ? "0" : "");
    lcd.print(savedMinute);



    inputCount = 0;  

    while (inputCount < 4) { 
      key = keypad.getKey();
        if (key == '#' or key=='*') {
    break; 
  }
      if (key) {
      
        if (key >= '0' && key <= '9') {
          if (inputCount == 0) {
            hour = (key - '0') * 10;  
          } else if (inputCount == 1) {
            hour += (key - '0');     
          } else if (inputCount == 2) {
            minute = (key - '0') * 10; 
          } else if (inputCount == 3) {
            minute += (key - '0');      
          }
          
          
          lcd.setCursor(0, 1);
          lcd.print(hour < 10 ? "0" : "");
          lcd.print(hour);
          lcd.print(":");
          lcd.print(minute < 10 ? "0" : "");
          lcd.print(minute);
          
         
          inputCount++;
        }
      }
    }
       delay(500);
     
  }

//for slot 2

if (key == '*' or inputCount==4) {
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set for slot 2:");
    
    lcd.setCursor(0, 1);
    lcd.print(savedHour2 < 10 ? "0" : "");
    lcd.print(savedHour2);
    lcd.print(":");
    lcd.print(savedMinute2 < 10 ? "0" : "");
    lcd.print(savedMinute2);



    inputCount2 = 0;  

    while (inputCount2 < 4) {  
      key = keypad.getKey();
        if (key == '#' or key=='*') {
    break; 
  }
      if (key) {
       
        if (key >= '0' && key <= '9') {
          if (inputCount2 == 0) {
            hour2 = (key - '0') * 10;  
          } else if (inputCount2 == 1) {
            hour2 += (key - '0');       
          } else if (inputCount2 == 2) {
            minute2 = (key - '0') * 10;  
          } else if (inputCount2 == 3) {
            minute2 += (key - '0');       
          }
          
        
          lcd.setCursor(0, 1);
          lcd.print(hour2 < 10 ? "0" : "");
          lcd.print(hour2);
          lcd.print(":");
          lcd.print(minute2 < 10 ? "0" : "");
          lcd.print(minute2);
          
          
          inputCount2++;
        }
      }
    }

    

   delay(500);

     
  }

  // manual control

if(key=='*'){
  
 lcd.clear();
 
  while(1){
      lcd.setCursor(0, 0);
  lcd.print("1 | 2 | 0 | #");
  lcd.setCursor(0, 1);
  lcd.print("B1| B2| B1B2|skip");

       key = keypad.getKey();

       if(key=='1'){
         lcd.clear();
          lcd.print("Opening...");
  lcd.setCursor(0, 1);
  lcd.print("First Box");
       myServo.write(110);
  delay(5000);      
  myServo.write(0); 
  
break;
       }
        if(key=='2'){
         lcd.clear();
          lcd.print("Opening...");
  lcd.setCursor(0, 1);
  lcd.print("second Box");
        //activateServo(myServo2,2);
      
    myServo2.write(0); 
  delay(5000);      
   myServo2.write(110);  
break;
       }
        if(key=='0'){
         lcd.clear();
          lcd.print("Opening...");
  lcd.setCursor(0, 1);
  lcd.print("Both Box");
  myServo.write(110);
    myServo2.write(0); 
  delay(5000);      
  myServo.write(0); 
   myServo2.write(110);  
        
break;
       }
       if(key=='#'){
  break;
       }
  }
    delay(100); 
lcd.clear();


}


 savedHour = hour;  
    savedMinute = minute;  
     savedHour2 = hour2; 
    savedMinute2 = minute2;  

  
  if (key == '#' or inputCount==4 or inputCount2==4 ) {
   
    inputCount = 0; 
    inputCount2=0; 
    lcd.clear();
    displayTime(); 
  }


  DateTime now = rtc.now();
  if (hour == now.hour() && minute == now.minute() && !alarmTriggered) {
   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time to take");
    lcd.setCursor(0, 1);
    lcd.print("medicine 1");
    
    delay(2000); 
    
   int i;
    for (i = 0; i < 40; i++) {
      lcd.clear();
      digitalWrite(13, HIGH);
  
      delay(100);
      lcd.setCursor(0, 0);
      lcd.print(" Time to take");
      lcd.setCursor(0, 1);
      lcd.print("medicine 1");
       

         bool flag = open(trigPin, echoPin, thresholdDistance);
  //Serial.println(flag ? "true" : "false");
if(flag)break;

      delay(100);
    
  //delay(2000);       
  

 // delay(2000);  
        
    
    }
    if(i==39){
 Serial.println(911); 
  Serial.println(11);
  i=0; 

    }

    digitalWrite(13, LOW);   
    alarmTriggered = true; 
    lcd.clear();
  }


if (minute != now.minute()) {
 alarmTriggered = false; 
}

//slot 2
 if (hour2 == now.hour() && minute2 == now.minute() && !alarmTriggered2) {
   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Time to take");
    lcd.setCursor(0, 1);
    lcd.print("medicine 2 ");
    
    delay(1000); 
    
int i;
    for ( i = 0; i < 40; i++) {
      lcd.clear();
      digitalWrite(13, HIGH);  
   
      delay(100);
      lcd.setCursor(0, 0);
      lcd.print("Time to take");
      lcd.setCursor(0, 1);
      lcd.print("medicine 2 ");
      
         bool flag = open(trigPin, echoPin, thresholdDistance);

  //Serial.println(flag ? "true" : "false");
if(flag){
  break;
}


          delay(100);
        
    }
     if(i==39){
 Serial.println(911);  //emergency whatsapp alarm not pressed
  Serial.println(12); 
i=0;
    }
     digitalWrite(13, LOW);
    alarmTriggered2 = true; 
    lcd.clear();
  }

if (minute2 != now.minute()) {
 alarmTriggered2 = false; 
}


//if (flag and now.hour() >= hour and now.hour()<=((hour+8)%24))
//21 22 23 24 1 2 3 4 5 6
if(flag and now.minute()==minute and now.hour()==hour){
  //slot 1
 //digitalWrite(13, HIGH);

lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Taking medecine");
    lcd.setCursor(0, 1);
    lcd.print("Slot 1");
activateServo(myServo,1);
//  myServo.write(110);

//   delay(5000);      
//   myServo.write(0); 
  


delay(500); 
lcd.clear();

}
else if(flag){
  //slot 2
 //digitalWrite(13, HIGH);

 lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Taking medecine");
    lcd.setCursor(0, 1);
    lcd.print("Slot 2");

//activateServo(myServo2,2);

 myServo2.write(0);
   
  delay(5000);      
  myServo2.write(110); 
    
   
lcd.clear();

}
//digitalWrite(13, LOW);


  delay(200);


 



  displayTime();
}

void displayTime() {
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  

  DateTime now = rtc.now();
  

  lcd.setCursor(6, 0);
  if (now.hour() < 10) {
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");

  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(":");

  lcd.setCursor(12, 0);
  if (now.second() < 10) {
    lcd.print("0");
  }
  lcd.print(now.second(), DEC);

 
  lcd.setCursor(6, 1);
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
}

void activateServo(Servo &servo, int which) {
  if(which==1){
       servo.write(110); 

int cnt=0;
  
  while (1) {
    bool flag = open(trigPin, echoPin, thresholdDistance);
       if (flag==0) {
      cnt++;
      
    }
    if(cnt==2){
      delay(500);
      break;
    }
 
 
  }
 servo.write(0);

  delay(500);  
  }

 
}



int open(int trigPin, int echoPin, float thresholdDistance) {
  long duration;
  float distance;
  int flag;


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  
  if (distance <thresholdDistance and distance>1 ) {
    flag = 1;
  } else if(distance>1) {
    flag = false;
  }
  else flag=-1;

 


  return flag;
}



