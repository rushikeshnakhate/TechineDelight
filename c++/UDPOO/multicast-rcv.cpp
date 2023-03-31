// Guidance:  https://www.tenouk.com/Module41c.html
#include <arpa/inet.h>
#include <array>
#include <iostream>
#include <netinet/in.h>
#include "udpSock.hpp"
#include "zz_diagnose.hpp"

int main() {
    UdpSock sock;
    diagnose(sock.isGood(), "Opening datagram socket for receive");

    {
        // enable SO_REUSEADDR to allow multiple instances of this application to
        //    receive copies of the multicast datagrams.
        int reuse = 1;
        diagnose(setsockopt(sock(), SOL_SOCKET, SO_REUSEADDR, (char *) &reuse,
                            sizeof(reuse)) >= 0, "Setting SO_REUSEADDR");
    }

    // Bind to the proper port number with the IP address specified as INADDR_ANY
    sockaddr_in localSock = {};    // initialize to all zeroes
    localSock.sin_family = AF_INET;
    localSock.sin_port = htons(4321);
    localSock.sin_addr.s_addr = INADDR_ANY;
    // Note from manpage that bind returns 0 on success
    diagnose(!bind(sock(), (sockaddr *) &localSock, sizeof(localSock)),
             "Binding datagram socket");

    // Join the multicast group on the local interface.  Note that this
    //    IP_ADD_MEMBERSHIP option must be called for each local interface over
    //    which the multicast datagrams are to be received.
    ip_mreq group = {};    // initialize to all zeroes
    group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
    group.imr_interface.s_addr = inet_addr("127.0.0.1");
    diagnose(setsockopt(sock(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &group,
                        sizeof(group)) >= 0, "Adding multicast group");

    // Read from the socket
    std::array<char, 1024> arr;
    arr.fill(0);
    diagnose(read(sock(), arr.data(), arr.size()) >= 0,
             "Reading datagram message");
    std::cout << "Message from multicast sender: " << arr.data()
              << std::endl;
    return 0;
}
