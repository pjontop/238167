/*   /$$   /$$                                         /$$       /$$$$$$$                             /$$$$$$  /$$$$$$$$ /$$       
    | $$  /$$/                                        | $$      | $$__  $$                           /$$__  $$|_____ $$/| $/       
    | $$ /$$/   /$$$$$$   /$$$$$$  /$$$$$$$   /$$$$$$ | $$      | $$  \ $$ /$$   /$$  /$$$$$$       | $$  \__/     /$$/ |_//$$$$$$$
    | $$$$$/   /$$__  $$ /$$__  $$| $$__  $$ /$$__  $$| $$      | $$$$$$$ | $$  | $$ /$$__  $$      | $$$$$$$     /$$/    /$$_____/
    | $$  $$  | $$$$$$$$| $$  \__/| $$  \ $$| $$$$$$$$| $$      | $$__  $$| $$  | $$| $$$$$$$$      | $$__  $$   /$$/    |  $$$$$$ 
    | $$\  $$ | $$_____/| $$      | $$  | $$| $$_____/| $$      | $$  \ $$| $$  | $$| $$_____/      | $$  \ $$  /$$/      \____  $$
    | $$ \  $$|  $$$$$$$| $$      | $$  | $$|  $$$$$$$| $$      | $$$$$$$/|  $$$$$$$|  $$$$$$$      |  $$$$$$/ /$$/       /$$$$$$$/
    |__/  \__/ \_______/|__/      |__/  |__/ \_______/|__/      |_______/  \____  $$ \_______/       \______/ |__/       |_______/ 
                                                                          /$$  | $$                                               
                                                                          |  $$$$$$/                                               
                                                                           \______/                                                
*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       pramsupandey                                              */
/*    Created:      23/9/2025, 4:08:13 p.m.                                   */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Global instances are defined in their respective files (drivetrain.cpp, controller.cpp)

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  
  // Initialize all systems
  robotDrivetrain.setBrakeType(BrakeSettings::DRIVETRAIN_BRAKE);
  robotDrivetrain.resetEncoders();
  
  intakeSystem.setBrakeType(BrakeSettings::INTAKE_BRAKE);
  antennaSystem.setBrakeType(BrakeSettings::ANTENNA_BRAKE);
  antennaSystem.resetPosition();
  
  // Display initialization message on controller
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Robot Systems Ready!");
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("Tank Drive + Intake");
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("Y=Emergency Stop");
  
  Controller1.rumble(Haptics::SYSTEM_READY);
  
  // Brief pause to show the message
  wait(2, sec);
  Controller1.Screen.clearScreen();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // Example autonomous routine
  
  // Reset encoders for autonomous
  robotDrivetrain.resetEncoders();
  antennaSystem.resetPosition();
  
  // Ensure all systems are stopped at start
  intakeSystem.emergencyStop();
  antennaSystem.emergencyStop();
  
  // Example autonomous sequence:
  
  // 1. Drive forward for 2 seconds
  robotDrivetrain.arcadeDrive(50, 0);  // 50% forward, 0% turn
  wait(2, sec);
  
  // 2. Start intake while turning
  intakeSystem.startAllIntakes();
  robotDrivetrain.arcadeDrive(0, 30);  // 0% forward, 30% turn
  wait(1, sec);
  
  // 3. Stop everything
  robotDrivetrain.stop();
  intakeSystem.stopAllIntakes();
  
  // Add your autonomous code here
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // Handle all controller inputs
    handleControllerInput();
    
    // Get joystick inputs for driving
    double forwardInput = getForwardInput();
    double turnInput = getTurnInput();
    
    // Use arcade drive control
    robotDrivetrain.arcadeDrive(forwardInput, turnInput);
    
    // Update all systems
    intakeSystem.update();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
