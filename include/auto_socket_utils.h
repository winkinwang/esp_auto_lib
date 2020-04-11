/*********************************************************************/
/* Filename:    auto_socket_utils.h                                                                             */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: the header of system socket(UDP/TCP) utils of ESP8266                                           */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*   Create:   2015-12-04                                                           		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2015-12-04    wangyunjin  Created                                                             */
/*     email:wyj0617mail@aliyun.com                                                                  */
/*********************************************************************/

#ifndef _SOCKET_UTILS_H
#define _SOCKET_UTILS_H

#include "ip_addr.h"
#include "espconn.h"

typedef void(*get_host_cb_t)(int8_t *ipaddr);
int32_t get_addr_by_host(char *hostName, get_host_cb_t cb);


//for UDP
int32_t udp_server_create(int32_t localPort, espconn_recv_callback cbFunc);

void udp_server_delete(int32_t udpSvrHandle);

int32_t udp_send_msg(uint8_t *dstIp, int32_t dstPort, uint8 *psent, uint16 length);

//for TCP
typedef void *  TCPHANDLE;

typedef enum _tcp_evt_e{
    E_TCP_EVT_CONNECTED=0,
    E_TCP_EVT_NEW_SUB_CONNECTION,
    E_TCP_EVT_SEND_MSG,
    E_TCP_EVT_RECV_MSG,
    E_TCP_EVT_RECONNECT,
    E_TCP_EVT_DISCONNECTED,
    E_TCP_EVT_MAX
}TCP_EVT_E;
typedef void (* tcp_event_cb_t)(TCP_EVT_E evtType, void *data, int32_t len, void *userdata);


//isChkMsg==1,  msg must find head of "<<" and end of">>", and the return to user
int32_t tcp_client_create(int8_t isChkMsg);
int32_t tcp_client_create_ssl(int8_t isChkMsg);


int32_t tcp_client_connect_svr(int32_t tcpHandle, uint8_t *svrIp, int32_t svrPort, tcp_event_cb_t evt_cb, void *userdata);

int32_t tcp_client_send_msg(int32_t tcpHandle, uint8 *sndData, uint16 length);

int32_t tcp_client_disconnect_svr(int32_t tcpHandle);

int32_t tcp_client_delete(int32_t tcpHandle);



typedef void (*tcp_listen_cb_t)(TCP_EVT_E evtType, int32_t subTcpIndex, void *userdata);
TCPHANDLE tcp_server_create(int32_t lisPort);

int32_t tcp_server_start(TCPHANDLE tcpHandle, tcp_listen_cb_t evt_cb, void *userdata);

int32_t tcp_server_set_sub_connection_cb(TCPHANDLE tcpHandle, int32_t subTcpIndex, tcp_event_cb_t evt_cb, void *userdata);

int32_t tcp_server_sub_send_msg(TCPHANDLE tcpHandle, int32_t subTcpIndex, uint8 *sndData, uint16 length);

int32_t tcp_server_sub_disconnect_client(TCPHANDLE tcpHandle, int32_t subTcpIndex);

int32_t tcp_server_delete(TCPHANDLE *pTcpHandle);

#endif
