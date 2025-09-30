/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       VEX                                                       */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// VEX V5 C++ API
#pragma once

// Essential VEX V5 includes - these should be provided by VEXcode
// If these aren't found, the VEX SDK may not be properly installed
#ifndef VexV5
#include "v5.h"
#include "v5_vcs.h"
#else
// Fallback for when SDK is not found - basic declarations
namespace vex {
    class brain;
    class controller;
    class motor;
    class motor_group;
    
    enum directionType { forward, reverse };
    enum brakeType { coast, brake, hold };
    enum gearSetting { ratio18_1, ratio36_1, ratio6_1 };
    enum velocityUnits { percent, rpm };
    enum rotationUnits { degrees };
    enum temperatureUnits { celsius };
    enum percentUnits { pct };
    enum timeUnits { sec, msec };
    
    extern brain Brain;
}

using namespace vex;
#endif

#include "robot-config.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

void vexcodeInit(void);