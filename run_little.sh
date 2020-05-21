echo "Building"
mkdir build  && cd build

# If you are using GCC compiler >= 5.1,
#conan profile new default --detect  # Generates default profile detecting GCC and sets old ABI
conan profile update settings.compiler.libcxx=libstdc++11 default  # Sets libcxx to C++11 ABI

conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .

echo "Running"

./bin/asio_server
#./bin/asio_client



