#include "NTP_Client.h"
#include <unistd.h>

int main(int argc, char* argv[]) 
{
	std::string ip;
	if(argc<2)
		ip="127.0.0.1";
	else
		ip=std::string(argv[1]);
    time_t ti=srv::NTP_Client::Instance(ip).GetCurrentTimestamp();
    std::cout<<ti<<std::endl;
    while(1)
    {
	sleep(1);
	ti=srv::NTP_Client::Instance(ip).GetCurrentTimestamp();
	std::cout<<ti<<std::endl;
    }
    return 0;
}
