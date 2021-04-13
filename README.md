# Motor Library for Arduino

这是一个用于控制电机的Arduino库，使用该库可以方便的控制电机的转向转速，对于带有编码器的电机，还可以方便地得到编码器的读数。

作者使用该库的环境是：

* Arduino Mega
* motor: MG513P3012V
* 390分辨率的霍尔编码器
* TB6612电机驱动板

## 马达定义及初始化

使用如下语句定义一个马达对象：

```cpp
motor myMotor(MOTOR_A, MOTOR_B, MOTOR_PWM, MOTOR_PIN1, MOTOR_PIN2, &pps, 1))
```

`MOTOR_A`和`MOTOR_B`分别为电机驱动板上控制方向的两根线所接端口；`MOTOR_PWM`为PWM端口；`MOTOR_PIN1`和`MOTOR_PIN2`为编码器的A相和B相；`pps`为存储编码器返回脉冲数的一个变量；最后一个参数是控制计算方式的一个变量。当为1时，编码器的精度成为原来的两倍。此时编码器计数中断应为`CHANGE`方式，为0时，则是`FALLING`方式，分辨率即为原分辨率。

定义马达后，在`setup`函数里使用`myMotor.Init()`对马达进行初始化。

## 控制马达转动

使用如下语句控制马达转动：

```cpp
myMotor.MotorControl(100);
```

参数代表了输入电机的PWM值，范围为-255到255。当该值为负时，电机反转。

## 编码器使用

编码器使用较为复杂，以如下例程做为参考：

```cpp
#include <Arduino.h>
#include <motor.h>
#include <PinChangeInt.h>
#include <MsTimer2.h>
/*********************定义电机引脚 ***********************/
#define MOTORRA_PWM 4
#define MOTORRA_PIN1 22
#define MOTORRA_PIN2 23
#define MOTORRA_A 18
#define MOTORRA_B 42
/********************************************************/
int pps = 0;
/**********************定义马达***********************************************/
motor motorRA(MOTORRA_A, MOTORRA_B, MOTORRA_PWM, MOTORRA_PIN1, MOTORRA_PIN2, &pps, 1);
/****************************************************************************/

const int t = 50; //定时中断所隔时间

void Count1()
{
  motorRA.Count(-1);
  /*该函数用于计数编码器返回的脉冲；有一个参数的作用在于：
  如果你写1时发现，电机正转编码器脉冲数却在减少，那么你改成-1就正常了*/
}

void Disp(int i)
{
  //串口显示函数，调试用
  Serial.print(motorRA.m);
  //m为电机转过的角度，单位理论上为度
  Serial.print(",");
  Serial.println(motorRA.velocity);
  //velocity为电机转速，单位理论上为转/s
}

void SpeedDetection()
{
  detachInterrupt(5);
  motorRA.SpeedDetection(t, 390); 
  //该函数用来计算电机速度和电机转过的角度，单位理论上分别为r/s和deg
  attachInterrupt(5, Count1, CHANGE);
}

void setup()
{
  Serial.begin(9600);

  motorRA.Init();

  attachInterrupt(5, Count1, CHANGE); 
  //这里如果是CHANGE的话，定义电机的最后一个参数为1，如果是FALLING的话，最后一个参数即为0
  MsTimer2::set(t, SpeedDetection);
  MsTimer2::start();
}

void loop()
{
  Disp(0);
}

```
