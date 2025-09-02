#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD: use 0x27 for most I2C LCDs; change if needed
LiquidCrystal_I2C lcd(0x27, 16, 2);

int gassensor = 0;

void setup() {
  pinMode(A0, INPUT);   // MQ-2 analog output
  pinMode(13, OUTPUT);   // LED
  pinMode(7, OUTPUT);   // Buzzer

  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
}

void loop() {
  gassensor = analogRead(A0);

  // Display sensor value
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gassensor);
  lcd.print("    "); // Clears leftover digits

  // Danger level
  if (gassensor >= 320) {
    digitalWrite(13, HIGH);
    tone(7, 523); // Continuous tone
    lcd.setCursor(0, 1);
    lcd.print("Status: DANGER  ");
  }
  // Warning level
  else if (gassensor >= 300) {
    digitalWrite(13, HIGH);
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("Status: WARNING ");
  }
  // Safe level
  else {
    digitalWrite(13, LOW);
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("Status: Normal  ");
  }

  Serial.println(gassensor);
  delay(1000); // Delay before next reading
}