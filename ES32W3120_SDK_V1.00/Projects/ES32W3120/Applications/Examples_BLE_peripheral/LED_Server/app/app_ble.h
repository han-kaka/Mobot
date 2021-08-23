#ifndef __APP_BLE_H
#define __APP_BLE_H

#include "global.h"

#define SYSTEM_CMD                  0xc1  //系统指令
#define CONTROL_CMD                 0xc2  //控制指令
#define SET_DATA_CMD                0xc3  //设置数据指令
#define READ_STATE_CMD              0xc4  //读取状态指令
#define READ_DATA_CMD               0xc5  //读取数据指令
#define WRITE_DATA_CMD              0xd5  //写数据指令

#define SYSTEM_HEART_BEATS          0x01  //数据心跳包
#define SYSTEM_ACK                  0x02  //确认收到数据
#define SYSTEM_ERROR                0x03  //故障
#define SYSTEM_RESEND               0x04  //重发

#define ERROR_IMU                   0x01  //IMU传感器故障
#define ERROR_FLASH                 0x02  //FLASH内存故障
#define ERROR_BAT                   0x03  //电池温度故障
#define ERROR_COMM                  0x04  //通信故障

#define CONTROL_CALIBRATE           0x01  //姿态校准
#define CONTROL_SCAN                0x02  //背部扫描
#define CONTROL_SEND_SCAN_DATA      0x03  //上传扫描数据
#define CONTROL_SEND_MONITOR_DATA   0x04  //上传实时监控数据
#define CONTROL_SEND_FLASH_DATA     0x05  //上传存储数据
#define CONTROL_NO_DATA             0x06  //没有离线数据

#define SEND_FLASH_DATA_START       0x01  //上位机通知下位机开始上传数据
#define SEND_FLASH_DATA_FINISH      0x02  //下位机通知上位机数据已经传输完毕
#define SEND_FLASH_DATA_DELETE      0x03  //上位机通知下位机可以删除数据

#define SET_FREQUENCY               0x01  //震动提醒频率

#define STATE_INFO                  0x01  //当前电量、内存、当前提醒设置状态、设备序列号
#define STATE_SCAN                  0x02  //上位机当前是否处于扫描界面

#define DATA_MONITOR_DATA           0x01  //检测产品传感器数据
#define DATA_UTC                    0x02  //北京时间
#define DATA_ONLINE_IMU_DATA        0x01  //实时IMU传感器数据及时间戳
#define DATA_OFFLINE_IMU_DATA       0x03  //离线IMU传感器数据及时间戳
#define DATA_SCAN_DATA              0x04  //上传扫描数据及时间戳

typedef struct {
    uint8_t tbd0;
    uint8_t tbd1;
    uint8_t tbd2;
    uint8_t tbd3;
    uint8_t tbd4;
    uint8_t tbd5;
    uint8_t utc_y;
    uint8_t utc_m;
    uint8_t utc_d;
    uint8_t utc_h;
    uint8_t utc_f;
    uint8_t utc_s;
    uint8_t utc_5ms;
    uint8_t tbd6;
    uint8_t tbd7;
    
} data_utc_t;

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


