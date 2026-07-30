#include "control.h"
#include "Sensor.h"

#define  Limit		2000			//PWM波限幅

//速度环PID
#define   Kp1   	70
#define   Ki1     	1.75
#define   Kd1  		0.0


//陀螺仪PID
#define   Kp3       1
#define   Ki3       0
#define   Kd3  	    0




/*************************************/
float Speed_Middle = 30;			                    //中值速度
int Motor_Left, Motor_Right;		                    //左右马达占空比

extern float Yaw;
extern volatile int mode;
extern volatile int flag;
extern volatile int32_t EncoderA_VEL, EncoderB_VEL;     //编码器测得当前速度	


/**************************************************************************
Function: Control function
Input   : none
Output  : none
函数功能：控制小车巡线
入口参数：无
返回  值：无
**************************************************************************/
void Control(void)
{
    float TargetA, TargetB;                         //目标速度
    float bias1, bias2, bias;                       //巡线、陀螺仪偏差


    /* 模式一、二 */

    bias = Incremental_Quantity();    

    /* 模式三、四 */

    TargetA = Speed_Middle - bias;
    TargetB = Speed_Middle + bias;
    // TargetA = 30;
    // TargetB = 30;

    Motor_Left  = (int)PWM_Limit(PID_A(EncoderA_VEL,TargetA), Limit, -Limit);
    Motor_Right = (int)PWM_Limit(PID_B(EncoderB_VEL,TargetB), Limit, -Limit);
    Set_Pwm(Motor_Left, Motor_Right);
}




/*
    函数功能：角度PID
    IN: 当前值，目标值
    OUT: 输出值
*/
float GYRO_Control(float now,float target)
{
	static float Bias, Last_bias, Last2_bias, Pwm;
	Bias = target-now;

    while (Bias > 180.0f)  Bias -= 360.0f;
    while (Bias < -180.0f) Bias += 360.0f;
	Pwm += Kp3 * (Bias - Last_bias) + Ki3 * Bias + Kd3 * (Bias - 2 * Last_bias + Last2_bias);

	Last_bias = Bias;
	Last2_bias = Last_bias;
	return Pwm;
}





/*
    函数功能：设置PWM比较值
    IN: 左马达占空比，右马达占空比
    OUT: 无
*/
void Set_Pwm(int Left, int Right)
{
    if(Left > 0)    {AIN1_High;AIN2_Low;}      //左正转
    else            {AIN1_Low;AIN2_High;}      //左反转
    DL_Timer_setCaptureCompareValue(PWM_0_INST, myabs(Left), DL_TIMER_CC_0_INDEX);

    if(Right > 0)   {BIN1_High;BIN2_Low;}      //右正转
    else            {BIN1_Low;BIN2_High;}      //右反转
    DL_Timer_setCaptureCompareValue(PWM_0_INST, myabs(Right), DL_TIMER_CC_1_INDEX);
}





/*=================== 增量式PID控制设计 ===================*/
//左A轮PID
float PID_A(float Encoder,float Target)
{
	static float Bias, Last_bias, Last2_bias, Pwm;
	Bias = Target - Encoder;
	Pwm += Kp1 * (Bias - Last_bias) + Ki1 * Bias + Kd1 * (Bias - 2 * Last_bias + Last2_bias);

	Last_bias = Bias;
	Last2_bias = Last_bias;
	return Pwm;
}



//右B轮PID
float PID_B(float Encoder,float Target)
{
	static float Bias, Last_bias, Last2_bias, Pwm;
	Bias = Target-Encoder;
	Pwm += Kp1 * (Bias - Last_bias) + Ki1 * Bias + Kd1 * (Bias - 2 * Last_bias + Last2_bias);

	Last_bias = Bias;
	Last2_bias = Last_bias;
	return Pwm;
}




/* 
    函数功能：限幅 + 绝对值函数
    IN: 输入值
    max: 最大值
    min: 最小值
    OUT: 输出值
*/
float PWM_Limit(float IN,float max,float min)
{
	float OUT = IN;
	if(OUT > max) OUT = max;
	if(OUT < min) OUT = min;
	return OUT;
}





















// #define  Limit		1500			//PWM?????

// //????PID
// #define   Kp1   	0.5
// #define   Ki1     	1
// #define   Kd1  		0.1


// //??????PID
// #define   Kp3       0.5
// #define   Ki3       0
// #define   Kd3  	    0




// /*************************************/
// float Speed_Middle = 10;			                    //??????
// int Motor_Left, Motor_Right;		                    //????????????

// extern float Yaw;
// extern volatile int mode;
// extern volatile int flag;
// extern volatile int32_t EncoderA_VEL, EncoderB_VEL;     //??????????????	


// /**************************************************************************
// Function: Control function
// Input   : none
// Output  : none
// ?????????????§³?????
// ??????????
// ????  ?????
// **************************************************************************/
// void Control(void)
// {
//     float TargetA, TargetB;                         //??????
//     float bias1, bias2, bias;                       //?????????????

//     /* ??????? */
//     if(mode == 1 || mode == 2)
//     {
//         if(flag == 1)       bias = GYRO_Control(Yaw, 0);
//         else if(flag == 2)  bias = Incremental_Quantity();
//         else if(flag == 3){
//             float MyYaw;

//             Yaw = 0;
            
//             if(Yaw > 0) MyYaw = Yaw - 180;
//             else MyYaw = Yaw + 180;
//             bias = GYRO_Control(MyYaw, 5);        
//         }
//         else if(flag == 4) bias = Incremental_Quantity();
        
//     }

//     /* ???????? */
//     else if(mode == 3 || mode == 4)
//     {
//         if(flag == 1)       bias = GYRO_Control(Yaw, 0);
//         else if(flag == 2)  bias = Incremental_Quantity();
//         else if(flag == 3){
//             float MyYaw;
//             if(Yaw > 0) MyYaw = Yaw - 180;
//             else MyYaw = Yaw + 180;
//             bias = GYRO_Control(Yaw, -110);        
//         }
//         else if(flag == 4) bias = Incremental_Quantity4();    
//     }

//     TargetA = Speed_Middle - bias;
//     TargetB = Speed_Middle + bias;

//     Motor_Left  = (int)PWM_Limit(PID_A(EncoderA_VEL,TargetA), Limit, -Limit);
//     Motor_Right = (int)PWM_Limit(PID_B(EncoderB_VEL,TargetB), Limit, -Limit);
//     Set_Pwm(Motor_Left, Motor_Right);
//    // printf("Motor_Left%d, Motor_Right:%d",Motor_Left,Motor_Right);
// }




// /*
//     ????????????PID
//     IN: ??????????
//     OUT: ????
// */
// float GYRO_Control(float now,float target)
// {
// 	static float Bias, Last_bias, Last2_bias, Pwm;
// 	Bias = target-now;
// 	Pwm += Kp3 * (Bias - Last_bias) + Ki3 * Bias + Kd3 * (Bias - 2 * Last_bias + Last2_bias);

// 	Last_bias = Bias;
// 	Last2_bias = Last_bias;
// 	return Pwm;
// }





// /*
//     ?????????????PWM????
//     IN: ?????????????????????
//     OUT: ??
// */
// void Set_Pwm(int Left, int Right)
// {
//     if(Left > 0)    {AIN1_High;AIN2_Low;}      //?????
//     else            {AIN1_Low;AIN2_High;}      //???
//     DL_Timer_setCaptureCompareValue(PWM_0_INST, myabs(Left), DL_TIMER_CC_0_INDEX);

//     if(Right > 0)   {BIN1_High;BIN2_Low;}      //?????
//     else            {BIN1_Low;BIN2_High;}      //????
//     DL_Timer_setCaptureCompareValue(PWM_0_INST, myabs(Right), DL_TIMER_CC_1_INDEX);
// }





// /*=================== ?????PID??????? ===================*/
// //??A??PID
// float PID_A(float Encoder,float Target)
// {
// 	static float Bias, Last_bias, Last2_bias, Pwm;
// 	Bias = Target - Encoder;
// 	Pwm += Kp1 * (Bias - Last_bias) + Ki1 * Bias + Kd1 * (Bias - 2 * Last_bias + Last2_bias);

// 	Last_bias = Bias;
// 	Last2_bias = Last_bias;
// 	return Pwm;
// }



// //??B??PID
// float PID_B(float Encoder,float Target)
// {
// 	static float Bias, Last_bias, Last2_bias, Pwm;
// 	Bias = Target-Encoder;
// 	Pwm += Kp1 * (Bias - Last_bias) + Ki1 * Bias + Kd1 * (Bias - 2 * Last_bias + Last2_bias);

// 	Last_bias = Bias;
// 	Last2_bias = Last_bias;
// 	return Pwm;
// }




// /* 
//     ???????????? + ?????????
//     IN: ?????
//     max: ????
//     min: ??§³?
//     OUT: ????
// */
// float PWM_Limit(float IN,float max,float min)
// {
// 	float OUT = IN;
// 	if(OUT > max) OUT = max;
// 	if(OUT < min) OUT = min;
// 	return OUT;
// }