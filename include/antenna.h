#ifndef ANTENNA_H
#define ANTENNA_H

#include "vex.h"
#include "config.h"

using namespace vex;

class AntennaSystem {
private:
    motor antennaMotor;
    bool isActive;
    bool isExtending;

public:
    // Constructor
    AntennaSystem();
    
    // Control functions
    void extend();
    void retract();
    void stop();
    void toggle();
    
    // Status functions
    bool isAntennaActive();
    bool isAntennaExtending();
    
    // Emergency stop
    void emergencyStop();
    
    // Utility functions
    void setBrakeType(brakeType brake);
    double getPosition();
    void resetPosition();
};

// Global antenna system instance
extern AntennaSystem antennaSystem;

#endif
