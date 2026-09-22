#include "SERVO_PID.h"
#include"control.h"


volatile int16_t ball_speed = 0;     // 小球速度（带符号，单位根据需要标定）
volatile int16_t Position = 0;//小球位置
volatile int16_t SetPosition = 0;


pid_cycle_struct position_cycle;
pid_cycle_struct velocity_cycle;  // 速度环PID (串级内环)


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
    // 位置环 (外环 → 输出目标速度)
    position_cycle.p =  6.0f;      //6.0
    position_cycle.i =  0.01f;
    position_cycle.d =  0.5f;

    //位置环PID限幅参数 (外环 → 输出目标速度)
    position_cycle.i_value_max = 30.0f;  
    position_cycle.i_value_pro = 1.0f;
    position_cycle.out_max = 120.0f;



    //速度环PID参数 (内环 → 输出舵机角度偏移)  — 内环比外环快, 先只调P
    velocity_cycle.p = 0.15f;     //0.15
    velocity_cycle.i = 0.03f;
    velocity_cycle.d = 0.0f;
    
    velocity_cycle.i_value_max = 50.0f;   //20
    velocity_cycle.i_value_pro = 1.0f;
    velocity_cycle.out_max = 50.0f;
}

void pid_set(float Kp,float Ki,float Kd){

    KP1 = Kp;   	
    KI1 = Ki;    	
    KD1 = Kd;  		
}


void Steer_set(int angle){
    if(angle>SERVO_MOTOR_RMAX){angle=SERVO_MOTOR_RMAX;}//限幅
    if(angle<SERVO_MOTOR_LMAX){angle=SERVO_MOTOR_LMAX;}
    DL_TimerG_setCaptureCompareValue(SERVO_PWM_INST, (uint32_t)SERVO_MOTOR_DUTY(angle),DL_TIMER_CC_0_INDEX);
}




void UART_RECEIVE1(uint8_t DATA) {
    static RxState rx_state = WAIT_HEADER;  // 静态变量保持状态
    static uint8_t rx_buf[4];               // 存放 4 个数据字节

    switch (rx_state) {
    case WAIT_HEADER:
        if (DATA == 0xAA) {   // 帧头可定义为 FRAME_HEADER
            rx_state = WAIT_SPD_H;
        }
        break;

    case WAIT_SPD_H:
        rx_buf[0] = DATA;     // 速度高字节
        rx_state = WAIT_SPD_L;
        break;

    case WAIT_SPD_L:
        rx_buf[1] = DATA;     // 速度低字节
        rx_state = WAIT_DX_H;
        break;

    case WAIT_DX_H:
        rx_buf[2] = DATA;     // 位移高字节
        rx_state = WAIT_DX_L;
        break;

    case WAIT_DX_L:
        rx_buf[3] = DATA;     // 位移低字节
        // 组合两个 16 位值（大端序）
        ball_speed = (int16_t)((rx_buf[0] << 8) | rx_buf[1]);
        Position    = (int16_t)((rx_buf[2] << 8) | rx_buf[3]);
        rx_state = WAIT_HEADER; // 重新等待下一帧
        break;

    default:
        rx_state = WAIT_HEADER;
        break;
    }
}



void three_question(void){  //先往右5cm 再往左10cm并停止


    if (sys_tick < 450) {
        // 0 ~ 499ms
        Steer_set(SERVO_MOTOR_MID + 100);
    }
    else if (sys_tick < 1600) {
        // 500 ~ 999ms
        Steer_set(SERVO_MOTOR_MID - 100);
    }
    else if (sys_tick <5000) {
            float A = 0.9;
            float B = 0.8;                     // 速度滤波系数 (比位置滤波稍弱，保证响应速度)
            static float filtered_position = 0;
            static float filtered_speed = 0;

            if (sys_tick % 5 == 0) {
                float raw_pos = (float)Position;
                float raw_spd = (float)ball_speed;

                // 一阶低通滤波
                filtered_position = A * raw_pos + (1.0f - A) * filtered_position;
                filtered_speed    = B * raw_spd + (1.0f - B) * filtered_speed;

                // ========== 外环：位置PID → 目标速度 ==========
                pid_control(&position_cycle, 128, filtered_position);
                float target_velocity = position_cycle.out;

                // ========== 内环：速度PID → 舵机角度 ==========
                pid_control(&velocity_cycle, target_velocity, filtered_speed);
                Steer_set(SERVO_MOTOR_MID + (int)(-velocity_cycle.out));
            }
    else if (sys_tick >5000){Steer_set(SERVO_MOTOR_MID+15);}

    }
}



void four_quesition(void){
    static uint32_t enter_tick = 0;
    static bool     first_run  = true;

    // ====== 首次进入：记录时刻 ======
    if (first_run) {
        enter_tick = sys_tick;
        first_run  = false;
    }

    // ====== 缓起步系数：0→1，2秒 ======
    uint32_t elapsed = sys_tick - enter_tick;
    float    ramp    = (float)elapsed / 2500.0f;
    if (ramp > 1.0f) ramp = 1.0f;

    pid_set(12, 1.75, 0);
    Speed_Middle = 18.0f * ramp;

    flag = 1;
    float A = 0.9;
    float B = 0.8;                     // 速度滤波系数 (比位置滤波稍弱，保证响应速度)
    static float filtered_position = 0;
    static float filtered_speed = 0;

    if (sys_tick % 5 == 0) {
        float raw_pos = (float)Position;
        float raw_spd = (float)ball_speed;

        // 一阶低通滤波
        filtered_position = A * raw_pos + (1.0f - A) * filtered_position;
        filtered_speed    = B * raw_spd + (1.0f - B) * filtered_speed;

        // ========== 外环：位置PID → 目标速度 ==========
        pid_control(&position_cycle, 0, filtered_position);
        float target_velocity = position_cycle.out;

        // ========== 内环：速度PID → 舵机角度 ==========
        pid_control(&velocity_cycle, target_velocity, filtered_speed);
    }

    Steer_set(SERVO_MOTOR_MID + (int)(-velocity_cycle.out));

}

void five_question(void){
    static uint32_t enter_tick = 0;
    static bool     first_run  = true;

    // ====== 首次进入：记录时刻 ======
    if (first_run) {
        enter_tick = sys_tick;
        first_run  = false;
    }

    // ====== 缓起步系数：0→1，2秒 ======
    uint32_t elapsed = sys_tick - enter_tick;
    float    ramp    = (float)elapsed / 2500.0f;
    if (ramp > 1.0f) ramp = 1.0f;

    pid_set(12, 1.75, 0);
    Speed_Middle = 18.0f * ramp;

    flag = 1;
    float A = 0.9;
    float B = 0.8;                     // 速度滤波系数 (比位置滤波稍弱，保证响应速度)
    static float filtered_position = 0;
    static float filtered_speed = 0;

    if (sys_tick % 5 == 0) {
        float raw_pos = (float)Position;
        float raw_spd = (float)ball_speed;

        // 一阶低通滤波
        filtered_position = A * raw_pos + (1.0f - A) * filtered_position;
        filtered_speed    = B * raw_spd + (1.0f - B) * filtered_speed;

        // ========== 外环：位置PID → 目标速度 ==========
        pid_control(&position_cycle, SetPosition, filtered_position);
        float target_velocity = position_cycle.out;

        // ========== 内环：速度PID → 舵机角度 ==========
        pid_control(&velocity_cycle, target_velocity, filtered_speed);
    }

    Steer_set(SERVO_MOTOR_MID + (int)(-velocity_cycle.out));

}
