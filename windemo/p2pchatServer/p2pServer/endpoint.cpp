

/*
sockaddr��sockaddr_in���������ݶ���һ���ģ���������ʹ����������

����Ա��Ӧ����sockaddr��sockaddr�Ǹ�����ϵͳ�õ�

����ԱӦʹ��sockaddr_in����ʾ��ַ��sockaddr_in�����˵�ַ�Ͷ˿ڣ�ʹ�ø����㡣

include <netinet/in.h>

struct sockaddr {
	unsigned short    sa_family;    // 2 bytes address family, AF_xxx
	char              sa_data[14];     // 14 bytes of protocol address
};

// IPv4 AF_INET sockets:

struct sockaddr_in {
	short            sin_family;       // 2 bytes e.g. AF_INET, AF_INET6
	unsigned short   sin_port;    // 2 bytes e.g. htons(3490)
	struct in_addr   sin_addr;     // 4 bytes see struct in_addr, below
	char             sin_zero[8];     // 8 bytes zero this if you want to
};

struct in_addr {
	unsigned long s_addr;          // 4 bytes load with inet_pton()
};
*/

// error C4996 : 'inet_ntoa' : Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

#define _WINSOCK_DEPRECATED_NO_WARNINGS
//http://www.cplusplus.com/forum/general/141779/
// #define this before any windows headers are included
#define _WIN32_WINNT _WIN32_WINNT_WIN8 // Windows 8.0
#include <Ws2tcpip.h>
// #pragma comment( lib, "Ws2_32.lib" ) // link with Ws2_32.lib 
#include "endpoint.h"
#include <stdio.h>

#define INET_PORTSTRLEN 5
#define TUPLE_LEN (INET_ADDRSTRLEN + INET_PORTSTRLEN + 1)
int ep_equal(endpoint_t lp, endpoint_t rp) {
  return ((lp.sin_family == rp.sin_family) &&
	(lp.sin_addr.s_addr == rp.sin_addr.s_addr) &&
	(lp.sin_port == rp.sin_port));
}

/* NOT THREAD SAFE */
char* ep_tostring(endpoint_t ep) {
  static char tuple[TUPLE_LEN];
  snprintf(tuple, TUPLE_LEN, "%s:%d",
	inet_ntoa(ep.sin_addr),
	ntohs(ep.sin_port));
  return tuple;
}

endpoint_t ep_fromstring(const char* tuple) {
  int size = TUPLE_LEN;//windows����28��sprintf_s ��˵̫С�ˣ��쳣�������ڱ��һ�㣿��Ϊ100����
#if 0 
  char _tuple[TUPLE_LEN];
#else
  char _tuple[100];
#endif
  const char* host = NULL;
  const char* port = NULL;
//  sprintf_s(_tuple, "%s", tuple);
  sprintf(_tuple, "%s", tuple);
  host = strtok(_tuple, ":");
  port = strtok(NULL, ":");
  if (host == NULL || port == NULL) {
	host = "255.255.255.255";
	port = "0";
  }
  return ep_frompair(host, atoi(port));
}

endpoint_t ep_frompair(const char* host, short port) {
  endpoint_t ep;
  memset(&ep, 0, sizeof ep);
  ep.sin_family = AF_INET;
  ep.sin_addr.s_addr = inet_addr(host);
  ep.sin_port = htons(port);
  return ep;
}
