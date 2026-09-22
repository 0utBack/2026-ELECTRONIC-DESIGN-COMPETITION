#ifndef __KEYSCAN_H__
#define __KEYSCAN_H__

#include "sys.h"
#include "SERVO_PID.h"

#define KEY1 P11_3
#define KEY2 P11_2
#define KEY3 P20_7
#define KEY4 P20_6


typedef enum
{
    KEY_EVENT_NONE = 0,

    KEY1_PRESS,
    KEY2_PRESS,
    KEY3_PRESS,
    KEY4_PRESS,

}KEY_EVENT;

extern volatile KEY_EVENT KeyEvent;
extern volatile int flag;                                  //电机控制
extern volatile int mode;                                  //问题选择
extern volatile int flag_en;                               //全程序启动使能

void KeyScan(void);


void KeyStateProcess(void);

#endif