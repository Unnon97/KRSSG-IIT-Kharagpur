#include "LiquidCrystal.h"

// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(6,7,9,10,11,12);

void setup() {
lcd.begin(16,2);

// set cursor position to start of first line on the LCD
lcd.setCursor(0,0);
//text to print
 lcd.print("HELLO");
// set cusor position to start of next line
/*lcd.setCursor(0,1);
lcd.print("   DISPLAY");*/
  
}
void loop()
{
 
}
