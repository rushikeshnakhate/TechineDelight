#include <arpa/inet.h>
#include "udpSock.hpp"
#include "zz_diagnose.hpp"

#define INVALID_FD -1
#define UNDEFINED -1
#define FAILURE    1
#define SUCCESS    0


class MultiCastSend {
public:
    bool IntializeMulticastSender(const u_short &ushSendingPortNo,
                                  const std::string &sSendingMulticastGroupAddress);

    bool SendMulticastData(std::string databuf);

private :
    UdpSock sock;
    sockaddr_in groupSock = {};   // init to all zeroes
    in_addr localIface = {};   // init to all zeroes

    ushort m_ushSendingPortNo;
    std::string m_sSendingMulticastGroupAddress;
    bool m_bMulticastSenderInitialized;
    int m_sender_fd;
};


bool MultiCastSend::IntializeMulticastSender(const u_short &ushSendingPortNo,
                                             const std::string &sSendingMulticastGroupAddress) {
    int iReturn = UNDEFINED;
    try {
        diagnose(sock.isGood(), "Opening datagram socket for send");
        groupSock.sin_family = AF_INET;
        groupSock.sin_addr.s_addr = inet_addr(sSendingMulticastGroupAddress.c_str());
        groupSock.sin_port = htons(ushSendingPortNo);
        localIface.s_addr = inet_addr("127.0.0.1");
        diagnose(setsockopt(sock(), IPPROTO_IP, IP_MULTICAST_IF, (char *) &localIface, sizeof(localIface)) >= 0,
                 "Setting local interface");
    }
    catch (std::exception &e) {
        std::cerr << e.what() << " Exception in function " << __FUNCTION__ << std::endl;
        m_bMulticastSenderInitialized = false;
        if (m_sender_fd != (INVALID_FD)) {
            close(m_sender_fd);
        }
        iReturn = FAILURE;
    }
    return iReturn;
}


bool MultiCastSend::SendMulticastData(std::string databuf) {
    bool iReturn = UNDEFINED;
    try {
        if (m_bMulticastSenderInitialized) {
            diagnose(sendto(sock(), databuf.c_str(), databuf.length(), 0,
                            (sockaddr *) &groupSock, sizeof(groupSock)) >= 0,
                     "Sending datagram message");
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << " Exception in function " << __FUNCTION__ << std::endl;
        iReturn = FAILURE;
    }
    return iReturn;
}

int main() {
    MultiCastSend multiCastSend;
    multiCastSend.IntializeMulticastSender(4321, "226.1.1.1");
    multiCastSend.SendMulticastData("sending data Rushikesh");
    return 0;
}
