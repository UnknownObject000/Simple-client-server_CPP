#include "Packets.h"
#pragma once

namespace srv
{

class NTP_Client
{
public:

  static NTP_Client &Instance();
  static NTP_Client &Instance(std::string ipaddr);
  static NTP_Client &Instance(std::string ipaddr,int port);
  time_t GetCurrentTimestamp();

private:

  NTP_Client();
  NTP_Client(std::string ipaddr);
  NTP_Client(std::string ipaddr,int port);
  ~NTP_Client(){};
  NTP_Client(const NTP_Client &) = delete;
  NTP_Client operator=(const NTP_Client &) = delete;

  unsigned long long NTP_TIMESTAMP_DELTA = 2208988800ull;
  udp::endpoint ntpServerEP;
  udp::socket *uSocket; //UDP client-socket to communicate with NTP server
};

} // namespace srv
