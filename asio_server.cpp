#include <iostream>
#include <fstream>
#include <csignal>
#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::cerr;
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
    // TODO: Need to debug
    if (false) {
        const std::string delimiter = "\r\n\r\n";
        boost::asio::write(socket, boost::asio::buffer("cmd1" + delimiter));


        // Read a single command from socket2.
        boost::asio::streambuf streambuf;
        boost::asio::async_read_until(socket, streambuf, delimiter,
                                      [delimiter, &streambuf](
                                              const boost::system::error_code &error_code,
                                              std::size_t bytes_transferred) {
                                          // Verify streambuf contains more data beyond the delimiter. (e.g.
                                          // async_read_until read beyond the delimiter)
                                          assert(streambuf.size() > bytes_transferred);

                                          // Extract up to the first delimiter.
                                          std::string command{
                                                  buffers_begin(streambuf.data()),
                                                  buffers_begin(streambuf.data()) + bytes_transferred
                                                  - delimiter.size()};

                                          // Consume through the first delimiter so that subsequent async_read_until
                                          // will not reiterate over the same data.
                                          streambuf.consume(bytes_transferred);

                                          assert(command == "cmd1");
                                          std::cout << "received command: " << command << "\n"
                                                    << "streambuf contains " << streambuf.size() << " bytes."
                                                    << std::endl;
                                      }
        );
    }

    //   ------ Need to debug

    boost::asio::streambuf buf;
    std::size_t num_of_readed_bytes = boost::asio::read_until(socket, buf, "\n");
    if (num_of_readed_bytes <= 0) {
        cerr << "num_of_readed_bytes<=0" << endl;
    }
    string data = boost::asio::buffer_cast<const char *>(buf.data());
    save_into_file(data);
    cout << data << endl;
}

void send_message(tcp::socket &socket, const string &message) {
    const string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}

// TODO: Change it or remove
int check_command_line_arguments(int argc, char *argv[]) {
    // Check command line arguments.
    int res;
    if (argc != 2) {
        std::cerr << "Usage: asio_server <port>\n";
        res = 1234; // default port
    } else {
        res = (int) *argv[2];
    }
}

void signal_handling(boost::asio::io_service &io_service) {
//    boost::asio::signal_set signals(io_service, SIGTERM, SIGHUP);
//    signals.async_wait(signal_handler);

    boost::asio::signal_set signals(io_service, SIGTERM, SIGHUP);
    signals.async_wait(
            boost::bind(&boost::asio::io_service::stop, &io_service));

//        signal(SIGTERM, simple_signal_handler);
//        signal(SIGHUP, simple_signal_handler);
}

int main(int argc, char *argv[]) {
    try {
//        const int host_port = check_command_line_arguments(argc, argv);
        const int host_port = 1234;

        boost::asio::io_service io_service;

        signal_handling(io_service);

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
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << "\n";
    }
    return 0;
}