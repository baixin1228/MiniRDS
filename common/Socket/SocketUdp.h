#ifndef _SOCKET_UDP_H
#define _SOCKET_UDP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdint.h>

int SocketUdpServerInit(char *addr,int port);
int SocketUdpServerSendData(char * data,int size,struct sockaddr_in * client_addr);
int SocketUdpServerReadData(char * buffer,int size,struct sockaddr_in * receive_addr);
int SocketUdpServerClose();
int SocketUdpClientInit(char * addr,int port);
int SocketUdpClientSendData(char * data,int size);
int SocketUdpClientReceiveData(char *buffer,int size);
int SocketUdpClientClose();




#endif
