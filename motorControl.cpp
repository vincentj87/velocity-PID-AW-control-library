#include "Arduino.h"
#include "motorControl.h"
#include "Pinout.h"


motorControl::motorControl(int pinPWM, int pinDIR_A, int pinDIR_B,int pinEncA,int pinEncB) {
  
  //init encoder lib
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  ESP32Encoder::attachHalfQuad(pinEncA, pinEncB);
  ESP32Encoder::clearCount();
  
  //init pinout
  pinMode(pinDIR_A, OUTPUT);
  pinMode(pinDIR_B, OUTPUT);
  pinMode(pinPWM, OUTPUT);
  
  _pinDIR_A = pinDIR_A;
  _pinDIR_B = pinDIR_B;
  _pinPWM = pinPWM;

}

void motorControl::motorMove(float pwm) {

  if (pwm >= 0) {
    _pwmOut = int(pwm);
    digitalWrite(_pinDIR_A, 0);
    digitalWrite(_pinDIR_B, 1);
    analogWrite(_pinPWM, _pwmOut);
  }
  if (pwm < 0) {
    pwm = -1 * pwm;
    _pwmOut = int(pwm);
    digitalWrite(_pinDIR_A, 1);
    digitalWrite(_pinDIR_B, 0);
    analogWrite(_pinPWM, _pwmOut);
  }
}
void motorControl::setPID(float Kp_val=1.5,float Ki_val=25.0,float Kd_val=0.02){
  _Kp=Kp_val;
  _Ki=Ki_val;
  _Kd=Kd_val;
}
float motorControl::getRPM(){
  return _rpm;
}
void motorControl::setSetpoint(int setPoint = 0){
  _rpm_setpoint=(float)setPoint;
}
float motorControl::getPID(){
  return (_PID_value);
}
void motorControl::calculatePID() {

  //execute every 25ms
  if ( (_nowT + 25000) <= micros()) {
    long _current_time = micros();
    float _delta_time = ((float)_current_time - (float)_nowT) / 1.0e6;
  
    int encoder_count = ESP32Encoder::getCount();
    ESP32Encoder::clearCount();
    
    float pulse_per_second = (float)encoder_count / _delta_time;
    _rpm = (pulse_per_second / PPR) * 60.0;
    //==============ERROR CALCULATION===============
    _rpm_error=_rpm_setpoint-_rpm;
    //==============P-TERM CALCULATION===============
    _Pterm=_rpm_error*_Kp;
    //==============I-TERM CALCULATION===============
    _Iterm=_Iterm+(_Ki*_rpm_error*_delta_time);
   
    if(_Iterm>255.0){//limit saturation high
      _Iterm=255.0;
    }
    else if(_Iterm<-255.0){//limit saturation low
      _Iterm=-255.0;
    }
    //==============D-TERM CALCULATION===============
    _Dterm=_Kd*(_rpm_error-_last_rpm_error)/_delta_time;
    //=============PID CALCULATION====================
    _PID_value=_Pterm+_Iterm+_Dterm;
    //=============ANTI WINDUP========================
    if(_PID_value>255){
      _Iterm-=_Ki*(_PID_value-255)*_delta_time;
      _PID_value=255;
    }
    if(_PID_value<-255){
      _Iterm+=_Ki*(-255-_PID_value)*_delta_time;
      _PID_value=-255;
    }
    _last_rpm_error=_rpm_error;
    
    if(_rpm_error==0){
      _Iterm=0;
    }
    

    
    
    _nowT=micros();
  }
}
