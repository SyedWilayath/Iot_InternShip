#include <Keypad.h>
#include<string.h>
#include <Servo.h>
Servo ser;

#define Password_Length 5 

char Data[Password_Length]; 
char Master[Password_Length] = "1234"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};   //connect to the row pinouts of the keypad (R1 R2 R3 R4 = D5 D4 D3 D2)
byte colPins[COLS] = {9, 8, 7, 6};     //connect to the column pinouts of the keypad (C1 C2 C3 C4 = D9 D8 D7 D6)

Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


const int GledPin = 13;
const int PIR = 12;
const int speaker = 11;

void setup(){
   pinMode(GledPin,OUTPUT);
   pinMode(speaker, OUTPUT);
   pinMode(PIR, INPUT);    
   Serial.begin(9600);
   ser.attach(10);
   digitalWrite(GledPin,LOW);

}

void loop(){
  
  ser.write(0);     
  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    data_count++; 
    Serial.print(customKey);
    }

  if(data_count == Password_Length-1){
    if(!strcmp(Data, Master) && digitalRead(PIR) == HIGH){
       ser.write(90);
       digitalWrite(GledPin,HIGH);
       for(int tuning = 100;tuning<=900;tuning+=100){
       tone(speaker, 440 * pow(2.0, (constrain(int(map(tuning, 0, 1023, 36, 84)), 35, 227) - 57) / 22.0), 1000);
       }
       delay(2000);
       ser.write(0);
       digitalWrite(GledPin,LOW);
       for(int tuning =900;tuning>0;tuning-=100){
       tone(speaker, 440 * pow(2.0, (constrain(int(map(tuning, 0, 1023, 36, 84)), 35, 227) - 57) / 22.0), 500);
       }
      }
    clearData();  
  }
  
  
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
