
#include "mbed.h"



class line_sensor{
    private:
    AnalogIn sensor_1, sensor_2, sensor_3, sensor_4, sensor_5, sensor_6;
    float threshhold;
   
    public:
    line_sensor(PinName s1, PinName s2, PinName s3, PinName s4, PinName s5, PinName s6) : 
    sensor_1(s1), sensor_2(s2), sensor_3(s3), sensor_4(s4), sensor_5(s5), sensor_6(s6){
        threshhold = 0.1f; 
    }
    float value_1, value_2, value_3, value_4, value_5,value_6;
    void read_line(){
        value_1= sensor_1.read();
        value_2= sensor_2.read();
        value_3= sensor_3.read();
        value_4= sensor_4.read();
        value_5= sensor_5.read();
        value_6= sensor_6.read();
    }
    bool line_detection(){


        if((value_1>=threshhold)||(value_2>=threshhold)||(value_3>=threshhold)||(value_4>=threshhold)||
        value_5>=threshhold||value_6>=threshhold){
              


            return true;
        }else{return false;}
        }

    bool line_centre(){
        if((value_3 || value_4)>=threshhold){
            return true;
            }
        else{return false;}
    }

    bool line_right(){
        if(value_1>=threshhold||value_2>=threshhold){
            return true;
            }
        else{return false;}
    }

    bool line_left(){
        if(value_6>= threshhold||value_5>=threshhold){
            return true;
            }    
        else{return false;}   

    }


    
    };
    
