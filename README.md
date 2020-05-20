# C++ Client Server with Boost.Asio

Based on [socket-programming-in-cpp-using-boost-asio-tcp-server-and-client](https://www.c-sharpcorner.com/article/socket-programming-in-cpp-using-boost-asio-tcp-server-and-client/)

To build this client-server I used [conan.io](https://docs.conan.io/en/latest/getting_started.html)
  
## How to build and run
Instruction written in `run_all.sh` file 

```shell script
sh run_all.sh
```

## Notes

Initially to handle signals I used

```shell script
void signal_handler(const boost::system::error_code &error, int signal_number) {
    cout << "t least it was here" << endl;
    if (!error) {
        cout << "It's a signal occurred! Sig number: " << signal_number << endl;
    } else {
        cout << "It's a error: " << error.message() << endl;
    }
}

boost::asio::signal_set signals(io_service, SIGTERM, SIGHUP);
signals.async_wait(signal_handler);
```
But it doesn't work as I checked it.