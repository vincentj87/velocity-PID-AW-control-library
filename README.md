# How to use :
## definition
Anti-windup in a PID controller prevents the integral term from continuously accumulating when the actuator reaches its output limit. Without anti-windup, the error can increase significantly because the actuator can't produce a higher output, causing the integral term to 'wind up' and leading to instability or poor control performance
## depedency 
this library depended on __[ESP32Encoder](https://github.com/madhephaestus/ESP32Encoder)__  library by madhephaestus

## setup library
+ include the `motorControl.h` and `motorControl.cpp` file in the same folder as your main sketch
+ you can ether declare your pinout inseperated header file or directly in main sketch, see `pinout.h` for example 
  
## using library
create an object from motorControl class 
``` c++
motorControl motor1(motorDriverPinPwm,motorDriverPinDirectionA,motorDriverPinDirectionB,encoderPin_A,encoderPin_B);
```
  
in the void setup set your PID value
``` c++
motor1.setPID(KP_value,KD_value,KI_value);
```

int the void loop call pid calculate function to get your PID value
``` c++
motor1.calculatePID();
```

move your motor based on the PID value:
``` c++
motor1.motorMove(motor1.getPID());
```

  
