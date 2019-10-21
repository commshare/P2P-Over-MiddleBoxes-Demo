#include <string.h>
#include <stdio.h>
#include "message.h"
#if WIN32
#include <winsock.h>
#endif



const char* strmtype(MessageType type) {
  switch (type) {
  case MTYPE_LOGIN:   return "LOGIN";
  case MTYPE_LOGOUT:  return "LOGOUT";
  case MTYPE_LIST:    return "LIST";
  case MTYPE_PUNCH:   return "PUNCH";
  case MTYPE_PING:    return "PING";
  case MTYPE_PONG:    return "PONG";
  case MTYPE_REPLY:   return "REPLY";
  case MTYPE_TEXT:    return "TEXT";
  default:            return "UNKNOW";
  }
}

/* htons https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-htons
The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
//The htons function returns the value in TCP/IP network byte order.
u_short htons(
  u_short hostshort// (A 16-bit number in host byte order.)
);

ntohs =net to host short int 16λ
htons=host to net short int 16λ
ntohl =net to host long int 32λ
htonl=host to net long int 32λ

*/

//to network order
/* return bytes serialized */
int msg_pack(Message msg, char* buf, unsigned int bufsize) {
  if (bufsize < MSG_HEADLEN + msg.head.length) {
	printf("buf too small");
	return 0;
  }
  int16_t m_magic = htons(msg.head.magic);
  int16_t m_type = htons(msg.head.type);
  int32_t m_length = htonl(msg.head.length);
  int index = 0;
  memcpy(buf + index, &m_magic, MSG_MAGICLEN);
  index += MSG_MAGICLEN;
  memcpy(buf + index, &m_type, MSG_TYPELEN);
  index += MSG_TYPELEN;
  memcpy(buf + index, &m_length, MSG_BODYLEN);
  index += MSG_BODYLEN;
  memcpy(buf + index, msg.body, msg.head.length);
  index += msg.head.length;
  return index;
}


/*
   Message body is a pointer to buf + len(head)
*/
Message msg_unpack(const char* buf, unsigned int buflen) {
  Message m;
  memset(&m, 0, sizeof(m));
  if (buflen < MSG_HEADLEN) {
	// at least we won't get an overflow
	return m;
  }
  int index = 0;
  //network to host short 
  m.head.magic = ntohs(*(uint16_t*)(buf + index));
  index += sizeof(uint16_t);
  if (m.head.magic != MSG_MAGIC) {
	return m;
  }
  m.head.type = ntohs(*(uint16_t*)(buf + index));
  index += sizeof(uint16_t);
  //uint32
  m.head.length = ntohl(*(uint32_t*)(buf + index));
  index += sizeof(uint32_t);
  //buflen - 2 - 2 -4 才是消息吧
  if (index + m.head.length > buflen) {
	printf("message declared body size(%d) is larger than what's received (%d), truncating\n",
	  m.head.length, buflen - MSG_HEADLEN);
	m.head.length = buflen - index;
  }
  if (MTYPE_PUNCH == m.head.type)
  {
	std::cout << " msg body size " << m.head.length << " buflen " << buflen << std::endl;
  }

  m.body = buf + index;
  if (MYTYP_SEND_SVR == m.head.type || MTYPE_PUNCH == m.head.type)
  {
	std::cout << " msg body size " << m.head.length << " buflen " << buflen << std::endl;
	if (m.body != nullptr)
	{
	  char temp[100];
	  memset(temp, 0, 100);
	  memcpy(temp, m.body, m.head.length);
	  temp[m.head.length] = '\0';
	  std::cout << " MYTYP_SEND_SVR " << m.head.length << " buflen " << buflen << " body " << temp << std::endl;
	}	
  }
  return m;
}


// send a Message
bool udp_send_msg(evpp_socket_t fd, const  sockaddr* addr, Message msg) {
  char buf[SEND_BUFSIZE] = { 0 };
  int wt_size = msg_pack(msg, buf, SEND_BUFSIZE);
  return evpp::udp::SendMessage(fd,addr,buf,wt_size);
  /* return sendto(sock, buf, wt_size,
	 MSG_DONTWAIT, (struct sockaddr*) & peer, sizeof(peer));*/
}
// send a buf with length
bool udp_send_buf(evpp_socket_t fd, const  sockaddr* addr,
  MessageType type, const char* buf, unsigned int len) {
  Message m;
  m.head.magic = MSG_MAGIC;
  m.head.type = type;
  m.head.length = len;
  m.body = buf;
  return udp_send_msg(fd, addr, m);
}
// send a NULL terminated text
bool udp_send_text(evpp_socket_t fd, const  sockaddr* addr,
  MessageType type, const char* text) {
  unsigned int len = text == NULL ? 0 : strlen(text);
  return udp_send_buf(fd, addr, type, text, len);
}
