#include "GYRO.h"

// �������ձ���
uint8_t RollL, RollH, PitchL, PitchH, YawL, YawH, VL, VH, SUM;
float Pitch,Roll,Yaw;

// ���ڽ���״̬��ʶ
#define WAIT_HEADER1 0
#define WAIT_HEADER2 1
#define RECEIVE_DATA 2

uint8_t RxState = WAIT_HEADER1;
uint8_t receivedData[9];
uint8_t dataIndex = 0;



//������ƫ������������
// void Serial_JY61P_Zero_Yaw(void)
// {
//     DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X69);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X88);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XB5);
// 	delay_ms(100);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X76);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
// 	delay_ms(100);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
// 	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
//     delay_ms(500);
// }




// // �����жϴ�������
// /*
//     * ���ڽ������ݣ����������Ƕ�
//     * ���յ������ݸ�ʽΪ��0x55 0x53 0xXX 0xXX 0xXX 0xXX 0xXX 0xXX 0xXX 0xXX
//     * ����0xXXΪ�Ƕ����ݣ���λΪ0.1��
//     * �Ƕ�����Ϊ16λ����8λ��ǰ����8λ�ں�
//     * �Ƕ�����Ϊ������ʾ˳ʱ����ת��������ʾ��ʱ����ת
//     * �Ƕ�����Ϊ0��ʾˮƽ
//     * �Ƕ�����Ϊ180��ʾ��ֱ
//     * �Ƕ�����Ϊ90��ʾ��ֱ����
//     * �Ƕ�����Ϊ-90��ʾ��ֱ����
//     * �Ƕ�����Ϊ360��ʾˮƽ����
//     * �Ƕ�����Ϊ-360��ʾˮƽ����
// */
// void UART_JY61P_INST_IRQHandler(void) 
// {
//     uint8_t uartdata = DL_UART_Main_receiveData(UART_JY61P_INST);   // ����һ��uint8_t����

//     switch (RxState) {
//     case WAIT_HEADER1:
//         if (uartdata == 0x55) {
//             RxState = WAIT_HEADER2;
//         }
//         break;
//     case WAIT_HEADER2:
//         if (uartdata == 0x53) {
//             RxState = RECEIVE_DATA;
//             dataIndex = 0;
//         } else {
//             RxState = WAIT_HEADER1;                                 // �������������ĵڶ���ͷ������״̬
//         }
//         break;
//     case RECEIVE_DATA:
//         receivedData[dataIndex++] = uartdata;
//         if (dataIndex == 9) {
//             // ���ݽ������ϣ������������ı���
//             RollL = receivedData[0];
//             RollH = receivedData[1];
//             PitchL = receivedData[2];
//             PitchH = receivedData[3];
//             YawL = receivedData[4];
//             YawH = receivedData[5];
//             VL = receivedData[6];
//             VH = receivedData[7];
//             SUM = receivedData[8];

//             // У��SUM�Ƿ���ȷ
//             uint8_t calculatedSum = 0x55 + 0x53 + RollH + RollL + PitchH + PitchL + YawH + YawL + VH + VL;
//             if (calculatedSum == SUM) {
//                 // У���ɹ������Խ��к�������
//                 if((float)(((uint16_t)RollH << 8) | RollL)/32768*180>180){
//                     Roll = (float)(((uint16_t)RollH << 8) | RollL)/32768*180 - 360;
//                 }else{
//                     Roll = (float)(((uint16_t)RollH << 8) | RollL)/32768*180;
//                 }

//                 if((float)(((uint16_t)PitchH << 8) | PitchL)/32768*180>180){
//                     Pitch = (float)(((uint16_t)PitchH << 8) | PitchL)/32768*180 - 360;
//                 }else{
//                     Pitch = (float)(((uint16_t)PitchH << 8) | PitchL)/32768*180;
//                 }

//                 if((float)(((uint16_t)YawH << 8) | YawL)/32768*180 >180){
//                     Yaw = (float)(((uint16_t)YawH << 8) | YawL)/32768*180 - 360;
//                 }else{
//                     Yaw = (float)(((uint16_t)YawH << 8) | YawL)/32768*180;
//                 }
                
//             } else {
//                 // У��ʧ�ܣ���������
//             }
//             RxState = WAIT_HEADER1;                                 // ����״̬�Եȴ���һ�����ݰ�
//         }
//         break;
//     }
// }
