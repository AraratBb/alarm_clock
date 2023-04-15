#include <Keypad.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
unsigned long timer;   
int hours = 0;
int minutes = 1; 
int seconds = 0;
int hourAlarm = 0;
int minuteAlarm = 0; 
char key;
char k = 'F';
int a;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','h'},
  {'4','5','6','m'},
  {'7','8','9','H'},
  {'N','0','F','M'}
};
byte rowPins[ROWS] = {7,6,5,4}; 
byte colPins[COLS] = {3,2,1,0};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void setup()
{
  lcd.begin(16,2);
  timer = millis();
}
  
void loop()
{
  key = keypad.getKey();
  switch(key) 
  {
  case '0' ... '9':
    a = a * 10 + (key - '0');
    break;

  case 'h':
    a = ( a > 24 ? hours : a );
    hours = a;
    a = 0;
    break;
    
   case 'm':
    a = ( a > 60 ? minutes : a );
    minutes = a;
    a = 0;
    break;
    
   case 'H':
    a = ( a > 24 ? hourAlarm : a );
    hourAlarm = a;
    a = 0;
    break;
    
   case 'M':
    a = ( a > 60 ? minuteAlarm : a );
    minuteAlarm = a;
    a = 0;
    break;
    
   case 'N':
    k = 'N';
    break;
    
   case 'F':
    k = 'F';
    break;
  }
  
  lcd.setCursor(0,0); 
  lcd.print("time: ");
  lcd.print(hours); 
  lcd.print(":"); 
  lcd.print(int(minutes)); 
  lcd.print(":");
  lcd.print(seconds);  
  lcd.setCursor(0,1);
  lcd.print("wake: ");
  lcd.print(hourAlarm);
  lcd.print(":");
  lcd.print(minuteAlarm);
  lcd.setCursor(13,1);
  
  if(k == 'F')
    lcd.print("OFF");
  
  if(k == 'N')
    lcd.print("ON ");
  
  if (millis() - timer > 1000)
  {
    timer = millis();
    seconds ++;  
  }
    
  if(seconds == 60)
  {
    seconds = 0;
    minutes ++;
    lcd.setCursor(11,0); 
    lcd.print(' ');
  }
 
  if(minutes == 60)
  {
    minutes = 0;
    seconds = 0;
    hours++;
    lcd.setCursor(9,0); 
    lcd.print(':');
  }
  
  if(hours == 24)
  {
    hours = 0;
    minutes = 0; 
    seconds = 0;
    lcd.setCursor(7,0); 
    lcd.print(':');
    lcd.setCursor(12,0); 
    lcd.print(' ');
  }
  
  if(minutes == minuteAlarm && hours == hourAlarm && k == 'N')
  {
     tone(A4,2000);
     analogWrite(A2, 255);
  }
  
  if(k == 'F')
  {
    noTone(A4);
    analogWrite(A2, 0);
  }
}