#include "handler.h"
#include "evpp/sockets.h"
#include "evpp/logging.h"

void Handler::OnRecv(int server_sock, const sockaddr* from, const char* buf, size_t dlen)
{
  Message msg = msg_unpack(buf, dlen);
  if (msg.head.magic != MSG_MAGIC || msg.body == NULL) 
  {
	printf("Invalid message(%d bytes): {0x%x,%d,%d} %p", dlen,
	  msg.head.magic, msg.head.type, msg.head.length, msg.body);
	return;
  }
  LOG_TRACE << "RECV " << msg.head.length << " bytes from " << evpp::sock::ToIPPort(from)
	<< " msg type " << strmtype((MessageType)msg.head.type);// << " body :" << msg.body;
	
 
  switch (msg.head.type) {
  case MTYPE_LOGIN:
  {
	//if (0 == eplist_add(g_client_pool, from)) {
	//  log_info("%s logged in", ep_tostring(from));
	//  udp_send_text(sock, from, MTYPE_REPLY, "Login success!");
	//}
	//else {
	//  log_warn("%s failed to login", ep_tostring(from));
	//  udp_send_text(sock, from, MTYPE_REPLY, "Login failed");
	//}
  }
  break;
  case MTYPE_LOGOUT:
  {
	/*if (0 == eplist_remove(g_client_pool, from)) {
	  log_info("%s logged out", ep_tostring(from));
	  udp_send_text(sock, from, MTYPE_REPLY, "Logout success");
	}
	else {
	  log_info("%s failed to logout", ep_tostring(from));
	  udp_send_text(sock, from, MTYPE_REPLY, "Logout failed");
	}*/
  }
  break;
  case MTYPE_LIST:
  {
	/*log_info("%s quering list", ep_tostring(from));
	char text[SEND_BUFSIZE - MSG_HEADLEN] = { 0 };
	for (eplist_t* c = g_client_pool->next; c != NULL; c = c->next) {
	  if (ep_equal(c->endpoint, from)) strcat(text, "(you)");
	  strcat(text, ep_tostring(c->endpoint));
	  if (c->next) strcat(text, ";");
	}
	udp_send_text(sock, from, MTYPE_REPLY, text);*/
  }
  break;
  case MTYPE_PUNCH:
  {
	/*endpoint_t other = ep_fromstring(msg.body);
	log_info("punching to %s", ep_tostring(other));
	udp_send_text(sock, other, MTYPE_PUNCH, ep_tostring(from));
	udp_send_text(sock, from, MTYPE_TEXT, "punch request sent");*/
  }
  break;
  case MTYPE_PING:
	udp_send_text(server_sock, from, MTYPE_PONG, NULL);
	break;
  case MTYPE_PONG:
	break;
  default:
	//udp_send_text(sock, from, MTYPE_REPLY, "Unkown command");
	break;
  }
}