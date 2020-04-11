/*********************************************************************/
/* Filename:    auto_pwm_utils.h                                                                             */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: the header of pwm utils of ESP8266                                           */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*   Create:   2016-10-04                                                           		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2016-10-04    wangyunjin  Created                                                             */
/*     email:wyj0617mail@aliyun.com                                                                  */
/*********************************************************************/

#ifndef __AUTO_PWM_UTILS_H__
#define __AUTO_PWM_UTILS_H__

/*SUPPORT UP TO 8 PWM CHANNEL*/
#define AUTO_PWM_CHANNEL_NUM_MAX 8 
#define AUTO_PWM_FREQUENCE_MAX 1000 
#define AUTO_PWM_DUTY 100


/*
*    AIH_pwm_init:  init the PWM function by special GPIOs, pwm_init should be called only once 
*    para:
*            freq==the frequnce of the PWM, must 0< freq<2000
*            pin_info_list==the GPIOs of enable PWM function, eg:pin_info_list[][3]={{PERIPHS_IO_MUX_MTMS_U, 14, FUNC_GPIO14},...}
*            pwm_channel_num====the GPIOs NUM, the lenth of pin_info_list array
*
*    return:
*           NONE
*/
void AIH_pwm_init(uint16 freq, uint32 (*pin_info_list)[3], uint32 pwm_channel_num);

/*
*    AIH_pwm_start:  start the PWM function by special GPIOs
*    para:
*            NONE
*
*    return:
*           NONE
*/
void AIH_pwm_start(void);

/*
*    AIH_pwm_set_duty:  set the PWM duty by special channel
*    para:
*            duty==the duty of the PWM, must 0<= duty<=100
*            channel==the channel of GPIOs PWM array, 0<=channel<pwm_channel_num
*
*    return:
*           VOID
*/
void AIH_pwm_set_duty(uint8 duty, uint8 channel);

/*
*    AIH_pwm_get_duty:  get the PWM duty by special channel
*    para:
*            channel==the channel of GPIOs PWM array, 0<=channel<pwm_channel_num
*
*    return:
*           duty==the duty of the PWM, must 0<= duty<=100
*/
uint8 AIH_pwm_get_duty(uint8 channel);


/*
*    AIH_pwm_set_freq:  set the PWM frequnce for all channel
*    para:
*            freq==the frequence of the PWM, must 0<= duty<=2000
*            channel==the channel of GPIOs PWM array, 0<=channel<pwm_channel_num
*
*    return:
*           VOID
*/
void AIH_pwm_set_freq(uint16 freq);

/*
*    AIH_pwm_get_freq:  get the PWM frequnce of all channel
*    para:
*            NONE
*
*    return:
*           freq==the frequence of the PWM, must 0<= duty<=2000
*/
uint16 AIH_pwm_get_freq(void);
#endif

