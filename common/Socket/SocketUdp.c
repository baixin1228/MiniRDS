#include "SocketUdp.h"
#include <errno.h>

int socket_server_fb;
int socket_udp_server_is_open = 0;


int SocketUdpServerInit(char *addr,int port)
{
struct sockaddr_in server_bind_address;	bzero(&server_bind_address,sizeof(server_bind_address));
	server_bind_address.sin_family=AF_INET;
	server_bind_address.sin_addr.s_addr=inet_addr(addr);
	server_bind_address.sin_port=htons(port);

	socket_server_fb=socket(PF_INET,SOCK_DGRAM,0);
	if (bind(socket_server_fb, (struct sockaddr *)&server_bind_address, sizeof(server_bind_address)) < 0)
	{
		printf("bind error!\n");
		return -1;
	}

	socket_udp_server_is_open = 1;
	return 0;
}

int SocketUdpServerSendData(char * data,int size,struct sockaddr_in * client_addr)
{
	if(socket_udp_server_is_open)
	{
		sendto(socket_server_fb,data,size,0,(struct sockaddr *)client_addr,sizeof(struct sockaddr_in));
		return 0;
	}
	else
	{
		printf("upd server not init!\n");
		return -1;
	}
}

socklen_t receive_client_len;

int SocketUdpServerReadData(char * buffer,int size,struct sockaddr_in * receive_addr)
{
	receive_client_len = sizeof(struct sockaddr_in);
	if(socket_udp_server_is_open)
	{
		int n = recvfrom(socket_server_fb, buffer, size, 0,
			(struct sockaddr *)receive_addr, &receive_client_len);
		if (n <= 0)
		{
			printf("udp server recv error");
			return -1;
        }
		else if(n > 0)
		{
			return n;
		}
	}
	else
	{
		printf("upd server not init!\n");
		return -1;
	}
}

int SocketUdpServerClose()
{
	if(socket_udp_server_is_open) 
	{
		close(socket_server_fb);

		return 0;
	}else{
		printf("upd server not init!\n");
		return -1;
	}
}

int socket_client_fb;
struct sockaddr_in server_address;
int socket_udp_client_is_open = 0;

int SocketUdpClientInit(char * addr,int port)
{
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr(addr);
	server_address.sin_port=htons(port);

	socket_client_fb=socket(PF_INET,SOCK_DGRAM,0);
    printf("%s %d\n",addr,port);
	socket_udp_client_is_open = 1;
	return 0;
}

int SocketUdpClientSendData(char * data,int size)
{
	if(socket_udp_client_is_open)
	{
		sendto(socket_client_fb, data, size, 0, (struct sockaddr *)&server_address, sizeof(server_address));
		return 0;
	}
	else
	{
		printf("upd client not init!\n");
		return -1;
	}
}

int SocketUdpClientReceiveData(char *buffer,int size)
{
	if(socket_udp_client_is_open)
	{
		int ret = recvfrom(socket_client_fb, buffer, size, 0, NULL, NULL);
		if (ret == -1)
		{
			if (errno == EINTR)
			printf("udp client recv error!");
            return -1;
		}
		return ret;
	}
	else
	{
		printf("upd client not init!\n");
		return -1;
	}
}

int SocketUdpClientClose()
{

	if(socket_udp_client_is_open) 
	{
		close(socket_client_fb);
		return 0;
	}else
	{
		printf("upd client not init!\n");
		return -1;
	}
}
