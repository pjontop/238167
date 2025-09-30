#include "antenna.h"

// Constructor - Initialize antenna motor
AntennaSystem::AntennaSystem() :
    antennaMotor(MotorPorts::ANTENNA, GearRatios::ANTENNA_RATIO, false),
    isActive(false),
    isExtending(false)
{
    // Set brake type
    setBrakeType(BrakeSettings::ANTENNA_BRAKE);
    
    // Set velocity
    antennaMotor.setVelocity(Sensitivity::ANTENNA_SPEED, percent);
}

// Extend antenna
void AntennaSystem::extend() {
    if (!isActive || !isExtending) {
        isActive = true;
        isExtending = true;
        antennaMotor.spin(forward);
    }
}

// Retract antenna
void AntennaSystem::retract() {
    if (!isActive || isExtending) {
        isActive = true;
        isExtending = false;
        antennaMotor.spin(reverse);
    }
}

// Stop antenna movement
void AntennaSystem::stop() {
    if (isActive) {
        isActive = false;
        antennaMotor.stop();
    }
}

// Toggle antenna direction
void AntennaSystem::toggle() {
    if (isActive) {
        if (isExtending) {
            retract();
        } else {
            extend();
        }
    } else {
        extend(); // Default to extending if stopped
    }
}

// Check if antenna is active
bool AntennaSystem::isAntennaActive() {
    return isActive;
}

// Check if antenna is extending
bool AntennaSystem::isAntennaExtending() {
    return isExtending;
}

// Emergency stop
void AntennaSystem::emergencyStop() {
    antennaMotor.stop(brake);
    isActive = false;
    isExtending = false;
}

// Set brake type
void AntennaSystem::setBrakeType(brakeType brake) {
    antennaMotor.setStopping(brake);
}

// Get antenna position
double AntennaSystem::getPosition() {
    return antennaMotor.position(degrees);
}

// Reset antenna position
void AntennaSystem::resetPosition() {
    antennaMotor.resetPosition();
}

// Create global antenna system instance
AntennaSystem antennaSystem;
