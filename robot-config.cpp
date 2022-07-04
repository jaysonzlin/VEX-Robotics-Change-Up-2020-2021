#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LBMotor = motor(PORT7, ratio18_1, true);
motor LFMotor = motor(PORT6, ratio18_1, true);
motor RBMotor = motor(PORT4, ratio18_1, false);
motor RFMotor = motor(PORT5, ratio18_1, false);
motor RIntake = motor(PORT10, ratio18_1, true);
motor LIntake = motor(PORT1, ratio18_1, false);
motor BRollers = motor(PORT8, ratio6_1, false);
motor TRollers = motor(PORT9, ratio6_1, false);
inertial Inertial = inertial(PORT3);
line LeftTracker = line(Brain.ThreeWirePort.A);
line RightTracker = line(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
