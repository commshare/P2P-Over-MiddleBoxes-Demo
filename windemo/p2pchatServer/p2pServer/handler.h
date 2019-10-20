#pragma once
#include <functional>
#include <map>
#include <list>
#include "message.h"

using recvmsg_callback_t = std::function<void(int , const  sockaddr* , Message )>;
using recvbuf_callback_t = std::function<void(int , const  sockaddr* , const char* , size_t )>;
using clienpool_t = std::map<int, std::list</*const*/ sockaddr>>;

class Handler {
public:
  Handler() {}
  ~Handler() {}
  void OnRecv(int server_sock, const  sockaddr* from, const char* d, size_t dlen);
  clienpool_t clientpool_;
};