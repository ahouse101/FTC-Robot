// This task deals with the 8-way directional pad (TopHat).
// This DPad controls the robot's two drive motors.
task DPadDrive()
{
	while(true)
	{
		getJoystickSettings(joystick);

		byte padValue = getDriveDPad();

		switch (padValue)
		{
			case 0:		// Drive Forward
				motor[leftDrive] = -drivePower;
				motor[rightDrive] = -drivePower;
				break;
			case 1:		// Turn right
				motor[leftDrive] = -drivePower;
				motor[rightDrive] = 0;
				break;
			case 2:		// Spin right
				motor[leftDrive] = -drivePower;
				motor[rightDrive] = drivePower;
				break;
			case 3:		// Turn backward right
				motor[leftDrive] = 0;
				motor[rightDrive] = drivePower;
				break;
			case 4:		// Drive Backward
				motor[leftDrive] = drivePower;
				motor[rightDrive] = drivePower;
				break;
			case 5:		// Turn backward left
				motor[leftDrive] = drivePower;
				motor[rightDrive] = 0;
				break;
			case 6:		// Spin left
				motor[leftDrive] = drivePower;
				motor[rightDrive] = -drivePower;
				break;
			case 7:		// Turn left
				motor[leftDrive] = 0;
				motor[rightDrive] = -drivePower;
				break;
			default:	// Turn motors off
				motor[leftDrive] = 0;
				motor[rightDrive] = 0;
		}

		wait1Msec(10);	// Hand control back to the task scheduler
	}
}


// This task deals with the two triggers (buttons 7+8).
// The triggers switch between full power (100%, left
//	trigger) and low power (20%, right trigger) so that
// the driver has fine and rough control over the robot.
task DrivingSpeedChange()
{
	while(true)
	{
		getJoystickSettings(joystick);
		bool fast = getFastDriveBumper();	// True if depressed, false if not
		bool slow = getSlowDriveBumper();	// == above

		// Note that the fast trigger overrides the slow trigger, so if both
		// are held down, the robot will maintain 100% speed.
		if (fast)
		{
			drivePower = 100;
		}
		else if (slow)
		{
			drivePower = 5;
		}

		wait1Msec(10); // Hand control back to the task scheduler
	}
}
