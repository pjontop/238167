#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vex.h"

using namespace vex;

// Forward declarations
class Drivetrain;
extern Drivetrain robotDrivetrain;

// Controller configuration
extern controller Controller1;

// Controller input functions
double getForwardInput();
double getTurnInput();
bool isDriverControlActive();

// Main controller handler
void handleControllerInput();

#endif
