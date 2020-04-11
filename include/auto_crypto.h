/*********************************************************************/
/* Filename:    AIH_crypto.h                                                                               	   */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: the description os crypto  module		                                     */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*   Create:   2016-10-18                                                           		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2016-10-18     wangyunjin  Created                                                             */
/*********************************************************************/

#ifndef _AIH_CRYPTO_H_
#define _AIH_CRYPTO_H_


/*
* function:  AIH_crypto_encode
* Target: encrypt encode srcData by secretKey
*
* para: srcData---the source string
* 	    srcDataLen---the source string length
* 	    secretKey---the encode secret string
* 	    secretKeyLen---the encode secret string length
* 	    dstData---the output buffer after encode
* 	    dstDataMaxLen---the output buffer max length
*
* return: =srcDataLen---successful
* 		other ---failed
*/
int32_t  AIH_crypto_encode(char *srcData, int32_t srcDataLen, char *secretKey, int32_t secretKeyLen, char *dstData, int32_t dstDataMaxLen);

/*
* function:  OS_crypto_decode
* Target: encrypt decode srcData by secretKey
*
* para: srcData---the source string
* 	    srcDataLen---the source string length
* 	    secretKey---the encode secret string
* 	    secretKeyLen---the decode secret string length
* 	    dstData---the output buffer after decode
* 	    dstDataMaxLen---the output buffer max length
*
* return: =srcDataLen---successful
* 		other ---failed
*/

int32_t  AIH_crypto_decode(char *srcData, int32_t srcDataLen, char *secretKey, int32_t secretKeyLen, char *dstData, int32_t dstDataMaxLen);


#endif	//_OS_CONF_H

