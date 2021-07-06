#include <Leg.h>

// Use these to figure out where each leg goes. You might have to adjust this depending on what happens after you run it for the first time. 
// If the legs are rotating the wrong way, you probably confused left and right.
// This code only works to go forward.
// You will need to plug in the joystick to the buttons defined below (x pin and y pin)
// If you can you might need to calibrate the legs to where they are straight down and perpendicular compared to the body.
// There is a high chance this system might not work at all depending on how the servo library reads the servos angles. If it is not working I can fix that later though.

// #define LEG_RA_TOP 4
// #define LEG_RB_TOP 5
// #define LEG_LA_TOP 6
// #define LEG_LB_TOP 7
// #define LEG_RA_BOTTOM 8
// #define LEG_RB_BOTTOM 9
// #define LEG_LA_BOTTOM 10
// #define LEG_LB_BOTTOM 11

#define Y_PIN 0
#define X_PIN 1
#define JOY_BUTTON 2

Leg RA(4, 8, true);
Leg RB(5, 9, true);
Leg LA(6, 10, false);
Leg LB(7, 11, false);

const int deadZone = 40;
const int baseLegAngle = -20;
// The base leg angle determines how much the leg is bent in the idle position. It determines all other walking positions.


const int resetAngles[8] = {baseLegAngle, baseLegAngle, baseLegAngle, baseLegAngle, baseLegAngle, baseLegAngle, baseLegAngle, baseLegAngle};
const int leftAngles[8] = {baseLegAngle, baseLegAngle, baseLegAngle * -1, 0, baseLegAngle * -1, 0, baseLegAngle, baseLegAngle};
// The left and right angles should position the legs forward and in line with each other. 
// If they do not, the cause for this could be incorrect calibration or incorrect defining of sides (left and right legs).
const int rightAngles[8] = {baseLegAngle * -1, 0, baseLegAngle, baseLegAngle, baseLegAngle, baseLegAngle, baseLegAngle * -1, 0};
int currentLegAngles[8] = { 0 };

void setup() {
  Serial.begin(9600);
  resetLegPosition();
  pinMode(JOY_BUTTON, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(X_PIN, INPUT);
}

// Optimized for static movement
void loop() {
  setCurrentLegAngles();
  int mapY = map(analogRead(Y_PIN), 0, 1023, -100, 100);
  Serial.println(mapY);
  if (mapY > deadZone) {
    if (currentLegAngles == resetAngles) {
      leftWalk();
    } else if (currentLegAngles == leftAngles) {
      rightWalk();
    } else if (currentLegAngles == rightAngles) {
      leftWalk();
    }
  } else if (mapY < -deadZone) {
    // Unused statement. Would be used when walking backwards is implemented.
  } else {
    // Resets the leg position to idle when the bot is not being commanded to move.
    resetLegPosition();
  }
}

void leftWalk() {
  RA.setLegPosition(leftAngles[0], leftAngles[1]);
  RB.setLegPosition(leftAngles[2], leftAngles[3]);
  LA.setLegPosition(leftAngles[4], leftAngles[5]);
  LB.setLegPosition(leftAngles[6], leftAngles[7]);
}

void rightWalk() {
  RA.setLegPosition(rightAngles[0], rightAngles[1]);
  RB.setLegPosition(rightAngles[2], rightAngles[3]);
  LA.setLegPosition(rightAngles[4], rightAngles[5]);
  LB.setLegPosition(rightAngles[6], rightAngles[7]);
}

void resetLegPosition() {
  RA.setLegPosition(baseLegAngle, baseLegAngle);
  RB.setLegPosition(baseLegAngle, baseLegAngle);
  LA.setLegPosition(baseLegAngle, baseLegAngle);
  LB.setLegPosition(baseLegAngle, baseLegAngle);
}

void setCurrentLegAngles() {
  currentLegAngles[0] = RA.getTopAngle();
  currentLegAngles[4] = RA.getBottomAngle();
  currentLegAngles[1] = RB.getTopAngle();
  currentLegAngles[5] = RB.getBottomAngle();
  currentLegAngles[2] = LA.getTopAngle();
  currentLegAngles[6] = LA.getBottomAngle();
  currentLegAngles[3] = LB.getTopAngle();
  currentLegAngles[7] = LB.getBottomAngle();
}
