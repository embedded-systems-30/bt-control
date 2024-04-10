#include "mbed.h"

#include "LineSensor.hpp"






class bluetooth{
    private:
    Serial hm10;
   
   public:
    char c;
bluetooth(PinName pin, PinName pin2, int Baud_rate): hm10(pin, pin2, Baud_rate){};
char check_for_data(){
if(hm10.readable()){
    c= hm10.getc();
   return c;
}
return '\0';
}
};

   
int main(void){
    PwmOut right_motor(PC_7);
    PwmOut left_motor(PA_8);
    bluetooth bt(PA_11, PA_12, 9600);

    bool LineDetected;
     line_sensor sensor(PA_7, PA_6, PA_5, PA_12, PA_11, PA_8);
     while(1){
     LineDetected= sensor.line_detection();
     bt.check_for_data();
    if(LineDetected==true){

     if(sensor.line_centre==true){
        right_motor.period_us(30);
        left_motor.period_us(30);
        right_motor.write(0.75f);
        left_motor.write(0.75f);      

        if (bt.c=='T'){
            while(sensor.line_centre==true){
            right_motor.period_us(30);
            left_motor.period_us(30);
            right_motor.write(0.5f);
            left_motor.write(0.75f);
            }
         
        
        }
     }   
   
   }
 }
 wait(0.1);
}