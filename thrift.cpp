// g++ -g -Wall -I./ -I/usr/local/include/thrift Serv.cpp rtm_types.cpp rtm_constants.cpp thrift.cpp  -lthrift

#include "Serv.h"
#include <unistd.h>
#include <iostream>
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using boost::shared_ptr;

// argv[1]: projectId
// argv[2]: uid
// argv[3]: rtmToken
// argv[4]: groupId
// argv[5]: msg

int main(int argc, char **argv) {
    boost::shared_ptr <TSocket> socket(new TSocket("52.220.29.186", 13021));
    boost::shared_ptr <TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr <TProtocol> protocol(new TBinaryProtocol(transport));

    while (1) {
        try
        {
            transport->open();
            ServClient client(protocol);

            int32_t pid = atoll(argv[1]);
            int64_t uid = atoll(argv[2]);
            std::string token = argv[3];
            std::string version = "1.0";
            bool authed;
            authed = client.auth(pid, uid, token, version);
            std::cout << authed << std::endl;

            int64_t group_id = atoll(argv[4]);
            int64_t mid = time(NULL) * 10000000;
            int mtype = 61;

            mid++;
            std::string message = argv[5];
            client.send_broadcast_group_msg(group_id, mid, mtype, message);

            transport->close();
        } catch(...) {
        }

        sleep(1);
    }

    return 0;
}
