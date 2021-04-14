#include "motor.h"
motor::motor(int pA, int pB, int MOTOR_S, int MOTOR_D1, int MOTOR_D2, long *PPs, bool FC)
{
	pinA = pA;
	pinB = pB;
	MOTOR_SP = MOTOR_S;
	MOTOR_PIN1 = MOTOR_D1;
	MOTOR_PIN2 = MOTOR_D2;
	pps = PPs;
	ForC = FC;
}
/**
 * @description: initial a motor
 * @param {*}
 * @return {*}
 */
void motor::Init()
{
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	pinMode(MOTOR_SP, OUTPUT);
	pinMode(MOTOR_PIN1, OUTPUT);
	pinMode(MOTOR_PIN2, OUTPUT);
}

/**
 * @description: control motor speed
 * @param {int} sp: motor speed; -255 to 255
 * @return {*}
 */
void motor::MotorControl(int sp)
{
	if (sp > 255)
		sp = 255;
	else if (sp < -255)
		sp = -255;

	if (sp > 0)
	{
		digitalWrite(MOTOR_PIN1, LOW);
		digitalWrite(MOTOR_PIN2, HIGH);
		analogWrite(MOTOR_SP, sp);
	}
	else if (sp < 0)
	{
		digitalWrite(MOTOR_PIN1, HIGH);
		digitalWrite(MOTOR_PIN2, LOW);
		analogWrite(MOTOR_SP, -1 * sp);
	}
	else
	{
		digitalWrite(MOTOR_PIN1, LOW);
		digitalWrite(MOTOR_PIN2, LOW);
	}
}

/**
 * @description: count the encoder
 * usage: 
 * 	void Count()
 * 		myMotor.Count(1);
 * 	void setup()
 * 	...	  attachInterrupt(5, Count, CHANGE); ... // CHANGE -> FC=1; FALLING -> FC=0
 * @param {int} flag: adjust the direction of encoder
 * @return {*}
 */
void motor::Count(int flag)
{
	int now_pps = *pps;
	if (ForC)
	{
		if (digitalRead(pinA) == LOW)
		{
			if (digitalRead(pinB) == HIGH)
				*pps = now_pps - flag;
			else if (digitalRead(pinB) == LOW)
				*pps = now_pps + flag;
		}
		else
		{
			if (digitalRead(pinB) == HIGH)
				*pps = now_pps + flag;
			else if (digitalRead(pinB) == LOW)
				*pps = now_pps - flag;
		}
	}
	else
	{
		if (digitalRead(pinB) == HIGH)
			*pps = now_pps - flag;
		else if (digitalRead(pinB) == LOW)
			*pps = now_pps + flag;
	}
}

/**
 * @description: Calculate the motor speed and rotation angle
 * usage:
 * void SpeedDetection()
	{
	  detachInterrupt(5);
	  myMotor.SpeedDetection(t, 390);
	  attachInterrupt(5, Count, CHANGE);
	}
	void setup()
	... MsTimer2::set(t, SpeedDetection);
  	MsTimer2::start(); ...
 * @param {int} sampletime	
 * @param {int} resolution
 * @return {*}
 */
void motor::SpeedDetection(int sampletime, int resolution)
{
	if (ForC)
		resolution *= 2;
	int pps_val = *pps;
	velocity = (float)pps_val * (1000 / sampletime) / (float)(resolution);
	m += pps_val * 360.0 / (float)(resolution);
	*pps = 0;
}
