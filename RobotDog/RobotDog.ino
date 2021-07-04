#include <Servo.h>

#define LEG_RA_TOP 3
#define LEG_RB_TOP 5
#define LEG_LA_TOP 6
#define LEG_LB_TOP 9
#define LEG_RA_BOTTOM 10
#define LEG_RB_BOTTOM 11
#define LEG_LA_BOTTOM 6 // Figure out how to change these pins
#define LEG_LB_BOTTOM 9 // Figure out how to change these pins

Servo legLA_Bottom;
Servo legLB_Bottom;
Servo legRA_Bottom;
Servo legRB_Bottom;
Servo legLA_Top;
Servo legLB_Top;
Servo legRA_Top;
Servo legRB_Top;

void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}

int legStartPosition(int topLeg, int bottomLeg) {
  
}

int legMidPosition(int topLeg, int bottomLeg) {
  
}

int legEndPosition(int topLeg, int bottomLeg) {
  
}

void moveLeg(int topLeg, int bottomLeg) {
  
}
