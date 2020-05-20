#include <iostream>
#include <string>
#include <tuple>
#include <boost/program_options.hpp>

using std::cout;
using std::endl;
using std::string;
using std::tuple;
namespace po = boost::program_options;

po::variables_map process_program_options(const int argc, const char *const argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "Show brief usage message");

    po::variables_map args;
    po::store(
            po::parse_command_line(argc, argv, desc),
            args
    );
    po::notify(args);
    return args;
}

tuple<string, int, string> server_options(const int argc, char *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("host_ip", po::value<string>()->default_value("127.0.0.1"), "host ip")
            ("host_port", po::value<int>()->default_value(1234), "host port")
            ("input_data_file", po::value<string>()->default_value("input_data_file.txt"), "input data file");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        EXIT_FAILURE;
    }

    tuple<string, int, string> res = std::make_tuple(
            vm["host_ip"].as<string>(),
            vm["host_port"].as<int>(),
            vm["input_data_file"].as<string>()
    );

    return res;
};

void run_test_func(string msg, char *test_argv[], int test_argc);

int main(int argc, char *argv[]) {
    char *test_argv[] = {
            "--host_ip", "127.0.0.ZERO_data",
            "--host_port", "1234000",
            "--input_data_file", "input_data_file_ZERO_data.txt"
    };
    char *test_argv2[] = {
            "--host_ip", "TWO_data",
            "--host_port", "1234222",
    };
    char *test_argv3[] = {
            "--host_port", "1234333",
    };
    int test_argc = 4;

//    run_test_func("First data:",test_argv, test_argc);
//    run_test_func("Second data:",test_argv2, test_argc);
    run_test_func("Third data:",test_argv3, test_argc);

//    tuple<string, int, string> options = server_options(argc, argv);

    return 0;
}

void run_test_func(string msg, char *this_test_argv[], int this_test_argc) {
    cout << msg << endl;
    tuple<string, int, string> options = server_options(this_test_argc, this_test_argv);
    cout
            << "host_ip: " << std::get<0>(options) << endl
            << "host_port: " << std::get<1>(options) << endl
            << "input_data_file: " << std::get<2>(options) << endl
            << endl;
}