

// V 1.777
// Vinci Studio 7

// 

#include <Joystick.h>
#include <RBD_Timer.h>  
#include <RBD_Button.h>
#include <RBD_Light.h>

RBD::Button YS_on_off(12);
RBD::Button Elv_trim_down(2);
RBD::Button Elv_trim_up(3);
RBD::Button AP_Desingage(4);
RBD::Light ledfl(13);
// ************ VARIABLE*********
unsigned long interval = 30;   // Glavni update interval kontrola
unsigned long  currentMillis = 0;
const int led_sig = 13;
unsigned long previousMillis = 0;
double time_on;
//
int y_MIN;
int y_MAX;
int x_MIN;
int x_MAX;
int p_MIN;
int p_MAX;
int x;
int X;
int p;
int P;
int y;
int Y ;
int x_real;
int y_real;
int p_real;
bool b1 = HIGH;
bool b2 = HIGH;
bool b3 = HIGH;
bool b4 = HIGH;
bool YS_STATUS= HIGH;
String data ;
bool test = LOW;
bool led;
// ********************************


void setup() {


  
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2,INPUT);
  Joystick.begin();
 ledfl.blink(300,1500);
  
    y_MIN = 239;           // CALIBRATE YOUR VALUES 
    y_MAX = 501;

     x_MIN = 301;
    x_MAX = 935;
     
     
     p_MIN = 313;
    p_MAX = 525;

}



void YS_main_send(){

   if(YS_STATUS == HIGH){

//    if (X!= prev_X_Axsis || Y!= prev_Y_Axsis || P!= prev_P_Axsis){
  
  Joystick.setYAxis(Y);
  Joystick.setXAxis(X);
  Joystick.setThrottle(P);
   
   
//   prev_Y_Axsis=Y;
//   prev_X_Axsis=X;
//   prev_P_Axsis=P;
// }

}
}
void logic(){

  y = analogRead(A0);
  b1 = digitalRead(12);
  b2 = digitalRead(2);
  b3 = digitalRead(3);
  b4 = digitalRead(4);
  x = analogRead(A1);
  p = analogRead(A2);

  x_real = x;
  y_real = y;
  p_real = p;
  
  if(y<y_MIN){
    y=y_MIN;
  }
  if(y>y_MAX){
    y=y_MAX;
  }

if(x<x_MIN){
  x=x_MIN;
}
if(x>x_MAX){
  x=x_MAX;
}

if(p<p_MIN){
 p=p_MIN;
}
if(p>p_MAX){
  p=p_MAX;
}

  Y = map(y, y_MIN, y_MAX, -127, 127);
  X = map(x, x_MIN, x_MAX, -127, 127);
  P = map(p,p_MIN,p_MAX,0,255);

}



void debug(){


  if (Serial.available()) {
                // read the incoming byte:
                data= Serial.readString();

                // say what you got:
                Serial.println();
                Serial.print("Primljen input [ASCII konverzija] : ");
                Serial.println(data);

                 if(data == "TEST" || "test" || "t" || "T" ){
                 if (test == LOW){
                    test = HIGH; Serial.println("*************** TEST STARTED *************************");
                  }
                  else{
                    test = LOW;
                    Serial.println("*************** TEST DONE *************************");
                  }
                  
              }
        }




if(test == HIGH){
  time_on = millis();


Serial.print("y :");Serial.print(y_real);Serial.print("  Y :");Serial.print(Y);Serial.print("    p :");Serial.print(p_real);Serial.print("  P :");Serial.print(P);Serial.print("    x :");Serial.print(x_real);
Serial.print("  X :");Serial.print(X);Serial.print("    Joystic Status : ");Serial.print(YS_STATUS);Serial.print(" Data Delay [ms] =");Serial.print(interval);Serial.print("    Button 1: ");
Serial.print(b1);Serial.print("    Button 2: ");
Serial.print(b2);Serial.print("    Button 3: ");
Serial.print(b3);Serial.print("    Button 4: ");
Serial.print(b4);
Serial.print("    Vrijeme rada : ");Serial.print(time_on/1000 );Serial.print(" s ");
Serial.println();
  // put your main code here, to run repeatedly:
    
}
}
void buttons(){


    if (Elv_trim_down.isPressed()) {
      Joystick.pressButton(3);
    }
  if (Elv_trim_down.onReleased()) {
      Joystick.releaseButton(3);
    }
   
  

  if (Elv_trim_up.isPressed()) {
    
      Joystick.pressButton(4);
    }
if (Elv_trim_up.onReleased()) {
      Joystick.releaseButton(4);
    }
  




  if (AP_Desingage.isPressed()) {
      Joystick.pressButton(5);
    }
 if (AP_Desingage.onReleased()) {
      Joystick.releaseButton(5);
    }
  



   
  if (YS_on_off.onPressed()) {

if (YS_STATUS == HIGH) {
      YS_STATUS = LOW;
      Joystick.end();
      ledfl.off();
      digitalWrite(led_sig,LOW);
    }
    else {
      YS_STATUS = HIGH;
       Joystick.begin();
       ledfl.blink(300,1500);
    }
  
    
    delay(20);
  }
}








void loop() {
   
  currentMillis = millis();


if (currentMillis - previousMillis >= interval){

previousMillis = currentMillis;


logic();  
buttons();   
YS_main_send();
debug();


}


ledfl.update();
}


