#ifndef motorControl_h
#define motorControl_h

#include "Arduino.h"
#include <ESP32Encoder.h>
class motorControl:public ESP32Encoder{
  public:
 
    motorControl(int pinPWM, int pinDIR_A, int pinDIR_B,int pinEncA,int pinEncB);
    void motorMove(float pwm);
    void calculatePID();
    void setSetpoint(int setpoint );

    void setPID(float Kp_val,float Ki_val,float Kd_val);
    float getRPM(); 
    float getPID();
    
  private:
    int
    _pinPWM,
    _pinDIR_A,
    _pinDIR_B,
    _pwmOut;
    float
    _rpm,
    _rpm_error,
    _last_rpm_error=0.0,
    _rpm_setpoint,
    _Pterm,
    _Iterm,
    _Dterm,
    _PID_value,
    _Kp,
    _Ki,
    _Kd;
    unsigned long
    _nowT;
};
#endif
