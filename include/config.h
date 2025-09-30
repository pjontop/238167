#ifndef CONFIG_H
#define CONFIG_H

#include "vex.h"

using namespace vex;

// ================================
// ROBOT CONFIGURATION FILE
// ================================
// Modify this file to change ports, sensitivity, and controls

// ================================
// MOTOR PORTS CONFIGURATION
// ================================
namespace MotorPorts {
    // Drivetrain Motors
    const int LEFT_FRONT = PORT11;
    const int LEFT_MIDDLE = PORT12;
    const int LEFT_BACK = PORT13;
    
    const int RIGHT_FRONT = PORT1;
    const int RIGHT_MIDDLE = PORT2;
    const int RIGHT_BACK = PORT3;
    
    // Intake Motors
    const int INTAKE_MOTOR_2 = PORT18;  // 2nd motor intake
    const int TOP_INTAKE = PORT10;      // Top intake
    const int BOTTOM_GOAL_INTAKE = PORT6; // Bottom goal intake
    
    // Other Systems
    const int ANTENNA = PORT20;
}

// ================================
// CONTROL SENSITIVITY SETTINGS
// ================================
namespace Sensitivity {
    const double DRIVE_SENSITIVITY = 1.0;      // Drive speed multiplier (0.1 - 1.0)
    const double TURN_SENSITIVITY = 0.8;       // Turn sensitivity multiplier (0.1 - 1.0)
    const double DEADBAND = 5.0;               // Joystick deadband (percent)
    
    const double INTAKE_SPEED = 100.0;         // Intake motor speed (percent)
    const double ANTENNA_SPEED = 50.0;         // Antenna motor speed (percent)
}

// ================================
// CONTROLLER BUTTON MAPPING
// ================================
namespace Controls {
    // Drive Controls (built-in, cannot be changed)
    // Left Stick Y-axis: Forward/Backward
    // Right Stick X-axis: Turning
    
    // Function Buttons (using correct VEX V5 button names)
    const auto INTAKE_MOTOR_2_BUTTON = controller::button::buttonX;      // Hold X for intake motor 2
    const auto TOP_INTAKE_BUTTON = controller::button::buttonL1;         // L1 for top intake
    const auto BOTTOM_INTAKE_BUTTON = controller::button::buttonR1;      // R1 for bottom intake
    const auto REVERSE_INTAKE_BUTTON = controller::button::buttonR2;     // R2 for reverse intake
    const auto EMERGENCY_STOP_BUTTON = controller::button::buttonY;      // Y for emergency stop
    const auto ANTENNA_BUTTON = controller::button::buttonB;             // B for antenna control
    
    // Utility Buttons
    const auto ENCODER_DISPLAY_BUTTON = controller::button::buttonA;     // A to show encoder values
    const auto RESET_ENCODERS_BUTTON = controller::button::buttonDown;   // Down arrow to reset encoders
}

// ================================
// MOTOR GEAR RATIOS
// ================================
namespace GearRatios {
    const gearSetting DRIVETRAIN_RATIO = ratio18_1;
    const gearSetting INTAKE_RATIO = ratio18_1;
    const gearSetting ANTENNA_RATIO = ratio18_1;
}

// ================================
// BRAKE SETTINGS
// ================================
namespace BrakeSettings {
    const brakeType DRIVETRAIN_BRAKE = brake;
    const brakeType INTAKE_BRAKE = coast;
    const brakeType ANTENNA_BRAKE = hold;
}

// ================================
// HAPTIC FEEDBACK PATTERNS
// ================================
namespace Haptics {
    const char* FUNCTION_ACTIVATED = ".";       // Single short pulse
    const char* FUNCTION_DEACTIVATED = "..";    // Double short pulse
    const char* EMERGENCY_STOP = "---";         // Long pulse
    const char* SYSTEM_READY = ".-";            // Dot-dash pattern
    const char* ERROR = "....";                 // Rapid pulses
}

#endif