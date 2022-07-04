#include "vex.h"
#include "stuff.h"

using namespace vex;

const double WHEEL_DIAMETER = 3.25;
const double WHEEL_CIRCUMFERENCE = M_PI * WHEEL_DIAMETER;

const double FASTEST_TURN_SPEED = 50;
const double FAST_TURN_SPEED = 23;
const double SLOW_TURN_SPEED = 10; // 10->5
const double START_SLOW_TURN = 30;
const double STOP_SLOW_TURN = 5;
const double TURN_SPEED_SLOPE = (FAST_TURN_SPEED - SLOW_TURN_SPEED)/(START_SLOW_TURN -
STOP_SLOW_TURN);

double heading = 0;

void SetupMotors() {
	//Resets built-in motor encoders and sets braking mode of each motor
	
	LFMotor.setStopping(brake);
	LFMotor.resetRotation();
	LBMotor.setStopping(brake);
	LBMotor.resetRotation();
	RFMotor.setStopping(brake);
	RFMotor.resetRotation();
	RBMotor.setStopping(brake);
	RBMotor.resetRotation();

	LIntake.setStopping(coast);
	LIntake.resetRotation();
	LIntake.setMaxTorque(100,pct);
	RIntake.setStopping(coast);
	RIntake.resetRotation();
	RIntake.setMaxTorque(100,pct);

	TRollers.setStopping(hold);
	TRollers.resetRotation();
	TRollers.setMaxTorque(100,pct);
	BRollers.setStopping(hold);
	BRollers.resetRotation();
	BRollers.setMaxTorque(100,pct);
}

void SetupInertial() {
	//Calibrates Inertial Sensor to set current heading as 0 degrees
	//Prints Inertial heading, rotation, and drift to robot brain

	Inertial.calibrate();
	Brain.Screen.print("Calibrating inertial ....");
	vex::task::sleep(4000);
	while (Inertial.isCalibrating()) {
		vex::task::sleep(100);
	}

	Inertial.setHeading(0, degrees);
	Inertial.setRotation(0, degrees);
	for (int i = 0; i < 5; i++) {
		Brain.Screen.setCursor(2, 1);
		Brain.Screen.print("heading = %.3lf, rotation = %.3lf",
		Inertial.heading(degrees), Inertial.rotation(degrees));
		vex::task::sleep(1000);
	}
	double drift = (Inertial.rotation(degrees) / 5.0);
	Brain.Screen.setCursor(4, 1);
	Brain.Screen.print("DRIFT = %.3lf", drift);
	vex::task::sleep(3000);
	Brain.Screen.clearScreen();
}

void ResetHeading() {
	//Resets heading to 0
	
	heading = 0;
	Inertial.resetRotation();
}

double GetRotation() {
	//Returns the rotation after accounting for error in Inertial Sensor
	
	return 1.009 * Inertial.rotation(degrees);
}

void PrintGyro() {
	// Prints current gyro values, used for debugging
	
	Brain.Screen.print("Print gyro");
	for (int i = 0; i < 5; i++) {
		Brain.Screen.setCursor(i + 6, 1);
		Brain.Screen.print("h: %.1lf r: %.1lf y: %.1lf gr: %.lf", heading,
		Inertial.rotation(), Inertial.yaw(), GetRotation());
		vex::task::sleep(2000);
	}
	Brain.Screen.clearScreen();
}

void GyroTurn(double turn_degrees) {
	//Turns using the gyro for accuracy
	
	double target_heading = heading + turn_degrees;
	Brain.Screen.setCursor(2, 1);
	Brain.Screen.print(
		"START h: %.1lf, d: %.1lf th: %.1lf r: %.1lf y: %.1lf gr: %.lf", heading,
		turn_degrees, target_heading, Inertial.rotation(), Inertial.yaw(),
		GetRotation());
		
	//Right Turn
	if (turn_degrees > 0) {

		while (GetRotation() < target_heading - 30) {
		  LFMotor.spin(directionType::fwd, FAST_TURN_SPEED, velocityUnits::pct);
		  RFMotor.spin(directionType::rev, FAST_TURN_SPEED, velocityUnits::pct);
		  LBMotor.spin(directionType::fwd, FAST_TURN_SPEED, velocityUnits::pct);
		  RBMotor.spin(directionType::rev, FAST_TURN_SPEED, velocityUnits::pct);
		  vex::task::sleep(10);
		}

		while (GetRotation() < target_heading - 3.5) {

		  LFMotor.spin(directionType::fwd, SLOW_TURN_SPEED, velocityUnits::pct);
		  RFMotor.spin(directionType::rev, SLOW_TURN_SPEED, velocityUnits::pct);
		  LBMotor.spin(directionType::fwd, SLOW_TURN_SPEED, velocityUnits::pct);
		  RBMotor.spin(directionType::rev, SLOW_TURN_SPEED, velocityUnits::pct);
		  vex::task::sleep(10);
		}
	} 
	
	//Left Turn
	else if (turn_degrees < 0) {

		while (GetRotation() > target_heading + 30) {

			RFMotor.spin(directionType::fwd, FAST_TURN_SPEED, velocityUnits::pct);
			LFMotor.spin(directionType::rev, FAST_TURN_SPEED, velocityUnits::pct);
			RBMotor.spin(directionType::fwd, FAST_TURN_SPEED, velocityUnits::pct);
			LBMotor.spin(directionType::rev, FAST_TURN_SPEED, velocityUnits::pct);
			vex::task::sleep(10);
		}

		while (GetRotation() > target_heading + 3.5) {

			RFMotor.spin(directionType::fwd, SLOW_TURN_SPEED, velocityUnits::pct);
			LFMotor.spin(directionType::rev, SLOW_TURN_SPEED, velocityUnits::pct);
			RBMotor.spin(directionType::fwd, SLOW_TURN_SPEED, velocityUnits::pct);
			LBMotor.spin(directionType::rev, SLOW_TURN_SPEED, velocityUnits::pct);
			vex::task::sleep(10);
		}
	}

	RFMotor.stop(brakeType::brake);
	LFMotor.stop(brakeType::brake);
	RBMotor.stop(brakeType::brake);
	LBMotor.stop(brakeType::brake);
	Brain.Screen.setCursor(6, 1);
	Brain.Screen.print("FIN r: %.1lf y: %.1lf gr: %.1lf", Inertial.rotation(),
		Inertial.yaw(), GetRotation());

	heading = target_heading;
}

const double ALIGN_SPEED = 31;
const double ALIGN_TIME = 0.65;

double FAST_VELOCITY = 35;
double MEDIUM_VELOCITY = 30;
double SLOW_VELOCITY = 21;
double STIME_VELOCITY = 31;

bool SMOOTH_FLAG = false;
bool BACKUP_FLAG = false;
double STOP_VELOCITY = 25;
double TIME_DELTA = 0.005;
double VELOCITY_DELTA = 0.73;

const int CHECK_DISTANCE = 30000;
const int CHECK_LEFT_TRACKER = 30001;
const int CHECK_RIGHT_TRACKER = 30002;
const int CHECK_TRACKERS = 30003;
const int CHECK_TIME = 30004;
const double WHITE_VAL = 25;
vex::timer gyro_straight_timer;

double SCORE_TIME = 675;
const double CENTER_SCORE_POWER = 90;
const double CENTER_SCORE_TIME = 1000;

const double CORRECTION_FACTOR = 0.7;

void StraightTime(double velocity, double seconds) {
	//Drive Straight for certain amount of time

	LFMotor.spin(directionType::fwd, velocity, velocityUnits::pct);
	RFMotor.spin(directionType::fwd, velocity, velocityUnits::pct);
	LBMotor.spin(directionType::fwd, velocity, velocityUnits::pct);
	RBMotor.spin(directionType::fwd, velocity, velocityUnits::pct);
	vex::task::sleep(int(seconds * 1000));

	LBMotor.stop();
	RBMotor.stop();
	LFMotor.stop();
	RFMotor.stop();
}

void BackwardAlign() {
	//Used to align robot by backing into field perimeter
	
	StraightTime(-ALIGN_SPEED, ALIGN_TIME);
}

double GetInchesFromDegrees(double motor_degrees) {
	//Gets inches traversed from degrees turned in motor encoders
	
	return (motor_degrees * (5.0/3.0) * (WHEEL_CIRCUMFERENCE / 360.0));
}

double ComputeTopVelocity(double stop_distance) {
	//Computes the highest velocity allowed with remaining stopping distance
	
	return (sqrt((2 * (VELOCITY_DELTA / TIME_DELTA) * stop_distance) / 0.5 +
		STOP_VELOCITY * STOP_VELOCITY));
}

double ComputeStopDistance(double top_velocity) {
	//Calculates necessary stopping distance for a velocity
	
	double stop_time = (top_velocity - STOP_VELOCITY) / (VELOCITY_DELTA/TIME_DELTA);
	return (((top_velocity + STOP_VELOCITY )/2.0) * 0.5 * stop_time);
}

void InitializeCheckStop(int stop_method) {
	//Resets stopping mechanism: either the motor encoder for distance or the gyro timer for time
	
	if (stop_method == CHECK_DISTANCE) {
		LFMotor.setRotation(0, rotationUnits::deg);
	}  
	else if (stop_method == CHECK_TIME) {
		gyro_straight_timer.clear();
	}
}

bool CheckStop(int stop_method, double val, double & distance_traveled) {
	//Boolean that is True when a stop is necessary and determined based on the stopping method
	
	if (stop_method == CHECK_DISTANCE) {
		distance_traveled = GetInchesFromDegrees(fabs(LFMotor.rotation(rotationUnits::deg)));
		return (distance_traveled >= fabs(val));
	} 
	else if (stop_method == CHECK_TIME) {
		return (gyro_straight_timer.time(timeUnits::sec) >= val);
	} 
	else if (stop_method == CHECK_LEFT_TRACKER) {
		return (LeftTracker.value(percentUnits::pct) <= val);
	} 
	else if (stop_method == CHECK_RIGHT_TRACKER) {
		return (RightTracker.value(percentUnits::pct) <= val);
	} 
	else if (stop_method == CHECK_TRACKERS) {
		return ((RightTracker.value(percentUnits::pct) <= val) ||
	  (LeftTracker.value(percentUnits::pct) <= val));
	}
	return true;
}

void GyroStraight(double speed, int stop_method, double stop_val) {
	//Utiltizes gyro to correct drive inconsistencies for accurate straight drives

	bool is_forward = (speed > 0);
	speed = fabs(speed);
	InitializeCheckStop(stop_method);

	double top_velocity = speed;
	double total_distance = stop_val;
	double distance_traveled = 0.0, stop_distance = 0.0;
	bool do_smooth = (SMOOTH_FLAG &&
		(stop_method == CHECK_DISTANCE) &&
		(top_velocity >= FAST_VELOCITY));
	if (do_smooth) {
		stop_distance = ComputeStopDistance(top_velocity);
		if (2*stop_distance > total_distance) {
			stop_distance = total_distance/2.0;
			top_velocity = ComputeTopVelocity(stop_distance);
			}
	}
	while (!CheckStop(stop_method, stop_val, distance_traveled)) {
		double error = (GetRotation() - heading) / 90.0;
		double speed_correction = error * speed * CORRECTION_FACTOR;
		if (is_forward) {
			LFMotor.spin(directionType::fwd, speed - speed_correction,
			velocityUnits::pct);
			RFMotor.spin(directionType::fwd, speed + speed_correction,
			velocityUnits::pct);
			LBMotor.spin(directionType::fwd, speed - speed_correction,
			velocityUnits::pct);
			RBMotor.spin(directionType::fwd, speed + speed_correction,
			velocityUnits::pct);
		} 
		else {
			LFMotor.spin(directionType::rev, speed + speed_correction,
			velocityUnits::pct);
			RFMotor.spin(directionType::rev, speed - speed_correction,
			velocityUnits::pct);
			LBMotor.spin(directionType::rev, speed + speed_correction,
			velocityUnits::pct);
			RBMotor.spin(directionType::rev, speed - speed_correction,
			velocityUnits::pct);
		}
		if (do_smooth) {
			if (((total_distance - distance_traveled) <= stop_distance) && (speed > STOP_VELOCITY)) {
				speed -= VELOCITY_DELTA;
			} 
			else if (speed < top_velocity) {
				speed += VELOCITY_DELTA;
			}
		}
		task::sleep(TIME_DELTA*1000);
	}
	if (do_smooth) {
		LFMotor.stop(brakeType::coast);
		RFMotor.stop(brakeType::coast);
		RBMotor.stop(brakeType::coast);
		LBMotor.stop(brakeType::coast);
	} 
	else {
		RBMotor.stop();
		RFMotor.stop();
		LFMotor.stop();
		LBMotor.stop();
	}
}

void GyroStraightTime(double speed, double time_constraint) {
	//Gyro-corrected straight drive based on time for stops
	
	GyroStraight(speed, CHECK_TIME, time_constraint);
}

void GyroStraightUntilLeftWhite(double speed) {
	//Gyro-corrected straight drive based on left line tracker for stop
	
	GyroStraight(speed, CHECK_LEFT_TRACKER, WHITE_VAL);
}

void GyroStraightUntilRightWhite(double speed) {
	//Gyro-corrected straight drive based on right line tracker for stop
	
	GyroStraight(speed, CHECK_RIGHT_TRACKER, WHITE_VAL);
}

void GyroStraightUntilWhite(double speed) {
	//Gyro-corrected straight drive based on either line tracker of two for stop
	
	GyroStraight(speed, CHECK_TRACKERS, WHITE_VAL);
}

void GyroStraightDistance(double speed, double inches) {
	//Gyro-corrected straight drive based on distance for stop
	
	GyroStraight(speed, CHECK_DISTANCE, inches);
}

void StoreOn(){
	//Turns storing mechanism on for robot during autonomous
	
	LIntake.spin(fwd, 100, pct);
	RIntake.spin(fwd, 100, pct);
	TRollers.spin(reverse, 100, pct);
	BRollers.spin(fwd, 100, pct);
}

void Shoot(int balls){
	//Shoots the ball with 4 modes that shoot for shorter and longer times (more balls = more time needed to shoot)
	
	if(balls==1){
		TRollers.spin(fwd, 100, pct);
		BRollers.spin(fwd, 100, pct);
		LIntake.spin(reverse,100,pct);
		RIntake.spin(reverse,100,pct);
		vex::task::sleep(500);
	}
	else if (balls==2){
		TRollers.spin(fwd, 100, pct);
		BRollers.spin(fwd, 100, pct);
		vex::task::sleep(150);
	}
	else if (balls==3){
		TRollers.spin(fwd, 100, pct);
		BRollers.spin(fwd, 100, pct);
		vex::task::sleep(500);
	}
	else if (balls==4){
		TRollers.spin(fwd, 100, pct);
		BRollers.spin(fwd, 100, pct);
		LIntake.spin(reverse,100,pct);
		RIntake.spin(reverse,100,pct);
		vex::task::sleep(750);
	}
	TRollers.stop();
	BRollers.stop(); 
}

void MotorOff(){
	//Turns roller mechanism motors off
	
	LIntake.stop();
	RIntake.stop();
	TRollers.stop();
	BRollers.stop();
	LIntake.stop();
	RIntake.stop();
}

void Intake(int mode){
	//Two modes for intake: one for collecting balls and the other for releasing balls 
	
	if (mode==1){
		LIntake.spin(forward,100,pct);
		RIntake.spin(forward,100,pct);
	}
	if (mode==2){
		LIntake.spin(reverse, 100, pct);
		RIntake.spin(reverse, 100, pct);
		TRollers.spin(fwd, 100, pct);
		BRollers.spin(reverse, 100, pct);
	}
}

void sleep(double secs){
	//Sleeps the program for said amount of seconds
	
	vex::task::sleep(secs*1000);
}
