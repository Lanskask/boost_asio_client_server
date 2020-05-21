vagrant up
vagrant ssh

echo "Installing gcc"
sudo add-apt-repository -y ppa:deadsnakes/ppa
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -y
sudo apt-get install -y gcc-6
sudo apt-get install -y g++-6


echo "Installing conan"
sudo apt-get install -y python3.6
curl https://bootstrap.pypa.io/get-pip.py | sudo python3.6
sudo apt-get install -y python3-pip
python3.6 -m pip -V
sudo python3.6 -m pip install conan
conan --version
conan user


#-----------------------------
echo "Building"
mkdir build  && cd build

# If you are using GCC compiler >= 5.1,
conan profile new default --detect  # Generates default profile detecting GCC and sets old ABI
conan profile update settings.compiler.libcxx=libstdc++11 default  # Sets libcxx to C++11 ABI

conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .

echo "Running"
nohup ./bin/asio_server &
./bin/asio_client
cat message_log.txt



