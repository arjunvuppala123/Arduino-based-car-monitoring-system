#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>

int ledPin= 3;
int ledNo= 12;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int sensorPin = 0;
Adafruit_NeoPixel strip= Adafruit_NeoPixel(ledNo,ledPin,NEO_RGB+NEO_KHZ800);

int GasSensorVal= 0;// Set the initial sensorValue to 0
int forcePin=A1;
int ForceVal = 0;//for force

 
int buzzerPin= 2;
int echoPin= 6;
int trigPin= 5;
int minDistance = 50;
int maxDistance = 335;
int buzzer=11; 

int Forcevalue=0;


void setup() 
{

  //GAS SENSOR
  pinMode(A1, INPUT);
  Serial.begin(9600);
  pinMode(A2,INPUT);
  Serial.begin(9600);
  
  //force sensor leds
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(forcePin,INPUT);
  pinMode(buzzer,OUTPUT);
  // Initialize serial communication at 9600 bits per secondSerial.begin(9600);  
  strip.begin();
  for(int i = 0; i < ledNo; i++)
  {
   strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
  lcd.begin(16, 2);               // start lcd
  for(int i=0;i<=3;i++);
  lcd.setCursor(0,0);
  lcd.print("WELCOME BOIS");
  lcd.setCursor(0,1);
  delay(2000);
  lcd.clear();
  lcd.print("MPCA PROJECT V69");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.display();
}

void loop() 
{
  GasSensorVal = analogRead(A1);
  lcd.setCursor(0, 0);
  lcd.print("Gas :");
  lcd.print(GasSensorVal);
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.clear();
  delay(500);
  if (GasSensorVal >000 && GasSensorVal <= 306){
		lcd.print("Normal");
	}else if (GasSensorVal > 307 &&  GasSensorVal <= 420){
		lcd.print("Gas Detected");
	}else if (GasSensorVal > 421 && GasSensorVal <= 520){
		lcd.print("Dense Gas Det");
    }else if (GasSensorVal > 521 && GasSensorVal <= 724){
    lcd.print("EMERGENCY!");
    }
  
  delay(2000);
  //Serial.print("Gas ");
  Serial.println(GasSensorVal);
  //Serial.println(" cm");
  
  
  ForceVal = analogRead(A2);
  
  //forceval leds
  
  if (ForceVal < 375 && ForceVal >= 0) {
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
  }
  else
  {
    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
  }
  
  delay(10);
  
  
  
  lcd.setCursor(0, 0);
  delay(500);
  lcd.print("Force :");
  lcd.print(ForceVal);
  lcd.print(" N");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.clear();
   delay(500);
  //Serial.print("Force ");
  //Serial.print(ForceVal);
  //Serial.println(" N");
  
  int distance = calcDistance();
  lcd.setCursor(0, 0);
   delay(500);
  lcd.print("The object is");
  lcd.setCursor(0, 1);
  lcd.print("in: ");
  lcd.print(distance);
  lcd.print("cm");
  delay(2000);
  lcd.clear();
   delay(500);
  //Serial.println(distance);
  int ledsToGlow = map(distance, minDistance, maxDistance, ledNo, 1);
  //lcd.setCursor(0, 0);
  //lcd.print(ledsToGlow);
  ///delay(2000);
  //lcd.clear();
  Serial.println(ledsToGlow);
  if(ledsToGlow == 12)
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
  for(int i = 0; i < ledsToGlow; i++)
  {
    if(i < 4)
    {
      strip.setPixelColor(i,strip.Color(50,0,0));//green,red,blue
    }
    else if(i >= 4 && i < 8)
    {
      strip.setPixelColor(i,strip.Color(50,50,0));//green,red,blue
    }
    else if(i >= 8 && i < 12)
    {
      strip.setPixelColor(i,strip.Color(0,50,0));//green,red,blue
    }
  }
  for(int i = ledsToGlow; i < ledNo; i++)
  {
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
  delay(500);
  //gow
  int reading = analogRead(sensorPin);
  float voltage = reading * 4.68;
  voltage /= 1024.0;
   // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100;
  lcd.setCursor(0, 0);
  lcd.print(temperatureC);
  lcd.setCursor(0, 1);
  lcd.print(" degrees C");
  delay(2000);
  lcd.clear();
   delay(500);
  Serial.print(temperatureC);
  Serial.println(" degrees C");
 
  delay(1000);
  //koti
  //while(Forcevalue!=0)
  
  Forcevalue = analogRead(forcePin);
  lcd.setCursor(0, 0);
   delay(500);
  lcd.print("test");
  lcd.print(Forcevalue);
  delay(2000);
  lcd.clear();
   delay(500);
  //Serial.println (Forcevalue);
  tone(buzzer,Forcevalue);
  delay(100);
  noTone(buzzer);
  delay(100);
  
}

int calcDistance()
{
  long distance,duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/29/2;
  if(distance >= maxDistance)
  {
    distance = maxDistance;
  }
  if(distance <= minDistance)
  {
    distance = minDistance;
  }
  return distance;
}
//ggg



