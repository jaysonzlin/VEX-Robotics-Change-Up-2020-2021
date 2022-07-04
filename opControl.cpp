#include "vex.h"
#include "opControl.h"

using namespace vex;

void driveControl(){
	//Code for mapping controller joysticks in split arcade drive for robot movement

	int threshold;
	int x;
	int x1;
	int y;
	int y1; 
	int z;
	int z1;
	int slope;
	threshold = 15;
	
	//Controller deadzone created so joystick at rest doesn't trigger robot movement
	//Speed scales linearly once outside of controller deadzone
	slope= 100/(100-threshold);
	if(abs(Controller1.Axis3.position()) > threshold){
		x = Controller1.Axis3.position();
		x1= slope*(Controller1.Axis3.position()-threshold*(x/abs(x)))+1*(x/abs(x));
	}
	else{
		x=0;
		x1=0;
	}
	if(abs(Controller1.Axis4.position()) > threshold){
		y = Controller1.Axis4.position();
		y1 = slope*(Controller1.Axis4.position()-threshold*(y/abs(y)))+1*(y/abs(y));
	}
	else{
		y=0;
		y1=0;
	}
	if(abs(Controller1.Axis1.position()) > threshold){
		z = Controller1.Axis1.position();
		z1 = slope*(Controller1.Axis1.position()-threshold*(z/abs(z)))+1*(z/abs(z));
	}
	else{
		z=0;
		z1=0;
	}
	LFMotor.setStopping(coast);
	LBMotor.setStopping(coast);
	RFMotor.setStopping(coast);
	RBMotor.setStopping(coast);

	LFMotor.spin(fwd, (x1+ (y1*.35) + (z1*.4)), pct);
	LBMotor.spin(fwd, (x1+ (y1*.35) +(z1*.4)), pct);
	RFMotor.spin(fwd, (x1- (y1*.35)-(z1*.4)), pct);
	RBMotor.spin(fwd, (x1- (y1*.35)-(z1*.4)), pct);
	}

void intakeControl(){
	//Maps controller trigger buttons to robot's intake
	
	if (Controller1.ButtonR1.pressing()){
		LIntake.spin(fwd, 100, pct);
		RIntake.spin(fwd, 100, pct);
	}
	else if (Controller1.ButtonR2.pressing()){
		LIntake.spin(reverse, 100, pct);
		RIntake.spin(reverse, 100, pct);
	}
	else if (Controller1.ButtonX.pressing()){
		LIntake.spin(reverse,100,pct);
		RIntake.spin(reverse,100,pct);
	}
	else {
		LIntake.stop(hold);
		RIntake.stop(hold);
	}
}

void cycleControl(){
	//Maps controller trigger buttons to robot's internal cyclers to enable cycling of balls at goals

	TRollers.setStopping(hold);
	BRollers.setStopping(hold);

	if (Controller1.ButtonL2.pressing()){
		TRollers.spin(reverse,100,pct);
	}
	else if (Controller1.ButtonL1.pressing()){
		TRollers.spin(fwd,100,pct);
	}
	else if (Controller1.ButtonX.pressing()){
		TRollers.spin(reverse,100,pct);
	}
	else {
		TRollers.stop(hold);
		BRollers.stop(hold);
	}
}

void loader(){
	//Maps triggers buttons to storing mechanism to store balls

	if (Controller1.ButtonL1.pressing()){
		BRollers.spin(fwd,80,pct);
	}
	else if (Controller1.ButtonL2.pressing()){
		BRollers.spin(fwd,100,pct);
	}
	else if (Controller1.ButtonX.pressing()){
		BRollers.spin(reverse,100,pct);
	}
	else {
		BRollers.stop(hold);
	}
  }
