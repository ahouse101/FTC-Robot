// Globals:
int spinnerSpeed = 100;				// The speed of the "spinner" motor to be used when raising the flag
bool spongeClawDown = false; 		// If the SpongeClaw is currently in the up position
bool spongeClawClosed = false;	// If the SpongeClaw is currently in the closed position

// This task deals with the 8-way directional pad (TopHat).
// This DPad governs the movement of the robot's Tower, which uses two motors in series.
// The top and bottom directions move the tower up and down by "marks."
// The side directions move the tower to fully extended/collapsed positions.
task DPadTowerMove()
{
	while (true)
	{
		getJoystickSettings(joystick);

		byte padValue = getDriveDPad();

		switch (padValue)
		{
			case 0:		// Extend the tower by one mark

				break;
			case 2:		// Fully extend the tower

				break;
			case 4:		// Collapse the tower by one mark

				break;
			case 6:		// Fully collapse the tower

				break;
			default:		// Do nothing
				break;
		}

		// TEMPORARY
		if (joy2Btn(1))
		{
			motor[towerHigh] = 0;
			motor[towerLow] = 25;
		}
		else
		{
			motor[towerHigh] = 0;
			motor[towerLow] = 0;
		}
		// END TEMPORARY

		wait1Msec(10);	// Hand control back to the task scheduler
	}
}


task SpinnerSpin()
{
	while (true)
	{
		getJoystickSettings(joystick);

		if (getSpinnerButton())
		{
			spinnerSpeed = 100;
		}
		else
		{
			spinnerSpeed = 0;
		}

		motor[spinner] = spinnerSpeed;

		wait1Msec(10);
	}
}

void MoveClawDown()
{

}

void MoveClawUp()
{

}

void ToggleClaw()
{

}

// This task deals with button 2 (lowest in the group of four) and the two bumpers.
// These control the SpongeClaw:
// Bumpers move up and down, button toggles the closed/open position.
task SpongeClawMove()
{
	while (true)
	{
		getJoystickSettings(joystick);
		bool up = getClawUpBumper();				// True if depressed, false if not
		bool down = getClawDownBumper();			// == above
		bool toggle = getClawToggleButton();	// == above

		if (up)
		{
			if (spongeClawDown) MoveClawUp();
		}
		else if (down)
		{
			if (!spongeClawDown) MoveClawDown();
		}

		if (toggle)
		{
			ToggleClaw();
		}

		wait1Msec(32);
	}
}
