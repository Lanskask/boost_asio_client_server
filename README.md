# C++ Client Server with Boost.Asio

Based on [socket-programming-in-cpp-using-boost-asio-tcp-server-and-client](https://www.c-sharpcorner.com/article/socket-programming-in-cpp-using-boost-asio-tcp-server-and-client/) 
and code from Boost documentation and StackOverflow of cource :)

To build this client-server I used [conan.io](https://docs.conan.io/en/latest/getting_started.html)

Excuse me that without tests and `-Wall -Wextra -pedantic` flags.

I'm not sure that copying of `example_input_file.txt` via *cmake* works, becouse of this put 
`example_input_file.txt` file near bin file.
 
## How to build and run
General instruction written in `run_all.sh` file 

It isn't correct. 
DON"T RUN IT!!!
```shell script
sh run_all.sh
```

## How to use Programming options
```shell script
./asio_client --host_ip "127.0.0.1" --host_port 1234 --input_data_file "example_input_file.txt"
```

## TODO
- [x] ~~correct signal handling. Hope that asio error hanling closes all it's stuff itself~~ 
- [ ] On client read message from file
- [ ] Check how to pipe data from file into client and does it necesasry
- [ ] Just tell client `<host_url> <host_port> <input_data_file_name>`