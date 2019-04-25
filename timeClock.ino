#include <Chrono.h>

#include "Employees.h"
#include <RFID.h>

#include <SPI.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int power = 7;
int led = 8;
int serNum[5];
int myNum;
bool access = false;
bool clockedInStatus = false;
Chrono myChrono;
unsigned long hours;


//int cards[][5] = {{117,222,140,171,140}};
int employee_cards[1][5] = {{205, 189, 160, 89, 137}};

int (*p_array)[1][5] = &employee_cards;
Employee e("Fabian", "Hernandez", false, p_array, 0, 0);


void setup() {
  Serial.begin(9600);
  SPI.begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Employee Manage-");
  lcd.setCursor(0, 1);
  lcd.print("-ment System");
  
  rfid.init();
  pinMode(led, OUTPUT);
  pinMode (power, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite (power, LOW);
}

void loop() {
  menu();
}

void menu() {
  Serial.print("Main Menu\n");
  Serial.print("1.Clock In/Out\n");
  Serial.print("2.Inquiry\n");
  Serial.print("3.Create new employee\n");
  while (!Serial.available())
    myNum = Serial.parseInt();
  switch (myNum) {
    case 1:
      clockIn();
      break;
    case 2:
      viewHoursWorked();
      break;
    case 3:
      createNewEmp();
      //Ill leave this I cant erase it.
      //Serial.print("I love Christine\n");    //That's my girlfriend just fyi
      break;
  }
  Serial.read();
}

void clockIn() {
  Serial.print("Please scan your ID card\n");
  while (Serial.available())                          //Waiting for a serial input that is never going to come... Trickery.
    if (rfid.isCard()) {
      rfid.readCardSerial();
      Serial.print(rfid.serNum[0]);
      Serial.print(" ");
      Serial.print(rfid.serNum[1]);
      Serial.print(" ");
      Serial.print(rfid.serNum[2]);
      Serial.print(" ");
      Serial.print(rfid.serNum[3]);
      Serial.print(" ");
      Serial.print(rfid.serNum[4]);
      Serial.println("");
      break;
    }

  for (int x = 0; x < sizeof(employee_cards); x++) {
    for (int i = 0; i < sizeof(rfid.serNum); i++ ) {
      //if (rfid.serNum[i] != employee_cards[x][i]) {
      if (rfid.serNum[i] != e.getEmpID(i)) {
        access = false;
        break;
      } else {
        access = true;
      }
    }
    if (access) break;
  }

  if (access) {
    changeClockInStatus();
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(power, HIGH);
    delay(2000);
    digitalWrite(power, LOW);
    digitalWrite(led, LOW);
    access = false;
  }
  else {
    Serial.println("You don't work here.");
    lcd.clear();
    lcd.print("You don't");
    lcd.setCursor(0,1);
    lcd.print("work here.");
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
  }

}

void changeClockInStatus() //Changes clock in status from true to false, or vice versa
{
  if (clockedInStatus == false)
  {
    clockedInStatus = true;
    Serial.println("Welcome " + e.getFirstName() + " " + e.getLastName() + "\nSuccesful Clock in\n");
    lcd.clear();
    lcd.print("Welcome,");
    lcd.setCursor(0, 1);
    lcd.print(e.getFirstName() + " " + e.getLastName());
    myChrono.start();
  }
  else
  {
    myChrono.stop();
    hours = myChrono.elapsed() / 1000;
    e.setTimeWorked(hours);
    clockedInStatus = false;
    Serial.println("Goodbye " + e.getFirstName() + " " + e.getLastName() + "\nSuccesful Clock out\n");
    Serial.println(hours);
    Serial.println(e.getTimeWorked());
  }
}

void viewHoursWorked() {
  if(clockedInStatus == false){
    Serial.println("Hours worked: " + e.getTimeWorked());
    lcd.clear();
    lcd.print("Hours worked: ");
    lcd.setCursor(0, 1);
    lcd.print(e.getTimeWorked());
  }else{
    Serial.println("Clock out first to see your hours worked.");
  }
}

void createNewEmp(){
  if(e.getIsManager() == true){
    Serial.println("Present new key tag.");
    lcd.clear();
    lcd.print("Present new");
    lcd.setCursor(0, 1);
    lcd.print("key tag.");
  }else{
    Serial.println("Manager Access Only.");
    lcd.clear();
    lcd.print("Manager Access");
    lcd.setCursor(4, 1);
    lcd.print("Only.");
  }
}
