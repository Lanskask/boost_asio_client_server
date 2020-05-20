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
    myfile.open(file_name, std::ios_base::app);
    myfile << msg + "\n";
    myfile.close();
}

string read_data(tcp::socket &socket) {
    boost::asio::streambuf buf;
    std::size_t num_of_readed_bytes = boost::asio::read_until(socket, buf, "\n");
    if (num_of_readed_bytes <= 0) {
        cerr << "num_of_readed_bytes<=0" << endl;
    }
    string data = boost::asio::buffer_cast<const char *>(buf.data());
    save_into_file(data);
    cout << data << endl;
    return data;
}

void send_message(tcp::socket &socket, const string &message) {
    const string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}

void signal_handling(boost::asio::io_service &io_service) {
    boost::asio::signal_set signals(io_service, SIGTERM, SIGHUP);
    signals.async_wait(
            boost::bind(&boost::asio::io_service::stop, &io_service));
}

int main(int argc, char *argv[]) {
    try {
//        const int host_port = check_command_line_arguments(argc, argv);
        const int host_port = 1234;

        boost::asio::io_service io_service;

        signal_handling(io_service);

        for (;;) {
            //listen for new connection
            tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), host_port));

            //socket creation
            tcp::socket socket_(io_service);

            //waiting for the connection
            acceptor_.accept(socket_);
            cout << "Waiting for the connection" << endl;

            //read operation
            string accepted_message = read_data(socket_);

            //write operation
            send_message(socket_, "The message was:\n\t" + accepted_message);
            cout << "Server sent message to Client!" << endl;
        }
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << "\n";
    }
    return EXIT_SUCCESS;
}