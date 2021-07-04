#ifndef Leg
#define Leg

#include "Arduino.h"

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
        int _topPin;
        int _bottomPin;
        Servo top;
        Servo bottom;  
        bool _side;
}

#endif