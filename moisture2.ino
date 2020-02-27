#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <AntaresESP8266HTTP.h>


#define ACCESSKEY "0554658c64114ee0:ce03dc363aa6cd02"
#define WIFISSID "Mobile Comm L_5G"
#define PASSWORD "mobcommsukses"
#define projectName "sensor_kelembapan_tanah"
#define deviceName "MoistureSensor"
AntaresESP8266HTTP antares(ACCESSKEY);
#define moisture A0
LiquidCrystal_I2C lcd(0x3F, 16, 2);
Servo servo;
int WET = 16;
int DRY = 2;
int sense_Pin = 0;
int value = 0;

void setup() 
{
  // put your setup code here, to run once:
 
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Sensor Kelembapan Tanah");

  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);

  pinMode(WET, OUTPUT);
  pinMode(DRY, OUTPUT);
  pinMode(moisture, INPUT);

  servo.attach(2);
  servo.write(0);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Sensor Kelembapan: ");
  value= analogRead(sense_Pin);
  value= value/10;
  Serial.println(value);

  antares.add("Moisture Level : ", value);
  Serial.println("%");
  
    if(value>10)
    {
      lcd.setCursor(10,1);
      lcd.print("LEMBAB");
      digitalWrite(WET, HIGH);
      servo.write(0);
      delay(200);
    }
    else
    {
      lcd.setCursor(10,1);
      lcd.print("KERING");
      digitalWrite(DRY, HIGH);
      servo.write(90);
      delay(200);
    }
    delay(1000);
    lcd.clear();

    antares.send(projectName, deviceName);
}
