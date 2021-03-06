#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     towerLow,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     spinner,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     towerHigh,     tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    ClawLeftVertical,     tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    ClawRightVertical,    tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    ClawLeft,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    ClawRight,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
	Gamepad Control
	Alex House

	This program is the tele-op program for the FTC challenge. It uses multi-threading
	in order to process many simultaneous actions at once. Sets of gamepad controls
	are encapsulated in individual tasks, which all run simultaneously and are started
	in the main task, which does nothing.

	This version supports:
		- Driving with the driving gamepad's D-pad
		- Switching between drive speeds with the driving gamepad's bumpers
		- Spinning the spinner motor to raise the flag with the action gamepad's buttons 3 and 4
		- Moving the Tower with the action gamepad's joysticks
		- Changing the single motor which will be moved in the tower with the action gamepad's triggers
		- Moving the SpongeClaw up and down with the action gamepad's bumpers
		- Opening and closing the SpongeClaw with the actions gamepad's button 2.
*/

// Constants:
const int clawDownPosition = 0;
const int clawUpPosition = 75;
const int clawClosedPosition = 135;

// Action Globals:
int spinnerSpeed = 100;				// The speed of the "spinner" motor to be used when raising the flag
bool spongeClawDown = true; 		// If the SpongeClaw is currently in the up position
bool spongeClawClosed = false;	// If the SpongeClaw is currently in the closed position
bool towerLowMotorChosen = false;// If the low motor on the tower should be moved when we're moving one motor at a time

// Driver Globals:
byte drivePower = 100;

#include "JoystickDriver.c"
#include "GamepadAccessors.h"
#include "DriverController.h"
#include "ActionController.h"

void initializeRobot()
{
	servo[ClawLeftVertical] = clawDownPosition;
	servo[ClawRightVertical] = 220 - clawDownPosition;
	servo[ClawLeft] = 0;
	servo[ClawRight] = 255;
}

task main()
{
	initializeRobot();

	waitForStart();

	// Tasks related to the Driver controller
	StartTask(DPadDrive);
	StartTask(DrivingSpeedChange);

	// Tasks related to the Action controller
	StartTask(SpinnerSpin);
	StartTask(JoystickTowerMove);
	StartTask(TowerMotorChange);
	StartTask(SpongeClawMove);

	while(true)
	{
		wait1Msec(1000);	// Our gamepads do all of the work in this mode, and other tasks handle input.
	}
}
