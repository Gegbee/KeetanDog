#include <Arduino.h>
#include "Leg.h"
#include <Servo.h>

// Servo top;
// Servo bottom;  
// bool _side;

Leg::Leg(int topPin, int bottomPin, bool side) {
    pinMode(topPin, OUTPUT);
    pinMode(bottomPin, OUTPUT);
    _side = side;
    top.attach(topPin);
    bottom.attach(bottomPin);
}

void Leg::setTopAngle(int angle) {
    top.write(angle);
}
void Leg::setBottomAngle(int angle) {
    bottom.write(angle);
}
void Leg::setLegPosition(int topAngleChange, int bottomAngleChange) {
    // When setting leg position, 90 degrees is what the legs a calibrated in to be an idle pose. This is relative change to 90 degrees.
    if (_side == true) {
        topAngleChange *= -1;
        bottomAngleChange *= -1;
    }
    bottom.write(90 + bottomAngleChange);
    top.write(90 + topAngleChange);
}
void Leg::reset() {
    top.write(90);
    bottom.write(90);
}
bool Leg::getSide() {
    return _side;
}
int Leg::getTopAngle() {
    return top.read();
}
int Leg::getBottomAngle() {
    return bottom.read();
}