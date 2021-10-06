
#include<LiquidCrystal.h>
#include<Servo.h>
#define pinServo 10
//Native_LiquidCrystal.h
//Initializing variables
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo S1;
int degree = 0;
long cm=0;
unsigned char count = 0;
//int num = 1;

//sensor to detect volume of hand sanitizer fluids
long sensordistance2 (int triggerMotion2, int echoMotion2)
{
  //assigning pins
  pinMode(triggerMotion2, OUTPUT);   //setting trigger pin as output
  digitalWrite(triggerMotion2, LOW); 
  delayMicroseconds(2);
  digitalWrite(triggerMotion2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerMotion2, LOW);
  pinMode(echoMotion2, INPUT);        //setting echo pin as input
  return (pulseIn(echoMotion2, HIGH)*0.01723);
}

//sensor to detect the distance of the motion
long sensordistance (int triggerMotion, int echoMotion)
{
  //assigning pin
  pinMode(triggerMotion, OUTPUT);        //setting trigger pin as output
  digitalWrite(triggerMotion, LOW);      //setting the trigger pin off
  delayMicroseconds(2);
  digitalWrite(triggerMotion, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerMotion, LOW);
  pinMode(echoMotion, INPUT);            //setting the echo pin as input
  return (pulseIn(echoMotion, HIGH)*0.01723);
}

//Before start of project
void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Beware of");
  delay(500);
  lcd.setCursor(3,1);
  lcd.println("CORONA!");
  delay(1500);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Stay Safe");
  delay(2500);
  lcd.clear();
  lcd.print("Wash Hands Regularly");
  pinMode(13,OUTPUT);
  S1.attach(pinServo);
  Serial.begin(9600);
  S1.write(0);             //setting servo to zero degree
  delay(1000);
  pinMode(10,OUTPUT);
}

void loop()
{
  for (int i = 0; i < 13; i++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(500);
  }
  lcd.clear();
  cm = sensordistance (9,8);  //for sanitizer fluids
  if (cm > 20)
  {
    cm = sensordistance(5,4);  //for motion distance
    Serial.print(cm);
    Serial.println("cm");
    //If NO Motion
    if(cm > 180)
    {
      digitalWrite(10,LOW);     //Servo motor will be turned off
      S1.write(0);
    }
    if(cm < 180)
    {
      //If any Motion Detected
      lcd.begin(16,2);
      digitalWrite(10, HIGH);    //Servo motor turned on
      S1.write(60);
      lcd.setCursor(4,0);
      lcd.print("Welcome!!");
      //delay(1500);
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      lcd.clear();
      delay(500);
      S1.write(0);
      delay(500);  //Delay before next motion
    }
    
    delay(100);
  }
  else;               //if Sanitizer liquid has run out
  {
    digitalWrite(10, LOW);
    S1.write(0);
  }
}
 