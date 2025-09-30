#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "vex.h"

using namespace vex;

class Drivetrain {
private:
    // Left side motors
    motor leftFront;
    motor leftMiddle;
    motor leftBack;
    
    // Right side motors
    motor rightFront;
    motor rightMiddle;
    motor rightBack;
    
    // Motor groups for easier control
    motor_group leftMotors;
    motor_group rightMotors;

public:
    // Constructor
    Drivetrain();
    
    // Drivetrain control methods
    void arcadeDrive(double forward, double turn);
    void tankDrive(double leftSpeed, double rightSpeed);
    void stop();
    void setBrakeType(brakeType brake);
    
    // Utility methods
    void resetEncoders();
    double getLeftPosition();
    double getRightPosition();
    double getAveragePosition();
};

// Global drivetrain instance
extern Drivetrain robotDrivetrain;

#endif
