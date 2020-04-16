
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//COLOURFUL-1ST SENSOR, B&W-2ND SENSOR 1-2:entry  2-1 exit
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trigger1 = 2; //Trigger pin of 1st Sesnor
const int echo1 = 3; //Echo pin of 1st Sesnor
const int trigger2 = 4; //Trigger pin of 2nd Sesnor
const int echo2 = 5;//Echo pin of 2nd Sesnor
int count = 0;
long time_taken;
int dist,distL,distR;

int button = 6;
int press = 0;
boolean toggle = true;

void setup()
{
  Serial.begin(9600);
  lcd.begin();
 
 // Turn on the blacklight and print a message.
  lcd.backlight();

  pinMode(13, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(6, HIGH);
  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(10);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  time_taken = pulseIn(echo, HIGH);
  dist= time_taken*0.034/2;
  if (dist>50)
    dist = 50;
}

void loop()
{

  if(count > 0)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
 
  calculate_distance(trigger1,echo1);
  distL =dist; //get distance of left sensor
 
  if(dist < 50){
    for(int i=0;i < 6;i++)
    {
      calculate_distance(trigger2,echo2);
      distR =dist;
      if(dist < 50)
      {
        count++;
        Serial.print(count);
        break;
       
      }
      delay(200);
    }
  }
  calculate_distance(trigger2,echo2);
  distR =dist; //get distance of right sensor
  if(distR < 50){
    for(int i=0;i < 5;i++)
    {
      calculate_distance(trigger1,echo1);
      distR =dist;
      if(dist < 50)
      {
        count--;
        Serial.print(count);
        break;
      }
      delay(200);
    }
  }
  //Uncomment for debudding
  //Serial.print("L=");
  //Serial.println(distL);
  //Serial.print("R=");
  //Serial.println(distR);

  if(count < 0)
  {
    count = 0;
  }
 
  delay(200);
  lcd.setCursor(0,0);
  lcd.print("People in room:");
  lcd.setCursor(0,1);
  lcd.print(count);
  Serial.print(count);
  lcd.print(" ");
}
