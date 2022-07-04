/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LBMotor              motor         7               
// LFMotor              motor         6               
// RBMotor              motor         4               
// RFMotor              motor         5               
// RIntake              motor         10              
// LIntake              motor         1               
// BRollers             motor         8               
// TRollers             motor         9               
// Inertial             inertial      3               
// LeftTracker          line          A               
// RightTracker         line          B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "opControl.h"
#include "stuff.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial.calibrate();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

//Homerow Autonomous

//During Robot Skills Challenge, the code in void autonomous() should be replaced by 106.cpp

  SetupMotors();
  //First Goal
  Shoot(2);
  StoreOn();
  GyroStraightTime(-31,.25);//.25
  ResetHeading();
  GyroStraightUntilLeftWhite(50);//40
  GyroStraightDistance(40,8);//35
  GyroTurn(135);
  GyroStraightTime(40,1.25); 
  MotorOff();
  Shoot(1);

//Second Goal
  GyroStraightUntilRightWhite(-40);//-35
  //GyroStraightDistance(-35,5);
  MotorOff();
  GyroTurn(135);
  ResetHeading();
  StoreOn();
  GyroStraightUntilLeftWhite(45);
  GyroStraightDistance(40, 1);//35
  GyroTurn(-90); 
  MotorOff();
  GyroStraightTime(35,.65);//.75
  Shoot(3);
  MotorOff();
//Third Goal
  GyroStraightUntilLeftWhite(-35);
  GyroTurn(90);
  Intake(2);
  GyroStraightDistance(50,38);
  GyroTurn(-35);
  GyroStraightTime(50,1.5);
  MotorOff();
  Intake(2);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    driveControl();
    intakeControl();
    cycleControl();
    loader();
 

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
