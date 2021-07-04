#include <Leg.h>

#define LEG_RA_TOP 4
#define LEG_RB_TOP 5
#define LEG_LA_TOP 6
#define LEG_LB_TOP 7
#define LEG_RA_BOTTOM 8
#define LEG_RB_BOTTOM 9
#define LEG_LA_BOTTOM 10
#define LEG_LB_BOTTOM 11

#define Y_PIN 0
#define X_PIN 1
#define JOY_BUTTON 2

Leg RA(4, 8, true);
Leg RB(5, 9, true);
Leg LA(6, 10, false);
Leg LB(7, 11, false);

const int deadZone = 40;
const int walkDelay = 30;
const int baseLegAngle = -20;

// enum legPosition {
//   RESET,
//   LEFT_WALK_A,
//   RIGHT_WALK_A,
//   LEFT_WALK_B,
//   RIGHT_WALK_B
// };

// extern legPosition legState = RESET;

const int[8] resetAngles = {0, 0, 0, 0, 0, 0, 0, 0};
const int[8] forwardAngles = {0, 0, 0, 0, 0, 0, 0, 0};
const int[8] backwardAngles = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  resetLegPosition();
  pinMode(JOY_BUTTON, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(X_PIN, INPUT);
}

// Optimized for static movement
void loop() {
  int mapY = map(analogRead(Y_PIN), 0, 1023, -100, 100);
  Serial.println(mapY);
  if (mapY > deadZone) {
    int[8] legAngles = getCurrentPositions();
    if (legAngles == resetAngles) {
      leftWalk();
    } else if (legAngles == forwardAngles) {
      rightWalk();
    } else if (legAngles == backwardAngles) {
      leftWalk();
    }
  } else if (mapY < -deadZone) {

  } else {
    resetLegPosition();
  }
}

void leftWalk() {
  // legState = LEFT_WALK_A;
  RA.setLegPosition(baseLegAngle, baseLegAngle);
  RB.setLegPosition(baseLegAngle * -1, baseLegAngle * -1);
  LA.setLegPosition(baseLegAngle * -1, baseLegAngle * -1);
  LB.setLegPosition(baseLegAngle, baseLegAngle);
}

void rightWalk() {
  // legState = RIGHT_WALK_A;
  RA.setLegPosition(baseLegAngle * -1, baseLegAngle * -1);
  RB.setLegPosition(baseLegAngle, baseLegAngle);
  LA.setLegPosition(baseLegAngle, baseLegAngle);
  LB.setLegPosition(baseLegAngle * -1, baseLegAngle * -1);
}

void resetLegPosition() {
  // legState = RESET;
  // Sets the leg positions to the idle pose (90 is idle, so setting positions to 0 means that the legs will be at 90 degrees).
  RA.setLegPosition(baseLegAngle, baseLegAngle);
  RB.setLegPosition(baseLegAngle, baseLegAngle);
  LA.setLegPosition(baseLegAngle, baseLegAngle);
  LB.setLegPosition(baseLegAngle, baseLegAngle);
}

int * getCurrentPositions() {
  int[8] legAngles = {
  RA.getTopAngle(), 
  RB.getTopAngle(), 
  LA.getTopAngle(), 
  LB.getTopAngle(), 
  RA.getBottomAngle(), 
  RB.getBottomAngle(), 
  LA.getBottomAngle(), 
  LB.getBottomAngle()};
  return legAngles;
}