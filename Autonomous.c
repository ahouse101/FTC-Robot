#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, PIDControl, encoder)
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
	RoboLancers Autonomous
	Alex House

	The autonomous program for FTC
*/

// Constants:
const int clawDownPosition = 0;
const int clawUpPosition = 75;
const int clawClosedPosition = 130;

bool IRisLeft = true;

int IRDirection = 0;
  	int _dirAC = 0;
	int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
	int acS1, acS2, acS3, acS4, acS5 = 0;
	int _dirEnh, _strEnh;

#include "drivers\hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

void raiseClaw()
{
	servo[ClawLeftVertical] = clawUpPosition;
	servo[ClawRightVertical] = 220 - clawUpPosition;
}

void lowerClaw()
{
	servo[ClawLeftVertical] = clawDownPosition;
	servo[ClawRightVertical] = 220 - clawDownPosition;
}

void closeClaw()
{
	servo[ClawLeft] = clawClosedPosition;
	servo[ClawRight] = 255 - clawClosedPosition;
}

void openClaw()
{
	servo[ClawLeft] = 0;
	servo[ClawRight] = 255;
}

void initializeRobot()
{
  	tHTIRS2DSPMode _mode = DSP_1200;

	lowerClaw();
	closeClaw();

	wait1Msec(1000);

	raiseClaw();
}

void drive(byte power)
{
	motor[leftDrive] = power;
	motor[rightDrive] = power;
}

void driveToIRSensor()
{
	drive(5);

	while (true)
	{
		IRDirection = HTIRS2readDCDir(HTIRS2);
   	if (IRDirection < 0)
   		break; // I2C read error occurred
   	else if (IRDirection == 3)
		{
			IRisLeft = true;
			break; // Beacon is on the left.
		}
		else if (IRDirection == 7)
		{
			IRisLeft = false;
			break; // Beacon is on the right.
		}
	}

	wait1Msec(500);
	drive(0);
}

void faceIRSensor()
{
	int power = 10;

	while (true)
	{
		if (IRisLeft)
		{
			motor[rightDrive] = power;
			motor[leftDrive] = -power;
		}
		else
		{
			motor[rightDrive] = -power;
			motor[leftDrive] = power;
		}

		IRDirection = HTIRS2readDCDir(HTIRS2);
   	if (IRDirection < 0)
   		break; // I2C read error occurred
   	else if (IRDirection == 3 || IRDirection == 6)
   	{
   		power = 2;
		}
   	else if (IRDirection == 5)
   	{
   		break;
		}
	}

	drive(0);
}

task main()
{
	initializeRobot();

	waitForStart();

	driveToIRSensor();
	faceIRSensor();
}
