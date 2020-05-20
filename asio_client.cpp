#include <iostream>
#include <fstream>
#include <tuple>
#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/program_options.hpp>

using std::string;
using std::tuple;
using std::cout;
using std::endl;
using namespace boost::asio;
using ip::tcp;
namespace po = boost::program_options;

tuple<string, int, string> server_options(const int argc, char *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("host_ip", po::value<string>()->default_value("127.0.0.1"), "host ip")
            ("host_port", po::value<int>()->default_value(1234), "host port")
            ("input_data_file", po::value<string>()->default_value("example_input_file.txt"), "input data file");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        exit(EXIT_SUCCESS);
    }

    tuple<string, int, string> res = std::make_tuple(
            vm["host_ip"].as<string>(),
            vm["host_port"].as<int>(),
            vm["input_data_file"].as<string>()
    );

    return res;
};

const string read_file(const string &file_name) {
    std::ifstream ifs(file_name);
    if(!ifs.is_open()) {
        std::cerr << "File " << file_name <<  " isn't opened!" << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "File is opened!" << endl;
    }
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

std::tuple<string, int, string> check_command_line_arguments(int argc, char *argv[]) {
    // Check command line arguments.
    std::tuple<string, int, string> res;
    if (argc != 4) {
        std::cerr << "Usage: \n\tasio_client <host_url> <host_port> <input_data_file_name>\n";
        // set defaults
        res = std::make_tuple("127.0.0.1", 1234, "example_input_file.txt");
    } else {
        res = std::make_tuple(*argv[1], (int)*argv[2], *argv[3]);
    }
    return res;
}

int main(int argc, char *argv[]) {
    string host_ip_addr = "";
    int host_port = 0;
    string file_name = "";
    std::tie(host_ip_addr, host_port, file_name) = server_options(argc, argv);

    const string msg = read_file(file_name) + '\n';
//    cout << "msg: " << msg << "after msg" << endl;

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