 //Georgia State Winning (92287X) and State Runner-Up (92287A) Robot Skills Runs
 //Programming Portion: Max Score of 106
 
	SetupMotors();
	//Deploy and First Goal
	Shoot(2);
	GyroTurn(90);
	GyroStraightTime(-31,1);
	ResetHeading();

	//Second Goal
	StoreOn();
	GyroStraightDistance(35,2);
	GyroTurn(-45);
	GyroStraightUntilRightWhite(35);
	GyroTurn(-45);
	GyroStraightUntilLeftWhite(35);
	GyroStraightDistance(35,2);
	MotorOff();
	GyroTurn(-90);
	GyroStraightTime(35,1);
	Shoot(3);

	//Third Goal
	GyroStraightUntilLeftWhite(-35);
	GyroTurn(90);
	StoreOn();
	GyroStraightDistance(35,46);
	GyroTurn(-45);
	MotorOff();
	GyroStraightTime(35,1);
	Shoot(3);

	//Fourth Goal
	GyroStraightUntilRightWhite(-35);
	GyroStraightDistance(-35, 6);//10
	GyroTurn(135);
	StoreOn();
	GyroStraightUntilRightWhite(35);
	GyroStraightDistance(35,2);
	GyroTurn(-90);
	MotorOff();
	GyroStraightTime(30,1);
	Shoot(3);

	//Fifth Goal
	GyroStraightDistance(-35,6);
	GyroTurn(90);
	StoreOn();
	GyroStraightDistance(35,36);
	GyroTurn(-90);
	GyroStraightTime(35,.75);
	GyroStraightDistance(-35,6);
	GyroTurn(90);
	GyroStraightUntilRightWhite(35);
	GyroTurn(-35);
	MotorOff();
	GyroStraightTime(35,1);
	Shoot(3);

	//Possible Alignment
	GyroStraightUntilRightWhite(-35);
	GyroTurn(125);
	ResetHeading();
	StoreOn();

	//Sixth Goal
	GyroStraightUntilLeftWhite(35);
	GyroStraightDistance(35,2);
	MotorOff();
	GyroTurn(-90);
	GyroStraightTime(35,1);
	Shoot(3);

	//Seventh Goal
	GyroStraightUntilLeftWhite(-35);
	GyroTurn(90);
	StoreOn();
	GyroStraightDistance(35,48);
	GyroTurn(-45);
	MotorOff();
	GyroStraightTime(35,1);
	Shoot(3);

	//Eighth Goal
	GyroStraightUntilRightWhite(-35);
	GyroStraightDistance(-35, 9);//10
	GyroTurn(135);
	StoreOn();
	GyroStraightUntilRightWhite(35);
	GyroStraightDistance(35,1);
	GyroTurn(-90);
	MotorOff();
	GyroStraightTime(35,1);
	Shoot(3);
					 
	//Final Center Goal
	GyroStraightDistance(-35,6);
	GyroTurn(180);
	StoreOn();
	GyroStraightDistance(35,24);
	GyroTurn(20);
	GyroStraightDistance(35,6);
	//GyroTurn(-5);
	GyroStraightTime(100,1.5);
	//GyroStraightDistance(50,6);
	MotorOff();
	//GyroStraightTime(50,1.5);
	GyroTurn(-35);
	Shoot(3);
