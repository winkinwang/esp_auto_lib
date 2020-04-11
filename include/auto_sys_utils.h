/*********************************************************************/
/* Filename:    auto_sys_utils.h                                                                             */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: the header of system utils of ESP8266                                           */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*   Create:   2015-12-04                                                           		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2015-12-04    wangyunjin  Created                                                             */
/*     email:wyj0617mail@aliyun.com                                                                  */
/*********************************************************************/


#ifndef _AUTO_SYS_UTILS_H_
#define _AUTO_SYS_UTILS_H_

#define MAX_KEY_GPIO_NUM 8


enum UART_BR_E{
    E_BIT_RATE_300 = 300,
    E_BIT_RATE_600 = 600,
    E_BIT_RATE_1200 = 1200,
    E_BIT_RATE_2400 = 2400,
    E_BIT_RATE_4800 = 4800,
    E_BIT_RATE_9600   = 9600,
    E_BIT_RATE_19200  = 19200,
    E_BIT_RATE_38400  = 38400,
    E_BIT_RATE_57600  = 57600,
    E_BIT_RATE_74880  = 74880,
    E_BIT_RATE_115200 = 115200,
    E_BIT_RATE_230400 = 230400,
    E_BIT_RATE_460800 = 460800,
    E_BIT_RATE_921600 = 921600,
    E_BIT_RATE_1843200 = 1843200,
    E_BIT_RATE_3686400 = 3686400,
};

//uartNum=0/1, uart0[tx:gpio1,rx:gpio3], uart1[tx:gpio2]
int32_t AIH_debug_log_init(int32_t uartNum, enum UART_BR_E uartBitRate);

typedef void (*AIH_AT_CMD_CB)(void *data, int32_t dataLen);
//only uart0[gpio1,gpio3]
int32_t AIH_at_cmd_init(enum UART_BR_E uartBitRate, AIH_AT_CMD_CB cb);

int32_t AIH_at_send_str(char *dataBuff);

int32_t AIH_at_send_bytes(uint8_t *data, int32_t len);

/*
*    AIH_log_init:  initallize the uart0 output
*    the default baterate 115200
*
*/
//WARNING: Suggest to dispose
//void AIH_log_init();

//typedef void (*AIH_UART_RX_CB)(void *data, int32_t dataLen);
/*
*    AIH_uart_set_recvCb:  set the callback funtcion to recveive the UART input
*                                must call AIH_log_init() before 
*    para:
*            cb==the callback function
*            
*           
*/
//WARNING: Suggest to dispose
//void AIH_uart_set_recvCb(AIH_UART_RX_CB cb);


enum KEY_PRESS_TYPE_E
{
    E_KEY_SHORT_PRESS=0,   //short press key
    E_KEY_LONG_PRESS       //long press key
};

enum KEY_OPT_TYPE_E
{
    E_KEY_RELEASE=0,   //press key
    E_KEY_PRESS        //release key
};

typedef void (*key_press_cb)(enum KEY_PRESS_TYPE_E keyPressType, enum KEY_OPT_TYPE_E KeyOptType, int8_t gpioNum);
/*
*    auto_key_init:  initallize the keypad input
*    para:
*            gpioNumArray==the hw gpio port array
*            arrayNum==the max gpio port num of gpioNumArray, must < MAX_KEY_GPIO_NUM
*            keyCb====the callback function
*           
*/
int8_t AIH_key_init(int8_t *gpioNumArray,  int8_t arrayNum, key_press_cb keyCb);


/*
*    AIH_status_light_set:  set the status light
*    para:
*            gpioNum==the hw gpio port
*            defaultStatus == the default status of the gpio
*            intralMs==the intral time(ms) of the light change
*           
*/
int8_t AIH_status_light_set(int8_t gpioNum, int8_t defaultStatus, int32_t intralMs);


/*
*    AIH_gpio_output:  set the gpio output level(1/0)
*    para:
*            gpioNum==the hw gpio port
*            level====the level of the gpio(1,0)
*   return:
*            the real level of the gpio after set
*/
int8_t AIH_gpio_output(int8_t gpioNum,  int8_t level);


/*
*    AIH_gpio_input:  get the gpio input level(1/0)
*    para:
*            gpioNum==the hw gpio port
*            
*   return:
*            the real level of the gpio
*/
int8_t AIH_gpio_input(int8_t gpioNum);



typedef struct
{    
    char ssid[64];
    char pwd[64]; 
}AIH_WIFI_INFO_S;

typedef enum {
    EN_AIH_WIFI_MOD_STATION,
    EN_AIH_WIFI_MOD_AP,
    EN_AIH_WIFI_MOD_MAX
}AIH_WIFI_MOD_EN;

typedef void (*wifi_evt_func_cb)(int8_t err, int8_t *localIp, void *userdata);
/*
*    AIH_wifi_mode_switch:  switch device to AP/STA
*    para:
*            mode==the mode of wifi,  0---STA/1---AP
*            wifiInfo==the wifi SSID and PWD
*            evtfuncCb====the callback function, when setting success and get the host ip call this function
*            userData==the user data when call the cb funtion
*
*    return:
*           0---setting success, -1---failed with some error
*/
int32_t AIH_wifi_mode_switch(AIH_WIFI_MOD_EN mode, AIH_WIFI_INFO_S *wifiInfo, wifi_evt_func_cb evtfuncCb, void *userData);
//void AIH_wifi_stop();

/*
*    AIH_check_wifi_connect_status:  check the current connecting status
*    para:
*            NULL
*
*    return:
*           0---connect success, -1---not connect
*/
int32_t AIH_check_wifi_connect_status();



/*
*    AIH_property_erase_sector:  erase the property data sector by spi
*    para:
*            sectorAddr==the section addr of the sector in spi
* 
*
*    return:
*           none
*/
void AIH_property_erase_sector(uint32_t sectorAddr);



/*
*    AIH_property_set:  save the property data by spi, when re-write the data in old addr, must 
*                                AIH_property_erase_sector the whole sector
*    para:
*            inData==the data to write to spi
*            size==the size of the data
*            startAddr====the begin address of the flush to save
*
*    return:
*           0---save success, -1---failed with some error
*/
int32_t AIH_property_set(int8_t *inData, uint32_t size, uint32_t startAddr);

/*
*    AIH_property_get:  get the property data by spi
*    para:
*            outData==the data buffer to read from flush
*            size==the max size of the data
*            startAddr====the begin address of the flush
*
*    return:
*           0---save success, -1---failed with some error
*/
int32_t AIH_property_get(int8_t *outData, uint32_t size, uint32_t startAddr);


/*
*    AIH_get_ntp_time:  get the ntp time from the ntp-server
*    para:
*            cb== when get the ntp time from server, call this function to notify the user
*
*    return:
*           void
*/
typedef void (*get_ntp_cb_t)(char *curTime);
void AIH_get_ntp_time(get_ntp_cb_t func);

/*
*    AIH_get_version:  get the version of current SDK
*    para:
*            NULL
*
*    return:
*           not NULL---get success, NULL---failed
*/
const char *AIH_get_version();

uint64_t get_current_time();


typedef void (*AIH_SW_TIMER_CB)(void *cookie);

/*
*    AIH_sw_timer_register_func:  set the function implement after delayMs, persently support max=8 functions
*    para:
*            delayMs--- delay time(ms), must >10ms
*            funcCb--- the timer call the function to implement
*            cookie ---  the private data of the funcCb
*    return:
*            timerId----ther id of the register timer
*/
int64_t AIH_sw_timer_register_func(uint32_t delayMs, AIH_SW_TIMER_CB funcCb, void* cookie);

/*
*    AIH_sw_timer_remove_func:  remove the timer from the sw-timer system
*    para:
*            timerId--- the handle of the timer got by AIH_sw_timer_register_func
*     return:
*             -1-----failed
*             0------success
*           
*/
int32_t AIH_sw_timer_remove_func(int64_t timerId);

/*
*    AIH_sw_timer_reset:  reset the timer in the sw-timer system
*    para:
*            timerId--- the handle of the timer got by AIH_sw_timer_register_func
*            delayMs--- delay time(ms), must >10ms
*     return:
*             -1-----failed
*             0------success
*           
*/
int32_t AIH_sw_timer_reset(int64_t timerId, uint32_t delayMs);


typedef struct 
{
    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t min;
    uint32_t sec;
}AUTO_TIME_INFO_S;

/*
*    AIH_unix_time_convert:  convert the UNIX LONG time to day format[Y:]
*    para:
*            unixTime--- the unix time
*            timeInfo---the standy format time
*     return:
*             -1-----failed
*             0------success
*           
*/
void AIH_unix_time_convert(uint32_t unixTime, AUTO_TIME_INFO_S *timeInfo);


#endif
