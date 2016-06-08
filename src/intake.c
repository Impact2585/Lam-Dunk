#include "main.h"


void intake() {

	//sets intake
	if (joystickGetDigital(1, 6, JOY_DOWN))
	{
		motorSet(INTAKE_MOTOR, 127);
	}
	else if (joystickGetDigital(1, 8, JOY_DOWN))
	{
		motorSet(INTAKE_MOTOR, -127);
	}

	else
	{
		motorSet(INTAKE_MOTOR, 0);
	}

	//sets lift
	if (joystickGetDigital(1, 6, JOY_DOWN))
	{
		motorSet(LIFT_MOTOR, 127);
	}
	else if (joystickGetDigital(1, 5, JOY_UP))
	{
		motorSet(LIFT_MOTOR, -127);
	}
	else
	{
		motorSet(LIFT_MOTOR, 0);
	}
}



