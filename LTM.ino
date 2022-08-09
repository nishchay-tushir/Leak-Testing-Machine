#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd1(0x26, 16, 2);
float a = 0;
float b = 0;
float c = 0;
float d = 0;
const  float OffSet = 0.483;
int button = 0;
int t = 0;
int u = 0;
int o = 0;
float carrier;
float carrierx;
float carrierr;


void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  lcd.begin(16, 2);
  lcd1.begin(16, 2);
  lcd.backlight();
  lcd1.backlight();
  Serial.begin(9600);


}

void loop() {

  if (o == 0) {
    lcd.setCursor(2, 0);
    lcd.print ("Press 1 for");
    lcd.setCursor(1, 1);
    lcd.print ("Default Settings");
    lcd1.setCursor(2, 0);
    lcd1.print("Press 0 for");
    lcd1.setCursor(1, 1);
    lcd1.print("Custom Settings");
    char keyy = customKeypad.getKey();
    if (keyy) {
      o = 1;
      carrierr = (keyy);
      Serial.println(keyy);
      Serial.println(carrierr);
      lcd.clear();
      lcd1.clear();
    }
  }

  else if (t == 0 & carrierr == 48 ) {
    lcd.setCursor(1, 0);
    lcd.print ("Enter filling");
    lcd1.setCursor(0, 0);
    lcd1.print("Time in Seconds");
    char key = customKeypad.getKey();
    if (key) {
      t = 1;
      carrier = (key);
      Serial.println(key);
      Serial.println(carrier);
      lcd.clear();
      lcd1.clear();
    }
  }

  else if (u == 0 & carrierr == 48) {
    lcd.setCursor(1, 0);
    lcd.print ("Enter Testing");
    lcd1.setCursor(0, 0);
    lcd1.print("Time in Second");
    char keyx = customKeypad.getKey();
    if (keyx) {
      u = 1;
      carrierx = (keyx);
      Serial.println(keyx);
      Serial.println(carrierx);
      lcd.clear();
      lcd1.clear();
    }
  }

  else if (carrierr == 49) {
    carrier = 52;
    carrierx = 53;
    carrierr = 0;
  }

  else if (analogRead(A1) == 1023) {

    lcd.clear();
    lcd1.clear();
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    delay(100);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    delay(1000);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);

    lcd.clear();
    lcd1.clear();
    lcd.setCursor(1, 0);
    lcd.print("Starting Cycle");
    lcd.setCursor(0, 1);
    lcd.print("-----------------------");
    lcd1.setCursor(4, 0);
    lcd1.print("Air Pass");
    lcd1.setCursor(0, 1);
    lcd1.print("-----------------------");
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    delay(1500);
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cycle in Progress");
    lcd.setCursor(0, 1);
    lcd.print("-----------------------");
    digitalWrite(12, HIGH);
    lcd1.clear();
    digitalWrite(12, HIGH);
    float fill = carrier - 48;
    Serial.println(fill);

    for (int i = 0; i < fill ; i++) {
      lcd1.setCursor(0, 0);
      lcd1.print("Filling Air -");
      lcd1.setCursor(13, 0);
      lcd1.print(i);
      lcd1.setCursor(15, 0);
      lcd1.print("s");
      lcd1.setCursor(0, 1);
      lcd1.print("-----------------------");
      delay(1000);
    };

    lcd1.clear();
    lcd.clear();
    digitalWrite(13, HIGH);
    a = analogRead(A0);
    float test = carrierx - 48;


    for (int j = 0; j < test ; j++) {
      lcd.setCursor(0, 0);
      lcd.print("Leak Test -");
      lcd.setCursor(13, 0);
      lcd.print(j);
      lcd.setCursor(15, 0);
      lcd.print("s");
      lcd.setCursor(0, 1);
      lcd.print("-----------------------");
      lcd1.setCursor(0, 0);
      lcd1.print("Pressure-");
      lcd1.setCursor(9, 0);
      float pressure_bar = ((3.205 * ((float)(((analogRead(A0)) * 5.0) / 1024.0))) * 1000000.0 / 10e5);
      lcd1.print(pressure_bar);
      lcd1.setCursor(13, 0);
      lcd1.print("Bar");
      delay(1000);
    };
    b = analogRead(A0);
    digitalWrite(12, HIGH);
    c = a - 20;
    d = a + 20;

    if ( b<d and b>c) {
      digitalWrite(10, LOW);
      lcd1.clear();
      lcd1.setCursor(0, 0);
      lcd1.print("Leak Test-OK");
      lcd1.setCursor(0, 1);
      lcd1.print("-----------------------");
      delay(2000);
      digitalWrite(10, HIGH);
      lcd.clear();
      lcd1.clear();
    }
    else {
      digitalWrite(11, LOW);
      lcd1.clear();
      lcd1.setCursor(4, 0);
      lcd1.print("Leak Test");
      lcd1.setCursor(6, 1);
      lcd1.print("FAIL");
      delay(2000);
      digitalWrite(11, HIGH);
      lcd.clear();
      lcd1.clear();
    }
    delay(10);
  }
  else {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    lcd.setCursor(3, 0);
    lcd.print("Welcome to");
    lcd.setCursor(2, 1);
    lcd.print("L.T.M.");
    lcd1.setCursor(1, 0);
    lcd1.print("Press to start");
  }
}
