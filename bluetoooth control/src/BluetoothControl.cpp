

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
    PwmOut right_motor(PC_7);//creating objects for bluetooth module and right and left motor
    PwmOut left_motor(PA_8);

Ticker SpeedReducer;
float duty_cycle = .51f;
void reduce_speed(){//can be in hpp
     if (duty_cycle > 0){
     duty_cycle -= 0.05f;
     right_motor.period_us(30);
     left_motor.period_us(30);
     right_motor.write(duty_cycle);
     left_motor.write(1-duty_cycle);
     
    }else{
     SpeedReducer.detach();
 }
  if (duty_cycle < 0) {
        duty_cycle = 0;
        }
       
 }  
     DigitalOut ena(PB_2,0);
     
     void buggy_straight(){
         right_motor.write(0.6f);
         left_motor.write(0.4f);
     }
     void buggy_turn_right(){
         right_motor.write(0.6f);
         left_motor.write(0.35f);
     }
     void buggy_turn_left(){
      right_motor.write(0.65);
      left_motor.write(0.4f);
     }
int main(void){
    bluetooth bt(PA_11, PA_12, 9600);
    right_motor.write(0.50);
    left_motor.write(0.50);
    ThisThread::sleep_for(1000ms);
    ena=1; 
    
    
     line_sensor sensor(A0, A1, A2, A3, A4, A5);//creating an object for the 6 sensors
        right_motor.period_us(30);
        left_motor.period_us(30);
     while(1){
     sensor.read_line();
     bt.check_for_data();//check bluetooth module for any new values
    if(sensor.line_detection()==true){//if a line is detected and it is at the centre the buggy will move in a straight line continuously
        
     if(sensor.line_centre()){
      bt.c='c';
      buggy_straight();
        }

      if(sensor.line_right()){
         buggy_turn_right();
      }
      if(sensor.line_left()){
         buggy_turn_left();
      }
     }   
             if (bt.check_for_data()=='T'){//if microcontroller recieves command 'T' from buggy it will start doing a uturn until line has been detected again
            right_motor.period_us(30);
            left_motor.period_us(30);
            right_motor.write(0.6f);
            left_motor.write(0.6f);
            sensor.line_detection();
            if(sensor.line_centre()==true){
                bt.c='c';
                buggy_straight();
            }
            ThisThread::sleep_for(1000ms);
           
            }
       
         if ((!sensor.line_detection()) && (bt.check_for_data()!='T')){//if line is not detected and bluetooth command not received, stop the buggy
            SpeedReducer.attach(&reduce_speed, 0.0050);
              ena = 0;
             right_motor.write(0.5f);
        left_motor.write(0.5f);
            sensor.line_detection();
            }

    ThisThread::sleep_for(100ms);
    
   }
   
 }
