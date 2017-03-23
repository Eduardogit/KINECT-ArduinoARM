
#include <Servo.h>
#include <SoftwareSerial.h>

#define rxPin 0
#define txPin 1

SoftwareSerial blue(rxPin, txPin); // RX, TX



Servo giro;
Servo pinzon;
Servo yservo;
Servo xservo;
Servo yyservo;
int ypos = 0;
int xpos = 0;
int i = 0;
bool pinza = false;
void setup() {
  pinzon.attach(9);
  giro.attach(5);
  yyservo.attach(6);
  yservo.attach(10);
  Serial.begin(9600);
  blue.begin(9600);
  Serial.println("inicio...");
}

void loop() {
  static int v = 0; // value to be sent to the servo (0-180)
  
  if ( Serial.available() > 0) {
    char ch = Serial.read(); // read in a character from the serial port and assign to ch
    switch (ch) { // switch based on the value of ch
      case '0'...'9': // if it's numeric
        v = v * 10 + ch - '0';
        blue.println("dentro...");
        
        /*
           so if the chars sent are 45x (turn x servo to 45 degs)..
           v is the value we want to send to the servo and it is currently 0
           The first char (ch) is 4 so
           0*10 = 0 + 4 - 0 = 4;
           Second char is 5;
           4*10 = 40 + 5 = 45 - 0 = 45;
           Third char is not a number(0-9) so we  drop through...
        */
        break;
      case 'x':
        if(v > 150){
          yservo.write(180);  
        }else if(v > 100 && v < 150){
          yservo.write(90);  
        }else if(v> 60 && v< 100){
          yservo.write(60);  
        }else if(v < 60 && v > 30){
          yservo.write(30);  
        }else if(v < 30 && pinza == false){
          pinza = true;
          pinzon.write(180);
        }
        
        if(v > 150 && pinza == true){
          pinza = false;
          pinzon.write(0);
        }
        v = 0;
         break; 
       case 'y':
        if(v > 160 ){
          
          
          
          if(i == 180 || i > 175){
            i = 0;
          }else{
            i++;
          }
          giro.write(i);
        }else if(v > 140 && v < 160){
          yyservo.write(150);  
        }else if(v > 100 && v < 140){
         yyservo.write(90);  
        }else if(v < 100){
          yyservo.write(60);
        }
        v = 0;
       break;        
          
    }
  }
}

