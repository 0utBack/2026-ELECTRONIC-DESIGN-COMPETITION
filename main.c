#include "ti_msp_dl_config.h"

/* USER CODE BEGIN Includes */
#include "GYRO.h"
#include "sys.h"
#include "Encoder.h"
#include "Sensor.h"
#include "control.h"
#include "SERVO_PID.h"


/* USER CODE END Includes */


/* USER CODE BEGIN PV */
volatile int flag = 1;                                  //flag??�1�7�1�7??0-?????1-AB?�1�7�1�7?2-BC?�1�7�1�7?3-CD?�1�7�1�7?4-DA?�1�7�1�7?
volatile int mode = 1;                                  //mode??�1�7�1�7??0-?????1-???... ...??
volatile int flag_en = 1;                               //flag_en??�1�7�1�7??0-??????1-???

volatile uint32_t EncoderA_Port, EncoderB_Port;         //?????????
volatile int32_t EncoderA_CNT = 0, EncoderB_CNT = 0;    //???????????
volatile int32_t EncoderA_VEL = 0, EncoderB_VEL = 0;    //???????

extern int Motor_Left, Motor_Right;

extern float Pitch, Roll, Yaw;                          //?????

volatile float LED_CNT = 0.0;
volatile bool flag_LED = 0;
/* USER CODE END PV */
int MotorL, MotorR;


int16_t gyro_raw_z = 0;
int16_t gyro[3];
//static bool is_calibrated = false;
float yaw_angle = 0.0f;
//static int16_t gyro_z_bias = 0;

volatile uint32_t sys_tick = 0;   // 1ms计数

uint32_t second = 0;              // 秒数



/* USER CODE BEGIN PFP */
void Key_Scan(void);
void LED_Sound(void);
void TimeUpdate(void);
/* USER CODE END PFP */
 

int main(void)
{
    SYSCFG_DL_init();
  /* USER CODE BEGIN 2 */

    //IMU_Init(200, 5);            
    //�����ǻ����ж�ȡ��                  
    //NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);      
    //DL_Timer_startCounter(TIMER_1_INST);

    OLED_Init();
    OLED_CLS();

    OLED_ShowString(1,1,"TIME:",2);
    OLED_ShowNum(1,6,second,5,2);
    OLED_ShowString(1,12,"s",2);
    delay_ms(500);
    Encoder_Init();
    pid_init();


    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_Timer_startCounter(TIMER_0_INST);

    NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
    DL_Timer_startCounter(TIMER_1_INST);

    NVIC_EnableIRQ(UART0_INT_IRQn);  //�����ж�

    DL_TimerG_startCounter(SERVO_PWM_INST); //启动舵机PWM定时器

    //上电回中舵机回中
    DL_TimerG_setCaptureCompareValue(SERVO_PWM_INST, (uint32_t)SERVO_MOTOR_DUTY(SERVO_MOTOR_MID),DL_TIMER_CC_0_INDEX);
    
  /* USER CODE END 2 */

    while (1) {


        //Key_Scan();
        three_question();

        if(sys_tick %1000 == 0){
            
            OLED_ShowSignedNum(3,6,Position,5,2);
            OLED_ShowSignedNum(5,6,(int8_t)position_cycle.out,5,2);
        }
        // if(sys_tick %10 ==0)
        // {
        //     pid_control(&position_cycle, 0, Position);
        // }
        // if(sys_tick %20 == 0){Steer_set(SERVO_MOTOR_MID +(int)(-position_cycle.out));}
        if(flag_en)            //?????????
        {
            Follow_Route(); //�1�7�1�7???????????????
            if(flag == 1)TimeUpdate();
            
            
            
            
            //printf("%d , %d\n",EncoderA_VEL,EncoderB_VEL);
            
            //printf("PWM: %d , %d\n",Motor_Left,Motor_Right);
            //Set_Pwm(300,300);
            //printf("%d,%d,%d,%d,%d,%d,%d,%d,\n",P1,P2 ,P3,P4, P5, P6 , P7, P8); 
            //printf("Yaw:%f\n",Yaw);
            /* LED??? */
            //LED_Sound();
            // MotorL  = (int)PWM_Limit(PID_A(EncoderA_VEL,50), 3000, -3000);//
            // MotorR = (int)PWM_Limit(PID_B(EncoderB_VEL,50), 3000, -3000);
            // Set_Pwm(MotorL, MotorR);
            // printf("EncoderA_VEL:%d,EncoderB_VEL:%d\n",EncoderA_VEL,EncoderB_VEL);
            // printf("MotorL:%d,MotorR:%d\n",MotorL,MotorR);
            //printf("Yaw: %.1f deg, Gyro Z: %d\r\n", yaw_angle, gyro[2]);
        }
    }

}




/* USER CODE BEGIN 4 */

/*
    * ?????0?�1�7�1�7????????
*/
void TIMER_0_INST_IRQHandler(void)   //�ջ��ж�
{
    switch (DL_TimerA_getPendingInterrupt(TIMER_0_INST)) {
    case DL_TIMERA_IIDX_ZERO:   if(flag == 0) {Set_Pwm(0,0);} else {Control();}                               


    default:break;
    }
}


//�����ǻ����ж�   ��ʱ����
void TIMER_1_INST_IRQHandler(void)
{
    sys_tick++;
}


/*
    * ??????�1�7�1�7??
    * ????????????�1�7�1�7?mode
    * ????????????�1�7�1�7?flag_en??????
*/
void Key_Scan(void)
{
    /* 模式选择键 */
    if(DL_GPIO_readPins(KEY_PORT, KEY_S2_PIN) == 0)
    {
        delay_ms(10);
        if(DL_GPIO_readPins(KEY_PORT, KEY_S2_PIN) == 0)
        {
            while(!DL_GPIO_readPins(KEY_PORT, KEY_S2_PIN));
            mode = (mode + 1) % 5;
        }
    }

    /* 使能键 */
    if(DL_GPIO_readPins(KEY_PORT, KEY_EN_PIN) == 0)
    {
        delay_ms(10);
        if(DL_GPIO_readPins(KEY_PORT, KEY_EN_PIN) == 0)
        {
            while(!DL_GPIO_readPins(KEY_PORT, KEY_EN_PIN));
            flag_en = 1 - flag_en;
        }
    }
}





void GROUP1_IRQHandler(void)
{
    /* ???�1�7�1�7????? */
    Encodering();


    
}

void UART_0_INST_IRQHandler(void){
    if(DL_UART_Main_getPendingInterrupt(UART_0_INST)==DL_UART_MAIN_IIDX_RX){
        uint8_t data = DL_UART_Main_receiveData(UART_0_INST);
        UART_RECEIVE(data);
    }
}



void LED_Sound(void)
{
    if(flag_LED)
    {
        LED_High;
        LED_CNT  = LED_CNT + 0.1;
        if(LED_CNT >= 800) 
        {
            LED_Low;
            LED_CNT = 0;
            flag_LED = 0;
        }
    }
}
void TimeUpdate(void)
{
  if(sys_tick >= 1000)
  {
    sys_tick = 0;
    second++;
    OLED_ShowString(1,1,"TIME:",2);

    OLED_ShowNum(1,6,second,5,2);

    OLED_ShowString(1,12,"s",2);
  }

//   OLED_ShowString(1,1,"TIME:",2);

//   OLED_ShowNum(1,6,second,5,2);

//   OLED_ShowString(1,12,"s",2);
 }





/* USER CODE END 4 */