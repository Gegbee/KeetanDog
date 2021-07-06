#ifndef LEG_H
#define LEG_H

#include <Arduino.h>
#include <Servo.h>

class Leg {
    public:
        Leg(int topPin, int bottomPin, bool side);
        void setTopAngle(int angle);
        void setBottomAngle(int angle);
        void setLegPosition(int topAngleChange, int bottomAngleChange);
        void reset();
        bool getSide();
        int getTopAngle();
        int getBottomAngle();
    private: 
        Servo top;
        Servo bottom;  
        bool _side;
};

#endif