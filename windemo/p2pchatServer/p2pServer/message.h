#pragma once
#include <stdint.h>
#include <evpp/udp/udp_message.h>
#define MSG_MAGIC 0x8964 
#define MSG_MAGICLEN 2
#define MSG_TYPELEN 2
#define MSG_BODYLEN 4
#define MSG_HEADLEN (MSG_MAGICLEN + MSG_TYPELEN + MSG_BODYLEN)
/* a message is a UDP datagram with following structure:
   -----16bits--+---16bits--+-----32bits----------+---len*8bits---+
   --  0x8964   + msg type  + msg length(exclude) + message body  +
   -------------+-----------+---------------------+---------------+
*/
#pragma once
#include "packing.hpp"

#define SEND_BUFSIZE 1024
#define RECV_BUFSIZE 1024
typedef enum _MessageType MessageType;
typedef struct _Message Message;
typedef struct _MessageHead MessageHead;
enum _MessageType {
  MTYPE_LOGIN = 0,
  MTYPE_LOGOUT,
  MTYPE_LIST,
  MTYPE_PUNCH,
  MTYPE_PING,
  MTYPE_PONG,
  MTYPE_REPLY,
  MTYPE_TEXT,
  MYTYP_SEND_SVR,
  MTYPE_END
};
/*
__attribute__ ((packed)) 的作用就是告诉编译器取消结构在编译过程中的优化对齐,按照实际占用字节数进行对齐，是GCC特有的语法。
这个功能是跟操作系统没关系，跟编译器有关，gcc编译器不是紧凑模式的，我在windows下，用vc的编译器也不是紧凑的，
用tc的编译器就是紧凑的。例如：

在TC下：struct my{ char ch; int a;} sizeof(int)=2;sizeof(my)=3;（紧凑模式）

在GCC下：struct my{ char ch; int a;} sizeof(int)=4;sizeof(my)=8;（非紧凑模式）

在GCC下：struct my{ char ch; int a;}__attrubte__ ((packed)) sizeof(int)=4;sizeof(my)=5
*/
#if WIN32
PACKED(
struct _MessageHead {
  uint16_t magic;
  uint16_t type;
  uint32_t length;
}
);
#else
struct _MessageHead {
  uint16_t magic;
  uint16_t type;
  uint32_t length;
}__attribute__((packed));
#endif

struct _Message {
  MessageHead head;
  const char* body;
};

const char* strmtype(MessageType type);
int msg_pack(Message msg, char* buf, unsigned int bufsize);
Message msg_unpack(const char* buf, unsigned int bufsize);

bool udp_send_msg(evpp_socket_t fd, const  sockaddr* addr, Message msg);
bool udp_send_buf(evpp_socket_t fd, const  sockaddr* addr,
  MessageType type, const char* buf, unsigned int len);
bool udp_send_text(evpp_socket_t fd, const  sockaddr* addr,
  MessageType type, const char* text);