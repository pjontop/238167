#ifndef INTAKE_H
#define INTAKE_H

#include "vex.h"
#include "config.h"

using namespace vex;

class IntakeSystem {
private:
    motor intakeMotor2;      // 2nd motor intake (Port 18)
    motor topIntake;         // Top intake (Port 10) 
    motor bottomGoalIntake;  // Bottom goal intake (Port 6)
    
    bool isIntakeMotor2Active;
    bool isTopIntakeActive;
    bool isBottomIntakeActive;
    bool isReverseMode;

public:
    // Constructor
    IntakeSystem();
    
    // Individual motor controls
    void startIntakeMotor2();
    void stopIntakeMotor2();
    void startTopIntake();
    void stopTopIntake();
    void startBottomIntake();
    void stopBottomIntake();
    
    // Combined controls
    void startAllIntakes();
    void stopAllIntakes();
    void reverseAllIntakes();
    void setReverseMode(bool reverse);
    
    // Emergency stop
    void emergencyStop();
    
    // Status functions
    bool isAnyIntakeActive();
    void setBrakeType(brakeType brake);
    
    // Update function (call this in main loop)
    void update();
};

// Global intake system instance
extern IntakeSystem intakeSystem;

#endif
