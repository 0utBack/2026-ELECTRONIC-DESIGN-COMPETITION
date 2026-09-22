#include "Sensor.h"

#define Black_CNT1          5000                               //mode = 1 �1�7�1�7�1�7�1�9�1�7�1�7�1�7�1�7�1�7�1�7�1�7
#define Black_CNT2          5000                               //mode = 2 �1�7�1�7�1�7�1�9�1�7�1�7�1�7�1�7�1�7�1�7�1�7
#define Black_CNT3          5000                               //mode = 3�1�7�1�74 �1�7�1�7�1�7�1�9�1�7�1�7�1�7�1�7�1�7�1�7�1�7

#define White_CNT           1000                              //�1�7�1�7�1�7�1�9�1�7�1�7�1�7�1�7�1�7�1�7�1�7  
#define White_CNT2          5000                             //mode = 2 �1�7�1�7�1�7�1�9�1�7�1�7�1�7�1�7�1�7�1�7�1�7
#define White_CNT3          5000                            //mode = 3�1�7�1�74 �1�7�1�7�1�7�1�9�1�7�1�7�1�7�1�7�1�7�1�7�1�7


extern volatile int flag;                                  //flag�0�8�0�0�˄1�7�1�70-�1�7�1�7�0�5�1�7�1�71-AB�1�7�1�72-BC�1�7�1�73-CD�1�7�1�74-DA�1�7�1�7
extern volatile bool flag_LED;
extern volatile int mode;                                  //mode�0�8�0�0�˄1�7�1�70-�1�7�1�7�0�5�1�7�1�7
extern volatile int flag_en;



/*
    �1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�1�1�7���1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�4�1�7�1�7�1�7
    �1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7
*/
int Follow_Route(void)
{
    static int cnt = 0;
    /* �0�0�0�4�0�5 */
        if(flag == 1)                                                    //AB�1�7�1�7�0�6��
        {
            
            if( (P1) && (P2) && (P3) )        //�1�7�1�7�0�5�1�7�1�7�1�7�8�9�1�7�1�7�1�7�1�7
            {
                cnt++;

                if(cnt > Black_CNT1)                                    
                {
                    flag_LED = 1;
                    flag = 0;
                    flag_en = 0;
                    cnt = 0;
                    return 0;
                }
            }
            if( (P5) && (P6) && (P7) )        //�1�7�1�7�0�5�1�7�1�7�1�7�8�9�1�7�1�7�1�7�1�7
            {
                cnt++;

                if(cnt > Black_CNT1)                                    
                {
                    flag_LED = 1;
                    flag = 0;
                    flag_en = 0;
                    cnt = 0;
                    return 0;
                }
            }
            else   cnt = 0;                                         
        }   
    return 0;
}


 





/*
    函数功能：检测P3、P4、P5是否同时扫到黑线（十字路口停车用）
    返回值：1 = 三个传感器同时检测到黑线，0 = 未同时检测到
*/



int Incremental_Quantity(void)
{
    int value = 0;
    int count = 0;                      // 检测到黑线的传感器数量

    if(!P1)
    {
        value -= 38;
        count++;
    }
    if(!P2)
    {
        value -= 28;
        count++;
    }
    if(!P3)
    {
        value -= 21;
        count++;
    }
    if(!P4)
    {
        value -= 14;
        count++;
    }
    if(!P5)
    {
        value += 14;
        count++;
    }
    if(!P6)
    {
        value += 21;
        count++;
    }
    if(!P7)
    {
        value += 28;
        count++;
    }
    if(!P8)
    {
        value += 38;
        count++;
    }

    if(count > 1)                       // 多个传感器同时检测到黑线，取平均值
        value = value / count;

    return value;
}


int Incremental_Quantity1(void)
{
    int value = 0;
    int count = 0;                      // 检测到黑线的传感器数量

    if(!P1)
    {
        value -= 20;
        count++;
    }
    if(!P2)
    {
        value -= 15;
        count++;
    }
    if(!P3)
    {
        value -= 11;
        count++;
    }
    if(!P4)
    {
        value -= 8;
        count++;
    }
    if(!P5)
    {
        value += 8;
        count++;
    }
    if(!P6)
    {
        value += 11;
        count++;
    }
    if(!P7)
    {
        value += 15;
        count++;
    }
    if(!P8)
    {
        value += 20;
        count++;
    }

    if(count > 1)                       // 多个传感器同时检测到黑线，取平均值
        value = value / count;

    return value;
}









