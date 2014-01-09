int getTowerDualJoystick()
{
	return joystick.joy2_y1;
}

int getTowerSingleJoystick()
{
	return joystick.joy2_y2;
}

bool getTowerLowButton()
{
	return joy2Btn(7) == 1;
}

bool getTowerHighButton()
{
	return joy2Btn(8) == 1;
}

int getDriveDPad()
{
	return joystick.joy1_TopHat;
}

bool getFastDriveBumper()
{
	return joy1Btn(5) == 1;
}

bool getSlowDriveBumper()
{
	return joy1Btn(6) == 1;
}

bool getSpinnerFastButton()
{
	return joy2Btn(3) == 1;
}

bool getSpinnerSlowButton()
{
	return joy2Btn(4) == 1;
}

bool getClawDownBumper()
{
	return joy2Btn(5) == 1;
}

bool getClawUpBumper()
{
	return joy2Btn(6) == 1;
}

bool getClawToggleButton()
{
	return joy2Btn(2) == 1;
}
