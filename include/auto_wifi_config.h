#ifndef _AUTO_WIFI_CONFIG_H_
#define _AUTO_WIFI_CONFIG_H_

//#define AP_CONFIG_TYPE_AIRKILL_TOUCH 0  //使用airkiss + esp-touch mode
//#define AP_CONFIG_TYPE_UDP_BROADCAST 1  //使用udp  broadcast mode

typedef void (*wifi_config_func)(char *ssid, char *pwd);

//{"SSID":"XXXXXXX","PWD":"XXXXXX","RETPORT":2345}
int32_t AIH_wifi_config_start(int32_t broadcastPort, wifi_config_func apConfCb);

void AIH_wifi_config_stop();

int32_t AIH_ak_config_start(char *aesKey, wifi_config_func confCb);

void AIH_ak_config_stop();

int8_t AIH_ak_lan_discover_start(char *deviceType, char *deviceId);

void AIH_ak_lan_discover_stop(void);

#endif
