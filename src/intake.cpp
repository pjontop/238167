#include "intake.h"

// Constructor - Initialize all intake motors
IntakeSystem::IntakeSystem() :
    intakeMotor2(MotorPorts::INTAKE_MOTOR_2, GearRatios::INTAKE_RATIO, false),
    topIntake(MotorPorts::TOP_INTAKE, GearRatios::INTAKE_RATIO, false),
    bottomGoalIntake(MotorPorts::BOTTOM_GOAL_INTAKE, GearRatios::INTAKE_RATIO, false),
    isIntakeMotor2Active(false),
    isTopIntakeActive(false),
    isBottomIntakeActive(false),
    isReverseMode(false)
{
    // Set brake types
    setBrakeType(BrakeSettings::INTAKE_BRAKE);
    
    // Set initial velocities
    intakeMotor2.setVelocity(Sensitivity::INTAKE_SPEED, percent);
    topIntake.setVelocity(Sensitivity::INTAKE_SPEED, percent);
    bottomGoalIntake.setVelocity(Sensitivity::INTAKE_SPEED, percent);
}

// Start intake motor 2 (Port 18)
void IntakeSystem::startIntakeMotor2() {
    if (!isIntakeMotor2Active) {
        isIntakeMotor2Active = true;
        if (isReverseMode) {
            intakeMotor2.spin(reverse);
        } else {
            intakeMotor2.spin(forward);
        }
    }
}

// Stop intake motor 2
void IntakeSystem::stopIntakeMotor2() {
    if (isIntakeMotor2Active) {
        isIntakeMotor2Active = false;
        intakeMotor2.stop();
    }
}

// Start top intake (Port 10)
void IntakeSystem::startTopIntake() {
    if (!isTopIntakeActive) {
        isTopIntakeActive = true;
        if (isReverseMode) {
            topIntake.spin(reverse);
        } else {
            topIntake.spin(forward);
        }
    }
}

// Stop top intake
void IntakeSystem::stopTopIntake() {
    if (isTopIntakeActive) {
        isTopIntakeActive = false;
        topIntake.stop();
    }
}

// Start bottom intake (Port 6)
void IntakeSystem::startBottomIntake() {
    if (!isBottomIntakeActive) {
        isBottomIntakeActive = true;
        if (isReverseMode) {
            bottomGoalIntake.spin(reverse);
        } else {
            bottomGoalIntake.spin(forward);
        }
    }
}

// Stop bottom intake
void IntakeSystem::stopBottomIntake() {
    if (isBottomIntakeActive) {
        isBottomIntakeActive = false;
        bottomGoalIntake.stop();
    }
}

// Start all intake motors
void IntakeSystem::startAllIntakes() {
    startIntakeMotor2();
    startTopIntake();
    startBottomIntake();
}

// Stop all intake motors
void IntakeSystem::stopAllIntakes() {
    stopIntakeMotor2();
    stopTopIntake();
    stopBottomIntake();
}

// Reverse all intake motors
void IntakeSystem::reverseAllIntakes() {
    setReverseMode(!isReverseMode);
    
    // Restart active motors in new direction
    if (isIntakeMotor2Active) {
        intakeMotor2.stop();
        wait(50, msec);
        startIntakeMotor2();
    }
    if (isTopIntakeActive) {
        topIntake.stop();
        wait(50, msec);
        startTopIntake();
    }
    if (isBottomIntakeActive) {
        bottomGoalIntake.stop();
        wait(50, msec);
        startBottomIntake();
    }
}

// Set reverse mode
void IntakeSystem::setReverseMode(bool reverse) {
    isReverseMode = reverse;
}

// Emergency stop - immediately stop all motors
void IntakeSystem::emergencyStop() {
    intakeMotor2.stop(brake);
    topIntake.stop(brake);
    bottomGoalIntake.stop(brake);
    
    isIntakeMotor2Active = false;
    isTopIntakeActive = false;
    isBottomIntakeActive = false;
    isReverseMode = false;
}

// Check if any intake is active
bool IntakeSystem::isAnyIntakeActive() {
    return (isIntakeMotor2Active || isTopIntakeActive || isBottomIntakeActive);
}

// Set brake type for all motors
void IntakeSystem::setBrakeType(brakeType brake) {
    intakeMotor2.setStopping(brake);
    topIntake.setStopping(brake);
    bottomGoalIntake.setStopping(brake);
}

// Update function - handles motor states
void IntakeSystem::update() {
    // This function can be used for any continuous updates
    // Currently no continuous updates needed, but ready for future features
}

// Create global intake system instance
IntakeSystem intakeSystem;
