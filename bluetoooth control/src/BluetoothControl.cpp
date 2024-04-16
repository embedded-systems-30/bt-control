
#include "mbed.h"
#include "LineSensor.hpp"//inclue line sensor class



class bluetooth{
    private:
    BufferedSerial hm10;
   
   public:
    char c;
bluetooth(PinName pin, PinName pin2, int Baud_rate): hm10(pin, pin2, Baud_rate){};
char check_for_data(){//checks if data is readable then equates character c with the value given to the bluetooth module
if(hm10.readable()){
   hm10.read(&c,1);
   return c;
}
return '\0';//if no value is readable return random value in order to showcase error
}
};

Ticker SpeedReducer;
float duty_cycle = 0.75f;
void reduce_speed(){//can be in hpp
    PwmOut right_motor(PC_7);//creating objects for bluetooth module and right and left motor
    PwmOut left_motor(PA_8);
     if (duty_cycle > 0){
     duty_cycle -= 0.05f;
     right_motor.period_us(30);
     left_motor.period_us(30);
     right_motor.write(duty_cycle);
     left_motor.write(duty_cycle);
     
    }else{
     SpeedReducer.detach();
 }
  if (duty_cycle < 0) {
        duty_cycle = 0;
        }
 }  
int main(void){
    PwmOut right_motor(PC_7);//creating objects for bluetooth module and right and left motor
    PwmOut left_motor(PA_8);
    bluetooth bt(PA_11, PA_12, 9600);
    bool LineDetected;
     line_sensor sensor(A0, A1, A2, A3, A4, A5);//creating an object for the 6 sensors

     while(1){
     LineDetected = sensor.line_detection();
     bt.check_for_data();//check bluetooth module for any new values
    if(LineDetected==true){//if a line is detected and it is at the centre the buggy will move in a straight line continuously
        
     if(sensor.line_centre==true){
        right_motor.period_us(30);
        left_motor.period_us(30);
        right_motor.write(0.75f);
        left_motor.write(0.75f);
        bt.check_for_data();
        printf("line detected");

        if (bt.c=='T'){//if microcontroller recieves command 'T' from buggy it will start doing a uturn until line has been detected again
            right_motor.period_us(30);
            left_motor.period_us(30);
            right_motor.write(0.25f);
            left_motor.write(0.75f);
            sensor.line_detection();
           
            }
        
        }
     }   
    else if(LineDetected==false&&bt.c=='T') {        //if line not detected and u turn command is still active, continue turning
            right_motor.period_us(30);
            left_motor.period_us(30);
            right_motor.write(0.25f);
            left_motor.write(0.75f);
            sensor.line_detection();
            bt.check_for_data();
            }
    else {//if line is not detected and bluetooth command not received, stop the buggy
            SpeedReducer.attach(&reduce_speed, 0.0050);
            sensor.line_detection();
            }

    ThisThread::sleep_for(100ms);
   }
 }
