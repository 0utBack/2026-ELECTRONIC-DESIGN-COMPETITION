#include "KeyScan.h"


volatile KEY_EVENT KeyEvent = KEY_EVENT_NONE;

typedef enum
{
    KEY_IDLE = 0,
    KEY_SHAKE,
    KEY_PRESS
}KEY_STATE;

typedef struct
{
    KEY_STATE state;
    uint8_t cnt;
}KEY;

static KEY key1 = {KEY_IDLE,0};
static KEY key2 = {KEY_IDLE,0};
static KEY key3 = {KEY_IDLE,0};
static KEY key4 = {KEY_IDLE,0};

static void KeyFSM(KEY *key, uint8_t level, KEY_EVENT event)
{
    switch(key->state)
    {
        case KEY_IDLE:

            if(level == 0)
            {
                key->cnt = 0;
                key->state = KEY_SHAKE;
            }

            break;

        case KEY_SHAKE:

            if(level == 0)
            {
                if(++key->cnt >= 4)      //20ms
                {
                    key->state = KEY_PRESS;
                }
            }
            else
            {
                key->state = KEY_IDLE;
            }

            break;

        case KEY_PRESS:

            if(level == 1)
            {
                KeyEvent = event;
                key->state = KEY_IDLE;
            }

            break;
    }
}

void KeyScan(void)
{
    KeyFSM(&key1,!DL_GPIO_readPins(KEY_EN_PORT ,KEY_EN_PIN),KEY1_PRESS);

    KeyFSM(&key2,!DL_GPIO_readPins(KEY_SW_PORT ,KEY_SW_PIN),KEY2_PRESS);

    KeyFSM(&key3,!DL_GPIO_readPins(KEY_Up_PORT ,KEY_Up_PIN),KEY3_PRESS);

    KeyFSM(&key4,!DL_GPIO_readPins(KEY_Down_PORT ,KEY_Down_PIN),KEY4_PRESS);
}


void KeyStateProcess(void)
{ 
    switch(KeyEvent)
    {
        case KEY1_PRESS:
            
            flag_en = 1;

            KeyEvent = KEY_EVENT_NONE;

            break;

        case KEY2_PRESS:
            
            mode ++;


            KeyEvent = KEY_EVENT_NONE;

            break;

        case KEY3_PRESS:
            SetPosition +=5;

            KeyEvent = KEY_EVENT_NONE;

            break;

        case KEY4_PRESS:
            SetPosition -=5;


            KeyEvent = KEY_EVENT_NONE;

            break;
    }
}
