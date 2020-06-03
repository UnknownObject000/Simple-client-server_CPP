#include "NTP_Client.h"

using namespace srv;

NTP_Client::NTP_Client(std::string ipaddr,int port)
{
	if(port<=0||port>65534)
	{
		std::cerr<<"Invalid UDP Port!"<<std::endl;
		return;
	}
	ntpServerEP = udp::endpoint(boost::asio::ip::address::from_string(ipaddr.c_str()), port);
    	n_io_service service;
    	//udp\ntp client config
    	uSocket = new udp::socket(service);
    	try
    	{
    	    uSocket->open(udp::v4());
    	    std::cout << "<UDP Client started>\n";
    	}
    	catch (const std::exception &e)
    	{
    	    std::cerr << "Cannot start UDP client:\n"
    	              << e.what() << '\n';
    	}
}

NTP_Client::NTP_Client(std::string ipaddr)
{
    ntpServerEP = udp::endpoint(boost::asio::ip::address::from_string(ipaddr.c_str()), 123);
    n_io_service service;
    //udp\ntp client config
    uSocket = new udp::socket(service);
    try
    {
        uSocket->open(udp::v4());
        std::cout << "<UDP Client started>\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Cannot start UDP client:\n"
                  << e.what() << '\n';
    }
}

NTP_Client::NTP_Client()
{
    ntpServerEP = udp::endpoint(boost::asio::ip::address::from_string("88.147.254.235"), 123);
    n_io_service service;
    //udp\ntp client config
    uSocket = new udp::socket(service);
    try
    {
        uSocket->open(udp::v4());
        std::cout << "<UDP Client started>\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Cannot start UDP client:\n"
                  << e.what() << '\n';
    }
}

NTP_Client &NTP_Client::Instance()
{
    static NTP_Client ntpc;
    return ntpc;
}

NTP_Client &NTP_Client::Instance(std::string ipaddr)
{
	static NTP_Client ntpc(ipaddr);
	return ntpc;
}

NTP_Client &NTP_Client::Instance(std::string ipaddr,int port)
{
	static NTP_Client ntpc(ipaddr,port);
	return ntpc;
}

time_t NTP_Client::GetCurrentTimestamp()
{
    //Мог и shared_ptr создать, но контекста для него нет.
    ntp_packet *packet = new ntp_packet();

    uSocket->send_to(boost::asio::buffer(packet, 48), ntpServerEP);

    udp::endpoint ntpAnswerEndPoint;
    uSocket->receive_from(boost::asio::buffer(packet, 48), ntpAnswerEndPoint);

    time_t timestamp = (ntohl(packet->txTm_s) - NTP_TIMESTAMP_DELTA);

    delete packet;
    return timestamp; // Time-stamp seconds.
}
