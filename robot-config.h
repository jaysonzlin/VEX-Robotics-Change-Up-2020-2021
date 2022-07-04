using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LBMotor;
extern motor LFMotor;
extern motor RBMotor;
extern motor RFMotor;
extern motor RIntake;
extern motor LIntake;
extern motor BRollers;
extern motor TRollers;
extern inertial Inertial;
extern line LeftTracker;
extern line RightTracker;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
