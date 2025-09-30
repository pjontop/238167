#include "drivetrain.h"
#include "config.h"

// Constructor - Initialize all motors with their port numbers from config
Drivetrain::Drivetrain() :
    // Left side motors (ports from config)
    leftFront(MotorPorts::LEFT_FRONT, GearRatios::DRIVETRAIN_RATIO, false),
    leftMiddle(MotorPorts::LEFT_MIDDLE, GearRatios::DRIVETRAIN_RATIO, false),
    leftBack(MotorPorts::LEFT_BACK, GearRatios::DRIVETRAIN_RATIO, false),
    
    // Right side motors (ports from config)
    // Note: Right side motors are typically reversed
    rightFront(MotorPorts::RIGHT_FRONT, GearRatios::DRIVETRAIN_RATIO, true),
    rightMiddle(MotorPorts::RIGHT_MIDDLE, GearRatios::DRIVETRAIN_RATIO, true),
    rightBack(MotorPorts::RIGHT_BACK, GearRatios::DRIVETRAIN_RATIO, true),
    
    // Group motors together
    leftMotors(leftFront, leftMiddle, leftBack),
    rightMotors(rightFront, rightMiddle, rightBack)
{
    // Set brake type from config
    setBrakeType(BrakeSettings::DRIVETRAIN_BRAKE);
    
    // Set velocity units
    leftMotors.setVelocity(0, percent);
    rightMotors.setVelocity(0, percent);
}

// Arcade drive control - forward/backward and turning
void Drivetrain::arcadeDrive(double forward, double turn) {
    // Apply sensitivity from config
    forward *= Sensitivity::DRIVE_SENSITIVITY;
    turn *= Sensitivity::TURN_SENSITIVITY;
    
    // Calculate left and right motor speeds
    double leftSpeed = forward + turn;
    double rightSpeed = forward - turn;
    
    // Clamp values to [-100, 100] range
    leftSpeed = std::max(-100.0, std::min(100.0, leftSpeed));
    rightSpeed = std::max(-100.0, std::min(100.0, rightSpeed));
    
    // Set motor velocities
    leftMotors.setVelocity(leftSpeed, percent);
    rightMotors.setVelocity(rightSpeed, percent);
    
    // Spin the motors
    leftMotors.spin(forward);
    rightMotors.spin(forward);
}

// Tank drive control - independent left and right side control
void Drivetrain::tankDrive(double leftSpeed, double rightSpeed) {
    // Clamp values to [-100, 100] range
    leftSpeed = std::max(-100.0, std::min(100.0, leftSpeed));
    rightSpeed = std::max(-100.0, std::min(100.0, rightSpeed));
    
    // Set motor velocities
    leftMotors.setVelocity(leftSpeed, percent);
    rightMotors.setVelocity(rightSpeed, percent);
    
    // Spin the motors
    leftMotors.spin(forward);
    rightMotors.spin(forward);
}

// Stop all drivetrain motors
void Drivetrain::stop() {
    leftMotors.stop();
    rightMotors.stop();
}

// Set brake type for all motors
void Drivetrain::setBrakeType(brakeType brake) {
    leftMotors.setStopping(brake);
    rightMotors.setStopping(brake);
}

// Reset encoder positions to 0
void Drivetrain::resetEncoders() {
    leftMotors.resetPosition();
    rightMotors.resetPosition();
}

// Get left side encoder position (average of all left motors)
double Drivetrain::getLeftPosition() {
    return (leftFront.position(degrees) + leftMiddle.position(degrees) + leftBack.position(degrees)) / 3.0;
}

// Get right side encoder position (average of all right motors)
double Drivetrain::getRightPosition() {
    return (rightFront.position(degrees) + rightMiddle.position(degrees) + rightBack.position(degrees)) / 3.0;
}

// Get average encoder position of both sides
double Drivetrain::getAveragePosition() {
    return (getLeftPosition() + getRightPosition()) / 2.0;
}

// Create global drivetrain instance
Drivetrain drivetrain;
