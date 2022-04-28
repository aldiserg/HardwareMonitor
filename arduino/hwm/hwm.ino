
// -------------------- БИБЛИОТЕКИ ---------------------

#include <string.h>             // библиотека расширенной работы со строками
#include <Wire.h>               // библиотека для соединения
#include <LiquidCrystal_I2C.h>  // библтотека дислея
#include <TimerOne.h>           // библиотека таймера

// значок градуса!!!! lcd.write(223);
byte degree[8] = {0b11100,  0b10100,  0b11100,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000};
// правый край полосы загрузки
byte right_empty[8] = {0b11111,  0b00001,  0b00001,  0b00001,  0b00001,  0b00001,  0b00001,  0b11111};
// левый край полосы загрузки
byte left_empty[8] = {0b11111,  0b10000,  0b10000,  0b10000,  0b10000,  0b10000,  0b10000,  0b11111};
// центр полосы загрузки
byte center_empty[8] = {0b11111, 0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111};
byte row8[8] = {0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};

unsigned long err;
int PCdata[6];
int printErr;
String perc;
LiquidCrystal_I2C lcd(0x27, 20, 4);


#define printByte(args)  write(args);

void setup() {
  Serial.begin(9600);
  Timer1.initialize(40);   // поставить частоту ШИМ 25 кГц (40 микросекунд)
  // инициализация дисплея
  lcd.init();
  lcd.backlight();
}

// ------------------------------ ОСНОВНОЙ ЦИКЛ -------------------------------
void loop() {
    if (! Serial.available() > 0) {
    if (err == 0){
      err = millis();
    }
    if (millis() - err > (unsigned long) 10*1000 && printErr != 1) {
      lcd.clear();
      printErr = 1;
      lcd.setCursor(5, 1);
      lcd.print("CONNECTION");
      lcd.setCursor(7, 2);
      lcd.print("FAILED"); 
    }
  }
  
  if (Serial.available() > 0) {
    err = 0;
    printErr = 0;
    for (int i = 0; i < 6; i++) { 
      while (!Serial.available());
      PCdata[i] = Serial.read();
    }
  }
  if (printErr != 1){
    static_info();
    printData();
    printTable();  
  }
}

void printData() {
  lcd.setCursor(4, 0); lcd.print(PCdata[4]); lcd.write(223);
  lcd.setCursor(17, 0); lcd.print(PCdata[0]);
  if (PCdata[0] < 10) perc = "% ";
    else if (PCdata[0] < 100) perc = "%";
      else perc = "";  lcd.print(perc);
  lcd.setCursor(4, 1); lcd.print(PCdata[5]); lcd.write(223);
  lcd.setCursor(17, 1); lcd.print(PCdata[1]);
    if (PCdata[1] < 10) perc = "% ";
      else if (PCdata[1] < 100) perc = "%";
        else perc = "";  lcd.print(perc);
  lcd.setCursor(17, 2); lcd.print(PCdata[2]);
  if (PCdata[2] < 10) perc = "% ";
    else if (PCdata[2] < 100) perc = "%";
      else perc = "";  lcd.print(perc);
  lcd.setCursor(17, 3); lcd.print(PCdata[3]);
  if (PCdata[3] < 10) perc = "% ";
    else if (PCdata[3] < 100) perc = "%";
      else perc = "";  lcd.print(perc);
}
     
void printTable() {
  for (int i = 0; i < 4; i++) {
    byte line = ceil(PCdata[i] / 10);
    lcd.setCursor(7, i);
    if (line == 0) lcd.printByte(1)
      else lcd.printByte(4);
    for (int n = 1; n < 9; n++) {
      if (n < line) lcd.printByte(4);
      if (n >= line) lcd.printByte(2);
    }
    if (line == 10) lcd.printByte(4)
      else lcd.printByte(3);
  }
}
    

void static_info() {
    lcd.createChar(0, degree);
    lcd.createChar(1, left_empty);
    lcd.createChar(2, center_empty);
    lcd.createChar(3, right_empty);
    lcd.createChar(4, row8);
    lcd.setCursor(0, 0);
    lcd.print("CPU:");
    lcd.setCursor(0, 1);
    lcd.print("GPU:");
    lcd.setCursor(0, 2);
    lcd.print("GPUmem:");
    lcd.setCursor(0, 3);
    lcd.print("RAMuse:");
}
