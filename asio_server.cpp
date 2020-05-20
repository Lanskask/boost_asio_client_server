#include <iostream>
#include <fstream>
#include <csignal>
#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

void simple_signal_handler(const int signum) {
    cout << "Interrupt signal (" << signum << ") received.\n";

    exit(signum);
}

void save_into_file(const string &msg) {
    const string file_name = "message_log.txt";
    std::ofstream myfile;
    myfile.open(file_name);
    myfile << msg + "\n";
    myfile.close();
}

void read_data(tcp::socket &socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    string data = boost::asio::buffer_cast<const char *>(buf.data());
    save_into_file(data);
    cout << data << endl;
}

void send_message(tcp::socket &socket, const string &message) {
    const string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}

int main() {
    const int host_port = 1234;

    boost::asio::io_service io_service;
//    boost::asio::signal_set signals(io_service, SIGTERM, SIGHUP);
//    signals.async_wait(signal_handler);

    signal(SIGTERM, simple_signal_handler);
    signal(SIGHUP, simple_signal_handler);

    //listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), host_port));

    //socket creation
    tcp::socket socket_(io_service);

    //waiting for the connection
    acceptor_.accept(socket_);

    //read operation
    read_data(socket_);

    //write operation
    send_message(socket_, "Hello From Server!");
    cout << "Server sent Hello message to Client!" << endl;
    return 0;
}  