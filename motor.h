/*
 * @Autor: Mond
 * @Date: 2021-04-13 22:32:13
 * @LastEditors: Mond
 * @LastEditTime: 2021-04-13 22:32:30
 * @Description: An library for motor and its encoder
 */
#ifndef motor_H
#define motor_H

#include "Arduino.h"
class motor
{
public:
	long m;
	float velocity;
	int *pps;
	motor(int pA, int pB, int MOTOR_S, int MOTOR_D1, int MOTOR_D2, int *mill, bool FC);
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