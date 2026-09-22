#include "sys.h"
#ifndef __SERVO_PID__
#define __SERVO_PID__

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     双边限幅 数据范围是 [-32768,32767]
// 参数说明     x               被限幅的数据
// 参数说明     a               限幅范围左边界
// 参数说明     b               限幅范围右边界
// 返回参数     int             限幅之后的数据
// 使用示例     int dat = func_limit_ab(500, -300, 400);        //数据被限制在-300至+400之间  因此返回的结果是400
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define     func_limit_ab(x, a, b)  ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))

#define SERVO_MOTOR_FREQ            (320)                                        // 定义主板上舵机频率  请务必注意范围
#define SERVO_MOTOR_MID             (125)                     //135         
#define SERVO_MOTOR_LMAX            (60)                                        
#define SERVO_MOTOR_RMAX            (170)                                       
#define SERVO_MOTOR_DUTY(x)         ((float)10000.0/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))// ------------------ 舵机占空比计算方式 ------------------


typedef struct
{
    float p;                                             // PID 控制器比例项 P
    float i;                                             // PID 控制器积分项 I
    float d;                                             // PID 控制器微分项 D
    float p_value_last;                                  // 上一次偏差值
    float i_value;                                       // PID 积分值
    float i_value_pro;                                   // PID 积分值的比例（范围 0 - 1，用于限制积分增长速度）
    float i_value_max;                                   // PID 积分值上限
    float out;                                           // PID 控制器输出值
    float out_max;                                       // PID 输出值上限
    float incremental_data[2];                           // 增量式 PID 的偏差历史数据
} pid_cycle_struct;


typedef enum {
    WAIT_HEADER,      // 等待帧头 0xAA
    WAIT_SPD_H,       // 等待速度高字节
    WAIT_SPD_L,       // 等待速度低字节
    WAIT_DX_H,        // 等待位移高字节
    WAIT_DX_L         // 等待位移低字节
} RxState;



extern volatile int flag;
extern volatile int flag_en;
extern volatile int16_t Position;
extern volatile int16_t SetPosition;

extern  volatile uint32_t sys_tick;

extern pid_cycle_struct position_cycle;

void Steer_set(int angle);
void pid_init(void);
void pid_set(float Kp,float Ki,float Kd);
void pid_control (pid_cycle_struct *pid_cycle, float target, float real);
void UART_RECEIVE1(uint8_t DATA);
void three_question(void);
void four_question(void);
void five_question(void);

#endif