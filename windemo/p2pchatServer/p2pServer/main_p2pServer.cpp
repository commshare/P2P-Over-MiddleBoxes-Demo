// p2pServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<sstream>
#include <iostream>
#include <evpp/udp/udp_server.h>
#include <evpp/udp/udp_message.h>
#include <vector>
#if WIN32
#include <windows.h> 
#endif
#include "message.h"
#include "handler.h"
using namespace std::placeholders;  // 对于 _1, _2, _3...
/*https://handong1587.github.io/programming_study/2015/10/23/gflags-build-problems-winx86-vs2015.html
1>gflags_static_debug.lib(gflags.obj) : error LNK2019: 无法解析的外部符号 __imp__PathMatchSpecA@8，该符号在函数 "public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __thiscall google::`anonymous namespace'::CommandLineFlagParser::ProcessOptionsFromStringLocked(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &,enum google::FlagSettingMode)" (?ProcessOptionsFromStringLocked@CommandLineFlagParser@?A0xf0d9b533@google@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV45@W4FlagSettingMode@3@@Z) 中被引用
1>D:\mycode\P2P-Over-MiddleBoxes-Demo\windemo\p2pchatServer\Debug\p2pServer.exe : fatal error LNK1120: 1 个无法解析的外部命令
Add “shlwapi.lib” to “Project - Property - Linker - Input - Additional Dependencies”.


*/
//D:\mycode\P2P-Over-MiddleBoxes-Demo\windemo\p2pchatServer\bin/Debug/evpp_static.lib
#ifdef _WIN32
#include "../winmain-inl.h"
#endif
recvbuf_callback_t g_recvbuf_clk=nullptr;
int main(int argc, char* argv[]) {
  std::vector<int> ports = { 1053 };
  //创建一个udp服务器
  evpp::udp::Server server;
  Handler h;
  g_recvbuf_clk = std::bind(&Handler::OnRecv,&h,_1,_2,_3,_4);
  //这个是干啥用的
  server.SetThreadDispatchPolicy(evpp::ThreadDispatchPolicy::kIPAddressHashing);
  server.SetMessageHandler([](evpp::EventLoop* loop, evpp::udp::MessagePtr& msg) {
	std::stringstream oss;
	oss << "func=" << __FUNCTION__ << " OK"
	  << " body=" << std::string(msg->data(), msg->size()) << "\n";
	evpp_socket_t fd = msg->sockfd();
	const sockaddr*  remote_addr = msg->remote_addr();
	if (g_recvbuf_clk)
	{
	  g_recvbuf_clk(fd,remote_addr,msg->data(),msg->length());
	}
	});
  server.Init(ports);
  server.Start();

  while (!server.IsStopped()) {
	usleep(1);
  }
  return 0;
}