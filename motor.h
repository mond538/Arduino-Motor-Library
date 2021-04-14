/*
 * @Autor: Mond
 * @Date: 2021-04-13 22:32:13
 * @LastEditors: Mond
 * @LastEditTime: 2021-04-14 23:21:12
 * @Description: An library for motor and its encoder
 */
#ifndef motor_H
#define motor_H

#include "Arduino.h"
/**
 * @description: define a motor
 * @param {int} pA: Encoder A phase port number
 * @param {int} pB: Encoder B phase port number
 * @param {int} MOTOR_S: The port number that controls the motor speed
 * @param {int} MOTOR_D1: The port number that controls the direction of motor rotation -A
 * @param {int} MOTOR_D2: The port number that controls the direction of motor rotation -B
 * @param {int} *PPs: Variable address for storing the number of encoder pulses
 * @param {bool} FC: FALLING->0; CHANGE->1; 
 */
class motor
{
public:
	long m;
	float velocity;
	long *pps;
	motor(int pA, int pB, int MOTOR_S, int MOTOR_D1, int MOTOR_D2, long *PPs, bool FC);
	void Init();
	void MotorControl(int sp);
	void Count(int flag);
	void SpeedDetection(int sampletime, int resolution);

private:
	int pinA;
	int pinB;
	int MOTOR_SP;
	int MOTOR_PIN1;
	int MOTOR_PIN2;
	bool ForC;
	int adjust(int sp);
};
#endif