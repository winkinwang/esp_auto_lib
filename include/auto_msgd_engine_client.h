
/*********************************************************************/
/* Filename:    auto_msgd_engine_client.h                                                                             */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: the header of msgd client , subcriber/publisher msg from/to            */
/*                  the Group and User, in a engine for messageDispatcher                   */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*   Create:   2016-07-04                                                           		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2016-07-04    wangyunjin  Created                                                             */
/*     2016-12-29    wangyunjin  update                                                              */
/*********************************************************************/


#ifndef _AUTO_MSGD_ENGINE_CLIENT_H_
#define _AUTO_MSGD_ENGINE_CLIENT_H_

#ifndef NULL
#define NULL 0
#endif


typedef enum
{
	EN_ESP_MSGD_CLIENT_EVT_TYPE_CONNECTION_SUCCESS=0x2000,//new client connect
	EN_ESP_MSGD_CLIENT_EVT_TYPE_CONNECTION_KEEPALIVE,  //socket keepalive
	EN_ESP_MSGD_CLIENT_EVT_TYPE_CONNECTION_CLOSE,  //socket closed
	EN_ESP_MSGD_CLIENT_EVT_TYPE_MSG_RECEIVE_NOTIFY,  //msg has  receive notify	
	EN_ESP_MSGD_CLIENT_EVT_TYPE_MAX
}ESP_MSGD_CLIENT_EVT_TYPE_E;

typedef enum
{
    EN_ESP_MSGD_CLIENT_TYPE_NORMAL=0x1000,//for normal P2P
	EN_ESP_MSGD_CLIENT_TYPE_PUBLISHER,//for publisher
	EN_ESP_MSGD_CLIENT_TYPE_SUBSCRIBER,     //for subcriber
	EN_ESP_MSGD_CLIENT_TYPE_BOTH,          // for publisher and subcriber
	EN_ESP_MSGD_CLIENT_TYPE_MAX
}ESP_MSGD_CLIENT_TYPE_E;

typedef struct
{
    int32_t errCode;
    int32_t msgId;
}ESP_MSGD_CLIENT_MSG_RESPONSE_INFO_S;


typedef struct
{
    ESP_MSGD_CLIENT_EVT_TYPE_E evtType;
    union
    {
        ESP_MSGD_CLIENT_MSG_RESPONSE_INFO_S responseInfo;
    }info;
    void *userData;
}ESP_MSGD_CLIENT_EVT_INFO_S;


typedef void * ESPMSGDCLIHandle;

typedef void (*ESP_MSGD_CLIENT_FUNC_EVT_CB)(ESPMSGDCLIHandle handle, ESP_MSGD_CLIENT_EVT_INFO_S *evtInfo);
typedef void (*ESP_MSGD_CLIENT_FUNC_MSG_CB)(ESPMSGDCLIHandle handle, char *inBuff, int inBuffLen);


/*
* function:  esp_msgd_client_init
* Target: initialize the instance conenct to msgd-server and get the handle
*
* para: handle---the return handle of the server instanse
*         cliType----register client type, subscriber or publisher, both
*         remoteHostIp---the msgd server IP addr
* 	    remoteHostPort---the msgd server port to tcp connect
*
* return: =0---successful
* 		-1---failed
*
*/
int32_t esp_msgd_client_init(ESPMSGDCLIHandle *handle, ESP_MSGD_CLIENT_TYPE_E cliType, uint8 *remoteHostIp, int remoteHostPort);


/*
* function:  esp_msgd_client_register_topic
* Target: register one group and one user in msgd server for recv msg about this group and user
*
* para: handle---the handle create in msgd_client_init
* 	    groupName---the group listenning message
* 	    userName---the user listenning message
*
* return: =0---successful
* 		-1---failed
*
*/
int32_t esp_msgd_client_register_topic(ESPMSGDCLIHandle handle, char *groupName, char *userName);


/*
* function:  esp_msgd_client_set_keepalive
* Target: send the keepalive msg to msgd server when internvalue seconds to keep the tcp connection
*
* para: handle---the handle create in msgd_client_init
* 	    interntimeSec---the intervalue seconds when sending message, must between 1~600 sec
* 	    aliveMsg---the keepalive Msg to send
* 	    aliveMsgLen---the keepalive Msg length, must between 1~128
*
* return: =0---successful
* 		-1---failed
*/
int32_t esp_msgd_client_set_keepalive(ESPMSGDCLIHandle handle, int32_t interntimeSec, char *aliveMsg, int32_t aliveMsgLen);


/*
* function:  esp_msgd_client_set_listener
* Target: set the callback function to recv the connection event and message from msgd server
*
* para: handle---the handle create in msgd_client_init
* 	    evtCb---the connection event callback function
* 	    msgCb---the msg recv from msgd server callback funtion
* 	    userData---the private user data when callback function calling
*
* return: =0---successful
* 		-1---failed
*/
int32_t esp_msgd_client_set_listener(ESPMSGDCLIHandle handle, ESP_MSGD_CLIENT_FUNC_EVT_CB evtCb, ESP_MSGD_CLIENT_FUNC_MSG_CB msgCb, void *userData);

/*
* function:  esp_msgd_client_start
* Target: start the task to listen the message
*
* para: handle---the handle create in msgd_client_init
*         encrypt---the encrypt key string for encode the msg
*
* return: =0---successful
* 		-1---failed
*/
int32_t esp_msgd_client_start(ESPMSGDCLIHandle handle, char *encrypt);


/*
* function:  esp_msgd_client_send_p2p_msg
* Target: send the msg to the dstGroup-dstUser
*
* para: handle---the handle create in msgd_client_init
* 	    dstGroup---the dest group name of sending
* 	    dstUser---the dest user name of sending
* 	    persistTime---the persistent Time(sec) if publishing dstObj offline
* 	    msg---the msg content  of publishing
* 	    msgLen---the msg content .length of publishing
*         msgId-----the id of the special msg
*
* return: =0---successful
* 		-1---failed
*/
int32_t esp_msgd_client_send_p2p_msg(ESPMSGDCLIHandle handle, char *dstGroup, char *dstUser, int32_t persistTime, char *msg, int32_t msgLen, int32_t msgId);

/*
* function:  esp_msgd_client_publish_msg
* Target: send publish-msg to the dstGroup, and this client must be TYPE=EN_MSGD_CLIENT_TYPE_PUBLISHER or EN_MSGD_CLIENT_TYPE_BOTH
*
* para: handle---the handle create in msgd_client_init
* 	    dstGroup---the dest group name of publishing
* 	    persistTime---the persistent Time(sec) if publishing dstObj offline
* 	    msg---the msg content  of publishing
* 	    msgLen---the msg content .length of publishing
*         msgId-----the id of the special msg
*
* return: =0---successful
* 		-1---failed
*/
int32_t esp_msgd_client_publish_msg(ESPMSGDCLIHandle handle, char *dstGroup, int32_t persistTime, char *msg, int32_t msgLen, int32_t msgId);

/*
* function:  esp_msgd_client_stop
* Target: stop the task, not listen the message
*
* para: handle---the handle create in msgd_client_init
*
* return: =0---successful
* 		-1---failed
*/
int32_t esp_msgd_client_stop(ESPMSGDCLIHandle handle);

/*
* function:  esp_msgd_client_uninit
* Target: stop the task and destroy the object, disconnect to the msgd server
*
* para: handle---the handle create in msgd_client_init, and handle==NULL when success
*
* return: =0---successful
* 		-1---failed
*/
int32_t esp_msgd_client_uninit(ESPMSGDCLIHandle *handle);

#endif //_AUTO_MSGD_ENGINE_CLIENT_H_


