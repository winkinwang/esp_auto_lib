/*********************************************************************/
/* Filename:    auto_i2c_master.h                                                                             */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: the header of i2c master of ESP8266                                           */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*   Create:   2015-12-04                                                           		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2015-12-04    wangyunjin  Created                                                             */
/*     email:wyj0617mail@aliyun.com                                                                  */
/*********************************************************************/

#ifndef __AUTO_I2C_MASTER_H__
#define __AUTO_I2C_MASTER_H__

/*
*    AIH_i2c_master_gpio_init:  init the I2C function by special SDA&SCL gpio num 
*    para:
*            sdaGpioNum==the gpio num of I2C, must 0< sdaGpioNum<15
*            sclGpioNum==the gpio num of I2C, must 0< sclGpioNum<15
*
*    return:
*           NONE
*/
int32_t AIH_i2c_master_gpio_init(int8_t sdaGpioNum, int8_t sclGpioNum);

/*
*    AIH_i2c_master_start:  start the I2C function, before each write cmd must call this
*    para:
*            NONE
*
*    return:
*           NONE
*/
void AIH_i2c_master_start(void);

/*
*    AIH_i2c_master_stop:  stop the I2C function, after each write cmd must call this
*    para:
*            NONE
*
*    return:
*           NONE
*/
void AIH_i2c_master_stop(void);

/*
*    AIH_i2c_master_setAck:  set the ACK LEVLE 0/1 when read
*    para:
*            level==the level of the ACK signal
*
*    return:
*           VOID
*/
void AIH_i2c_master_setAck(uint8 level);

/*
*    AIH_i2c_master_getAck:  get the ACK LEVLE 0/1
*    para:
*            NONE
*
*    return:
*           level==the level of the ACK signal, 0/1
*/
uint8 AIH_i2c_master_getAck(void);

/*
*    AIH_i2c_master_readByte:  read the Byte data send by slave
*    para:
*            NONE
*
*    return:
*           data==the Byte of the read
*/
uint8 AIH_i2c_master_readByte(void);

/*
*    AIH_i2c_master_writeByte:  write the Byte data to slave
*    para:
*            data==the Byte of the send
*
*    return:
*           NONE
*/
void AIH_i2c_master_writeByte(uint8 wrdata);




/*eg:
LOCAL bool ICACHE_FLASH_ATTR
Master_i2c_write(uint8 addr, uint8 *pData, uint16 len)
{
    uint8 ack;
    uint16 i;

    auto_i2c_master_start();
    auto_i2c_master_writeByte(addr);
    ack = auto_i2c_master_getAck();

    if (ack) {
        os_printf("addr[0x%x] not ack when tx write cmd\n", addr);
        auto_i2c_master_stop();
        return false;
    }

    for (i = 0; i < len; i++) {
        auto_i2c_master_writeByte(pData[i]);

        ack = auto_i2c_master_getAck();
        if (ack) {
            os_printf("data[0x%x] not ack when tx write cmd\n", pData[i]);
            auto_i2c_master_stop();
            return false;
        }
    }
    auto_i2c_master_stop();
    
    return true;
}
*/

#endif
