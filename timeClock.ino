#include "Employees.h"
#include <RFID.h>

#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);
Employee e;
int power = 7;
int led = 8;
int serNum[5];
int myNum;
bool access = false;
bool clockedInStatus = false;

//int cards[][5] = {{117,222,140,171,140}};
int employee_cards[1][5] = {{202, 62, 251, 41, 38}};

int (*p_array)[1][5] = &employee_cards;



void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  e.setEmpID(p_array);
  e.setFirstName("Fabian");
  e.setLastName("Hernandez");
  
  pinMode(led, OUTPUT);
  pinMode (power, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite (power, LOW);
}

void loop(){
  menu();
}

void menu() {
  Serial.print("Main Menu\n");
  Serial.print("1.Clock In/Out\n");
  Serial.print("2.Inquiry\n");
  Serial.print("3.Create new employee\n");
  while(!Serial.available())
  myNum = Serial.parseInt();
  switch(myNum){
    case 1:
    clockIn();
    break;
    case 2:
    Serial.print("Hey!\n");
    break;
    case 3:
    Serial.print("I love Christine\n");
    break;
  }
  Serial.read();
}

void clockIn(){
  Serial.print("Please scan your ID card\n");
  while(Serial.available())                           //Waiting for a serial input that is never going to come... Trickery.
  if (rfid.isCard()){
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
          }else{
            access = true;
          }
        }
        if (access) break;
      }
      
   if(access){
      changeClockInStatus();
      digitalWrite(led, HIGH);
      delay(1000);
      
      digitalWrite(power, HIGH);
      delay(2000);
      digitalWrite(power, LOW);
      digitalWrite(led, LOW);
      access = false;
    }
    else{
      Serial.println("You don't work here.");
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
    }

}

void changeClockInStatus()
{
  if(clockedInStatus == false)
  {
    clockedInStatus =true;
     Serial.println("Welcome " + e.getFirstName() + " " + e.getLastName() + "\nSuccesful Clock in\n");
  }
  else
  {
    clockedInStatus =false;
    Serial.println("Goodbye " + e.getFirstName() + " " + e.getLastName() + "\nSuccesful Clock out\n");
  }
    
}

void createEmployee(){
  Serial.println("Please enter the first name of the employee: ");
  Serial.println("Please enter the last name of the employee: ");
  Serial.println("Enter 1 for Employee or 2 for Manager");
}

void validateTag(){
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
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

    }
    if (access) {
      Serial.println("Welcome " + e.getFirstName() + " " + e.getLastName());
      /*
        Valid card : Switch ON the LED for 1000 ms (1 second)
      */
      digitalWrite(led, HIGH);
      delay(1000);
      /*
        Valid card : Switch ON the POWER PIN for 2000 ms (2 seconds)), the POWER PIN can activate for example a relais, controlling a doorlock)
      */
      digitalWrite(power, HIGH);
      delay(2000);
      digitalWrite(power, LOW);
      digitalWrite(led, LOW);
      access = false;
    }
    else {
      /*
        NON-Valid card : switch ON and OFF the LED twice for 0,5 seconds
      */
      Serial.println("Not allowed!");
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
    }
  }
  rfid.halt();
}
