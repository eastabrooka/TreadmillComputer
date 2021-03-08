// Arduino with PCF8574T I2C LCD example

#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
#define HOUR 3600
#define MIN 60

void PrintBoilerplate()
{
  lcd.setCursor(0, 0);
  lcd.print("Time Elapsed");
  lcd.setCursor(0, 1);
  lcd.print("Distance:");
  lcd.setCursor(0, 2);
  lcd.print("Est 5K Time:");
  lcd.setCursor(0, 3);
  lcd.print("Calories Burnt");

  delay(1000);
}

void TimeElapsed(int TimeElapsed)
{
  int time_target = TimeElapsed;
  int hour = time_target / HOUR;
  int second = time_target % HOUR;
  int minute = second / MIN;
  second %= MIN;
  char Buf[16];

  sprintf(Buf, "%.2d:%.2d\0", minute, second);
  lcd.setCursor(13, 0);
  lcd.print(Buf);
  
}
void DistanceTraveled(int DistanceInMeters)
{
  char Buf[16];
  
  lcd.setCursor(9, 1);
  sprintf(Buf, "%.4dm\0", DistanceInMeters);
  lcd.print(Buf);

  double Miles; 
  Miles = 0.00062137*DistanceInMeters ;
  
  lcd.setCursor(15, 1);
  sprintf( Buf, dtostrf( Miles, 4, 2, "%f\0" ) );
  lcd.print(Buf);
}
void Est5KTime(int Est5KTimeSeconds)
{
  char Buf[16];
  int time_target = Est5KTimeSeconds;
  int hour = time_target / HOUR;
  int second = time_target % HOUR;
  int minute = second / MIN;
second   %= MIN;
  
  lcd.setCursor(12, 2);
  int pos = 0;
  pos += sprintf(&Buf[pos], "%01d:", hour);
  pos += sprintf(&Buf[pos], "%02d:", minute);
  pos += sprintf(&Buf[pos], "%02d", second);
  lcd.print(Buf);
}
void CaloriesBurned(int CaloriesBurn)
{
  char Buf[16];
  
  // delay(1000);

  lcd.setCursor(15, 3);
  sprintf(Buf, "%d",CaloriesBurn);
  lcd.print(Buf);
}

void setup() {
  lcd.init();                        // Initialize I2C LCD module
  lcd.backlight();                   // Turn backlight ON
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  PrintBoilerplate();

  delay(2000);

}


int Meters = 0;

int Calories = 0;

// 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 2
// T i m e   E l a p s e d
void loop()
{
 // UpdateDisplay(  millis() / 1000, Meters ,  6000-Meters, Calories);
 TimeElapsed( millis() / 1000);
 DistanceTraveled(Meters);
 Est5KTime(6000-Meters);
 CaloriesBurned(Calories);
 
  Meters+=10;
  Calories++;
  delay(100);


}
