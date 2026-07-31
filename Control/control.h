#include "sys.h"


#define  Limit		2000			//PWM波限幅

//速度环PID
#define   Kp1   	70
#define   Ki1     	1.75
#define   Kd1  		0.0



//陀螺仪PID
#define   Kp3       1
#define   Ki3       0
#define   Kd3  	    0

extern float KP1,KI1,KD1;
extern float Speed_Middle;	

void Control(void);
void Set_Pwm(int Left, int Right);
float PWM_Limit(float IN,float max,float min);
float PID_A(float Encoder,float Target);
float PID_B(float Encoder,float Target);
float Target_Control(float now,float target);
float GYRO_Control(float now,float target);
