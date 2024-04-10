#include "mbed.h"



class line_sensor{
    private:
    AnalogIn sensor_1, sensor_2, sensor_3, sensor_4, sensor_5, sensor_6;
    float threshhold;
   
    public:
     bool line_right, line_left, line_centre;
    line_sensor(PinName s1, PinName s2, PinName s3, PinName s4, PinName s5, PinName s6) : 
    sensor_1(s1), sensor_2(s2), sensor_3(s3), sensor_4(s4), sensor_5(s5), sensor_6(s6){
        threshhold = 1.2;
    }
    
    bool line_detection(){
        float value_1= sensor_1.read();
        float value_2= sensor_2.read();
        float value_3= sensor_3.read();
        float value_4= sensor_4.read();
        float value_5= sensor_5.read();
        float value_6= sensor_6.read();

        if(value_1>=threshhold||value_2>=threshhold||value_3>=threshhold||value_4>=threshhold||
        value_5>=threshhold||value_6>=threshhold){
            return true;  
            if(value_1>=threshhold||value_2>=threshhold||(value_2&&value_3>=threshhold)){
                line_right = true;
                line_left = false;
                line_centre = false;
            }
            else if((value_3 || value_4)>=threshhold&&(value_2 && value_1 && value_5 && value_6)<threshhold){
                line_centre = true;
                line_right = false;
                line_left = false;
            }
            else if(value_6>= threshhold||value_5>=threshhold||(value_5&&value_4)>=threshhold){
                line_centre =false;
                line_right = false;
                line_left = true;
            }
        }else{return false;}


        }


    
    };
    
