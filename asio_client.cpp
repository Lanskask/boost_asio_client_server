#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

const string &read_file(const string &file_name) {
    std::ifstream ifs(file_name);

    std::string content;
    content.assign(
            std::istreambuf_iterator<char>(ifs),
            std::istreambuf_iterator<char>()
    );
    return content;
}

void send_msg(const string &msg, tcp::socket &socket) {
    boost::system::error_code error;
    boost::asio::write(socket, buffer(msg), error);
    if (!error) {
        cout << "Client sent hello message!" << endl;
    } else {
        cout << "send failed: " << error.message() << endl;
    }
}

void receive_msg(tcp::socket &socket) {
    boost::system::error_code error;
    // getting a response from the server
    streambuf receive_buffer;
    read(socket, receive_buffer, transfer_all(), error);
    if (error && error != error::eof) {
        cout << "receive failed: " << error.message() << endl;
    } else {
        const char *data = buffer_cast<const char *>(receive_buffer.data());
        cout << data << endl;
    }
}

int check_command_line_arguments(int argc, char *argv[]) {
    // Check command line arguments.
    if (argc != 4) {
        std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
        std::cerr << "  For IPv4, try:\n";
        std::cerr << "    receiver 0.0.0.0 80 .\n";
        std::cerr << "  For IPv6, try:\n";
        std::cerr << "    receiver 0::0 80 .\n";
    }
}

int main(int argc, char *argv[]) {
    const string host_ip_addr = "127.0.0.1";
    const int host_port = 1234;
    const string msg = "Hello from Client!\n";
    const string file_name = argv[1];

    check_command_line_arguments(argc, argv);


    boost::asio::io_service io_service;

    //socket creation
    tcp::socket socket(io_service);

    //connection
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(host_ip_addr), host_port));

    // request/message from client
    send_msg(msg, socket);

    receive_msg(socket);

    return EXIT_SUCCESS;
}