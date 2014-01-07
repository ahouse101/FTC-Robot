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

bool getSpinnerButton()
{
	return joy2Btn(3) == 1;
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
