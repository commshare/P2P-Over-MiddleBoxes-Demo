/* NOT THREAD SAFE */

/*
sockaddr和sockaddr_in包含的数据都是一样的，但他们在使用上有区别：

程序员不应操作sockaddr，sockaddr是给操作系统用的

程序员应使用sockaddr_in来表示地址，sockaddr_in区分了地址和端口，使用更方便。

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
