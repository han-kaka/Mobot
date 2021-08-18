#ifndef __APP_BLE_H
#define __APP_BLE_H

#include "global.h"

#define SYSTEM_CMD                  0xc1  //ϵͳָ��
#define CONTROL_CMD                 0xc2  //����ָ��
#define SET_DATA_CMD                0xc3  //��������ָ��
#define READ_STATE_CMD              0xc4  //��ȡ״ָ̬��
#define READ_DATA_CMD               0xc5  //��ȡ����ָ��

#define SYSTEM_HEART_BEATS          0x01  //����������
#define SYSTEM_ACK                  0x02  //ȷ���յ�����
#define SYSTEM_ERROR                0x03  //����
#define SYSTEM_RESEND               0x04  //�ط�

#define ERROR_IMU                   0x01  //IMU����������
#define ERROR_FLASH                 0x02  //FLASH�ڴ����
#define ERROR_BAT                   0x03  //����¶ȹ���
#define ERROR_COMM                  0x04  //ͨ�Ź���

#define CONTROL_CALIBRATE           0x01  //��̬У׼
#define CONTROL_SCAN                0x02  //����ɨ��
#define CONTROL_SEND_SCAN_DATA      0x03  //�ϴ�ɨ������
#define CONTROL_SEND_MONITOR_DATA   0x04  //�ϴ�ʵʱ�������
#define CONTROL_SEND_FLASH_DATA     0x05  //�ϴ��洢����
#define CONTROL_NO_DATA             0x06  //û����������

#define SET_FREQUENCY               0x01  //������Ƶ��

#define STATE_INFO                  0x01  //��ǰ�������ڴ桢��ǰ��������״̬���豸���к�
#define STATE_SCAN                  0x02  //��λ����ǰ�Ƿ���ɨ�����

#define DATA_MONITOR_DATA           0x01  //����Ʒ����������
#define DATA_TIME                   0x02  //����ʱ��
#define DATA_ONLINE_IMU_DATA        0x01  //ʵʱIMU���������ݼ�ʱ���
#define DATA_OFFLINE_IMU_DATA       0x03  //����IMU���������ݼ�ʱ���
#define DATA_SCAN_DATA              0x04  //�ϴ�ɨ�����ݼ�ʱ���

typedef struct {
    uint8_t start;
    uint8_t len;
    uint8_t cmd;
    uint8_t address;
    uint8_t data[15];
    uint8_t sum;
    
} ble_data_t;

int ble_data_decode(void);

#endif


