/* NOT THREAD SAFE */

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
