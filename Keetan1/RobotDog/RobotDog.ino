#include <Servo.h>

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

Servo legLA_Bottom;
Servo legLB_Bottom;
Servo legRA_Bottom;
Servo legRB_Bottom;
Servo legLA_Top;
Servo legLB_Top;
Servo legRA_Top;
Servo legRB_Top;

Servo bottom[] = {legLA_Bottom, legLB_Bottom, legRA_Bottom, legRB_Bottom}; 
Servo top[] = {legLA_Top, legLB_Top, legRA_Top, legRB_Top};
Servo left[] = {legLA_Bottom, legLB_Bottom, legLA_Top, legLB_Top};
Servo right[] = {legRA_Bottom, legRB_Bottom, legRA_Top, legRB_Top};

const int deadZone = 40;
const int walkDelay = 30;

enum legPosition {
  RESET,
  LEFT_WALK_A,
  RIGHT_WALK_A,
  LEFT_WALK_B,
  RIGHT_WALK_B
};

extern legPosition legState = RESET;

void setup() {
  Serial.begin(9600);
  legLA_Bottom.attach(LEG_LA_BOTTOM);
  legLB_Bottom.attach(LEG_LB_BOTTOM);
  legRA_Bottom.attach(LEG_RA_BOTTOM);
  legRB_Bottom.attach(LEG_RB_BOTTOM);
  legLA_Top.attach(LEG_LA_TOP);
  legLB_Top.attach(LEG_LB_TOP);
  legRA_Top.attach(LEG_RA_TOP);
  legRB_Top.attach(LEG_RB_TOP);

  resetLegPosition();
  
  pinMode(JOY_BUTTON, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(X_PIN, INPUT);
}

void loop() {
  int mapY = map(analogRead(Y_PIN), 0, 1023, -100, 100);
  Serial.println(mapY);
  if (mapY > deadZone) {
    switch (legState) {
      case RESET:
          leftWalk();
      case LEFT_WALK_A:
          rightWalk();
      case RIGHT_WALK_A:
          resetLegPosition();
    }
  } else if (mapY < -deadZone) {
    
  } else {
    resetLegPosition();
  }
}

void rotate(bool dir) {
  resetLegPosition();
  delay(walkDelay);
  if (dir == true) {

  } else {
    
  }
}

void leftWalk() {
  legState = LEFT_WALK_A;
  changeLegPosition(legLA_Top, legLA_Bottom);
  legIdlePosition(legLB_Top, legLB_Bottom);
  legForwardPosition(legRA_Top, legRA_Bottom);
  legIdlePosition(legRB_Top, legRB_Bottom);
}

void rightWalk() {
  legState = RIGHT_WALK_A;
  legIdlePosition(legLA_Top, legLA_Bottom);
  legForwardPosition(legLB_Top, legLB_Bottom);
  legIdlePosition(legRA_Top, legRA_Bottom);
  legForwardPosition(legRB_Top, legRB_Bottom);
}

void resetLegPosition() {
  legState = RESET;
  // Sets the leg positions to the idle pose with hind legs
  for (int i = 0; i < 4; i++) {
    legIdlePosition(top[i], bottom[i]);
  }
}

bool valueInArray(Servo val, Servo arr[]){
    for(int i = 0; i < sizeof(arr); i++){
        if (arr[i] == val) {
          return true;
        }
    }
    return false;
}

void changeLegPosition(Servo topLeg, Servo bottomLeg, int topChange, int bottomChange) {
  if (valueInArray(topLeg, right) == true) {
    topChange *= -1
    bottomChange *= -1
  }
  topLeg.write(90 + topChange);
  bottomLeg.write(90 + bottomChange);
}
