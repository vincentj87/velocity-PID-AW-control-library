How to use :

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

  
