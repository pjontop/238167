#include "controller.h"
#include "config.h"
#include "intake.h"
#include "antenna.h"

// Controller instance
controller Controller1 = controller(primary);

// Button state tracking for edge detection
bool lastXState = false;
bool lastL1State = false;
bool lastR1State = false;
bool lastR2State = false;
bool lastYState = false;
bool lastBState = false;
bool lastAState = false;
bool lastDownState = false;

// Get forward/backward input from left joystick Y-axis
double getForwardInput() {
    double input = Controller1.Axis3.position(percent);
    
    // Apply deadband from config
    if (abs(input) < Sensitivity::DEADBAND) {
        input = 0;
    }
    
    return input;
}

// Get turn input from right joystick X-axis
double getTurnInput() {
    double input = Controller1.Axis1.position(percent);
    
    // Apply deadband from config
    if (abs(input) < Sensitivity::DEADBAND) {
        input = 0;
    }
    
    return input;
}

// Check if any joystick is being used
bool isDriverControlActive() {
    return (abs(Controller1.Axis3.position()) > Sensitivity::DEADBAND || 
            abs(Controller1.Axis1.position()) > Sensitivity::DEADBAND);
}

// Handle all controller inputs
void handleControllerInput() {
    // Get current button states
    bool currentXState = Controller1.ButtonX.pressing();
    bool currentL1State = Controller1.ButtonL1.pressing();
    bool currentR1State = Controller1.ButtonR1.pressing();
    bool currentR2State = Controller1.ButtonR2.pressing();
    bool currentYState = Controller1.ButtonY.pressing();
    bool currentBState = Controller1.ButtonB.pressing();
    bool currentAState = Controller1.ButtonA.pressing();
    bool currentDownState = Controller1.ButtonDown.pressing();
    
    // Handle X button (Hold for intake motor 2)
    if (currentXState && !lastXState) {
        // X button pressed - start intake motor 2
        intakeSystem.startIntakeMotor2();
        Controller1.rumble(Haptics::FUNCTION_ACTIVATED);
    } else if (!currentXState && lastXState) {
        // X button released - stop intake motor 2
        intakeSystem.stopIntakeMotor2();
        Controller1.rumble(Haptics::FUNCTION_DEACTIVATED);
    }
    
    // Handle L1 button (Top intake)
    if (currentL1State && !lastL1State) {
        if (intakeSystem.isAnyIntakeActive()) {
            intakeSystem.stopTopIntake();
            Controller1.rumble(Haptics::FUNCTION_DEACTIVATED);
        } else {
            intakeSystem.startTopIntake();
            Controller1.rumble(Haptics::FUNCTION_ACTIVATED);
        }
    }
    
    // Handle R1 button (Bottom intake)
    if (currentR1State && !lastR1State) {
        if (intakeSystem.isAnyIntakeActive()) {
            intakeSystem.stopBottomIntake();
            Controller1.rumble(Haptics::FUNCTION_DEACTIVATED);
        } else {
            intakeSystem.startBottomIntake();
            Controller1.rumble(Haptics::FUNCTION_ACTIVATED);
        }
    }
    
    // Handle R2 button (Reverse all intakes)
    if (currentR2State && !lastR2State) {
        intakeSystem.reverseAllIntakes();
        Controller1.rumble(Haptics::FUNCTION_ACTIVATED);
    }
    
    // Handle Y button (Emergency stop)
    if (currentYState && !lastYState) {
        intakeSystem.emergencyStop();
        antennaSystem.emergencyStop();
        Controller1.rumble(Haptics::EMERGENCY_STOP);
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("EMERGENCY STOP!");
    }
    
    // Handle B button (Antenna control)
    if (currentBState && !lastBState) {
        antennaSystem.toggle();
        Controller1.rumble(Haptics::FUNCTION_ACTIVATED);
    }
    
    // Handle A button (Display encoder values)
    if (currentAState && !lastAState) {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("L:%.1f R:%.1f", 
                                robotDrivetrain.getLeftPosition(), 
                                robotDrivetrain.getRightPosition());
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("Ant:%.1f", antennaSystem.getPosition());
        Controller1.rumble(Haptics::FUNCTION_ACTIVATED);
    }
    
    // Handle Down button (Reset encoders)
    if (currentDownState && !lastDownState) {
        robotDrivetrain.resetEncoders();
        antennaSystem.resetPosition();
        Controller1.rumble(Haptics::FUNCTION_DEACTIVATED);
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("Encoders Reset");
    }
    
    // Update last button states
    lastXState = currentXState;
    lastL1State = currentL1State;
    lastR1State = currentR1State;
    lastR2State = currentR2State;
    lastYState = currentYState;
    lastBState = currentBState;
    lastAState = currentAState;
    lastDownState = currentDownState;
}
