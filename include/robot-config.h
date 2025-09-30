using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;

// Project specific includes
#include "config.h"
#include "drivetrain.h"
#include "intake.h"
#include "antenna.h"
#include "controller.h"

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );