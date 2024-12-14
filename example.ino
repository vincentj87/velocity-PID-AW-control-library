#include "motorControl.h"
#include "Pinout.h"
String out;
motorControl M1(PWM1,DIR1A,DIR1B,encM1A,encM1B);
motorControl M2(PWM2,DIR2A,DIR2B,encM2A,encM2B);
void setup(){
  M1.setPID(KP_value,KI_value,KD_value);
  M2.setPID(KP_value,KI_value,KD_value);
  M1.setSetpoint(0);
  M2.setSetpoint(0);
  Serial.begin(115200);
}
void loop(){
 
   M2.calculatePID();
   M1.calculatePID();
   M1.motorMove(M1.getPID());
   M2.motorMove(M2.getPID());
  Serial.print(M1.getRPM());
  Serial.print(" ");
  Serial.println(M2.getRPM());

  while(Serial.available()){
    char a=char(Serial.read());
    if(a!='\n'){
      out+=a;
      
    }else{
      M1.setSetpoint(out.toFloat());
      M2.setSetpoint(out.toFloat());
      out="";
    }
  }
delay(10);
}
