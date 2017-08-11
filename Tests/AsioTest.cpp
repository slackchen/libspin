//
// Created by Adrian on 2017/8/10.
//

#include "../Headers.h"
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service& io_service, tcp::endpoint& endpoint)
            : acceptor(io_service, endpoint), socket(io_service)
    {
        cout << "begin to accept at port: " << endpoint.port() << endl;

        DoAccept();
    }

    void DoAccept()
    {
        acceptor.async_accept(socket, [this](boost::system::error_code ec){

            if (!ec)
            {

            }

            DoAccept();
        });

    }

private:
    tcp::socket socket;
    tcp::acceptor acceptor;
};


int main() {

    boost::asio::io_service io_service;

    tcp::endpoint endpoint(tcp::v4(), 8888);

    vector<Server> servers;
    cout << servers.size() << "," << servers.capacity() << endl;
    servers.emplace_back(io_service, endpoint);


    cout << servers.size() << "," << servers.capacity() << endl;

    io_service.run();

    return 0;
}
