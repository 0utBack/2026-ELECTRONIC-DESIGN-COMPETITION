#include "SERVO_PID.h"


#define RX_BUF_SIZE 3
static uint8_t rx_buf[RX_BUF_SIZE];
static uint8_t rx_idx = 0;
static uint8_t rx_state = 0; // 0:等待帧头
volatile uint8_t new_command = 0; // 主循环检查用
volatile uint16_t target_angle = 0; // 目标角度（0~300）

volatile int8_t Position = 0;//小球位置


pid_cycle_struct position_cycle;
pid_cycle_struct angle_cycle;


//舵机PID
void pid_control (pid_cycle_struct *pid_cycle, float target, float real)
{
    float    proportion_value    = 0;          // 比例量
    float    differential_value  = 0;          // 微分量

    proportion_value = target - real;          // 比例量 = 目标值 - 实际值



    pid_cycle->i_value += (proportion_value * pid_cycle->i_value_pro);  // 积分量 = 积分量 + 比例量 * 积分程度

    pid_cycle->i_value = func_limit_ab(pid_cycle->i_value, -pid_cycle->i_value_max, pid_cycle->i_value_max);  // 积分量限幅

    differential_value = proportion_value - pid_cycle->p_value_last;  // 微分量 = 比例量 - 上一次比例量

    pid_cycle->out = (pid_cycle->p * proportion_value + pid_cycle->i * pid_cycle->i_value + pid_cycle->d * differential_value);  // PID拟合

    pid_cycle->out = func_limit_ab(pid_cycle->out, -pid_cycle->out_max, pid_cycle->out_max);  // PID输出限幅

    pid_cycle->p_value_last = proportion_value;        // 保存比例量
}


void pid_init(void)
{
    //P/I/D参数
    position_cycle.p =  0.5f;
    position_cycle.i =  0.01f;
    position_cycle.d =  0.0f;

    angle_cycle.p = 1.0f;
    angle_cycle.i = 1.0f;
    angle_cycle.d = 0.0f;


    //PID限幅参数
    position_cycle.i_value_max = 200.0f;
    position_cycle.i_value_pro = 1.0f;
    position_cycle.out_max = 200.0f;

    angle_cycle.i_value_max = 1.0f;
    angle_cycle.i_value_pro = 1.0f;
    angle_cycle.out_max = 1.0f;
}


void Steer_set(int angle){
    if(angle>SERVO_MOTOR_RMAX){angle=SERVO_MOTOR_RMAX;}//限幅
    if(angle<SERVO_MOTOR_LMAX){angle=SERVO_MOTOR_LMAX;}
    DL_TimerG_setCaptureCompareValue(SERVO_PWM_INST, (uint32_t)SERVO_MOTOR_DUTY(angle),DL_TIMER_CC_0_INDEX);
}




void UART_RECEIVE(uint8_t DATA){
    //if(DATA == 0x11){flag_en = 1;flag = 1;}
    //if(DATA == 0x66){flag_en = 0;flag = 0;}
     switch (rx_state) {
            case 0: // 等待帧头 0xAA
                if (DATA == 0xAA) {
                    rx_state = 1;
                }
                break;
            case 1: // 角度高字节
                Position=(int8_t)DATA;
                rx_state = 0;
                break;
        }
}

