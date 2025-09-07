#include <DFRobot_DHT11.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
DFRobot_DHT11 DHT;
#define DHT11_PIN 10

int LED1 = 8;
int LED2 = 7;
int buzzer = 6;
#define pwm 9

byte degree[8] = {
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(1, degree);
  lcd.clear();
  lcd.print("Temperature Controlled");
  lcd.setCursor(0,1);
  lcd.print("DC Fan");
  delay(2000);

  Serial.begin(9600);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pwm, OUTPUT);

  analogWrite(pwm, 0); // Fan initially off
}

void loop() {
  delay(200);
  DHT.read(DHT11_PIN);
  int temp = DHT.temperature;
  int hum = DHT.humidity;

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C  Humi: ");
  Serial.println(hum);

  lcd.setCursor(0, 0);
  lcd.print("Temp= ");
  lcd.print(temp);
  lcd.write(1);  // degree symbol
  lcd.print("C ");

  lcd.print("Humi= ");
  lcd.print(hum);
  lcd.print("%");

  lcd.setCursor(0, 1);

  if (temp < 20) {
    analogWrite(pwm, 0);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(buzzer, LOW);
    lcd.print("Fan Speed= 0%   ");
  } else if (temp < 29) {
    analogWrite(pwm, 51);  // ~20%
    digitalWrite(LED1, HIGH);
    lcd.print("Fan Speed= 20%  ");
  } else if (temp < 30) {
    analogWrite(pwm, 102); // ~40%
    digitalWrite(LED1, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.print("Fan Speed= 40%  ");
  } else if (temp < 31) {
    analogWrite(pwm, 153); // ~60%
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.print("Fan Speed= 60%  ");
  } else if (temp < 33) {
    analogWrite(pwm, 204); // ~80%
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.print("Fan Speed= 80%  ");
  } else {
    analogWrite(pwm, 255); // 100%
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.print("Fan Speed=100%  ");
  }

  delay(1000);
}
