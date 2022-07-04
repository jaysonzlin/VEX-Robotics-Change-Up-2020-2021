#ifndef STUFF_H
#define STUFF_H

void SetupMotors(void);
void SetupInertial(void);
void ResetHeading(void);
double GetRotation(void);
void PrintGyro(void);
void GyroTurn(double turn_degrees);

void StraightTime(double velocity, double seconds);
void BackwardAlign(void);
double GetInchesFromDegrees(double motor_degrees);
double ComputeTopVelocity(double stop_distance);
double ComputeStopDistance(double top_velocity);

void InitializeCheckStop(int stop_method);
bool CheckStop(int stop_method, double val, double & distance_traveled);
void GyroStraight(double speed, int stop_method, double stop_val);
void GyroStraightTime(double speed, double time_constraint);
void GyroStraightUntilLeftWhite(double speed);
void GyroStraightUntilRightWhite(double speed);
void GyroStraightUntilWhite(double speed);
void GyroStraightDistance(double speed, double inches);
void StoreOn(void);
void Shoot(int balls);
void MotorOff(void);
void Intake(int mode);
void sleep(int secs);

#endif 
