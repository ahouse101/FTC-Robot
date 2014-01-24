// This task deals with the 8-way directional pad (TopHat).
// This DPad governs the movement of the robot's Tower, which uses two motors in series.
// The top and bottom directions move the tower up and down by "marks."
// The side directions move the tower to fully extended/collapsed positions.
task JoystickTowerMove()
{
	while (true)
	{
		getJoystickSettings(joystick);

		if (abs(getTowerDualJoystick()) > 10)	// We're using the main joystick
		{
			int scaledSpeed = getTowerDualJoystick() * 100 / 127;
			motor[towerHigh] = scaledSpeed;
			motor[towerLow] = scaledSpeed;
		}
		else if 	(abs(getTowerSingleJoystick()) > 10)	// The single-motor joystick is being used instead
		{
			int scaledSpeed = getTowerSingleJoystick() * 100 / 127 / 2;
			if (towerLowMotorChosen)
			{
				motor[towerLow] = scaledSpeed;
				motor[towerHigh] = 0;
			}
			else
			{
				motor[towerLow] = 0;
				motor[towerHigh] = scaledSpeed;
			}
		}
		else	// Neither joystick has been moved outside the deadzone
		{
			motor[towerLow] = 0;
			motor[towerHigh] = 0;
		}

		wait1Msec(10);	// Hand control back to the task scheduler
	}
}

task TowerMotorChange()
{
	while (true)
	{
		getJoystickSettings(joystick);

		if (getTowerLowButton()) towerLowMotorChosen = true;
		else if (getTowerHighButton()) towerLowMotorChosen = false;

		wait1Msec(10);	// Hand control back to the task scheduler
	}
}

task SpinnerSpin()
{
	while (true)
	{
		getJoystickSettings(joystick);

		if (getSpinnerFastButton())
		{
			spinnerSpeed = 100;
		}
		else if (getSpinnerSlowButton())
		{
			spinnerSpeed = 20;
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
	servo[ClawLeftVertical] = clawDownPosition;
	servo[ClawRightVertical] = 220 - clawDownPosition;
	wait1Msec(200);
	spongeClawDown = true;
}

void MoveClawUp()
{
	servo[ClawLeftVertical] = clawUpPosition;
	servo[ClawRightVertical] = 220 - clawUpPosition;
	wait1Msec(200);
	spongeClawDown = false;
}

void ToggleClaw()
{
	if (spongeClawClosed)
	{
		servo[ClawLeft] = 0;
		servo[ClawRight] = 255;
	}
	else
	{
		servo[ClawLeft] = clawClosedPosition;
		servo[ClawRight] = 255 - clawClosedPosition;
	}
	wait1Msec(200);
	spongeClawClosed = !spongeClawClosed;
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
