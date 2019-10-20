#pragma once
#include <functional>
#include <map>
#include <list>
#include <string>
#include "message.h"
#include <set>

using recvmsg_callback_t = std::function<void(int , const  sockaddr* , Message )>;
using recvbuf_callback_t = std::function<void(int , const  sockaddr* , const char* , size_t )>;
//一个集合（set）是一个容器，它其中所包含的元素的值是唯一的
using clientpool_t =std::shared_ptr<std::set<std::string>>;//std::map<int, std::list</*const*/ sockaddr>>;

class Handler {
public:
  Handler() :clientpool_(std::make_shared<std::set<std::string>>()){}
  ~Handler() {}
  void OnRecv(int server_sock, const  sockaddr* from, const char* d, size_t dlen);
  clientpool_t clientpool_;
};