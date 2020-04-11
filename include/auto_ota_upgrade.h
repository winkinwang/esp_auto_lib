#ifndef _AUTO_UPGRADE_H_
#define _AUTO_UPGRADE_H_

typedef void (*ota_upgrade_cb_t)(int8_t result);
/*
*    AIH_ota_upgrade_start:  upgrade firmware by ota
*    para:
*            svrIp==the upgrade server ip
*            svrPort==the upgrade server port
*            urlRootPath==the bin-dir path of the server,this diretory must contain user1.bin and user2.bin
*            funcCb====the callback function, when setting success and get the host ip call this function
*
*    return:
*           0---setting success, -1---failed with some error
*/

int32_t AIH_ota_upgrade_start(const uint8_t svrIp[], uint32_t svrPort, const char *urlRootPath, ota_upgrade_cb_t funcCb);

void AIH_ota_upgrade_stop();

#endif
