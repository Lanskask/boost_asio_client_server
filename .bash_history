sudo install gcc-6
#sudo install gcc-6sudo apt-get install gcc-6
sudo apt-get install gcc-6
exit
ls
gcc --version
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-6
sudo apt-get update -y
sudo apt-get install -y gcc-6
echo "Installing conan"
sudo apt-get install -y python3.6
echo "Installing conan"
sudo apt-get install -y python3.6
curl https://bootstrap.pypa.io/get-pip.py | sudo python3.6
python3.6 -m pip -V
sudo python3.6 -m pip install conan
conan --version
conan user
sudo apt-get install -y python3-pip
#sudo apt-get install -y python3-pippython3.6 -m pip -V
python3.6 -m pip -V
sudo python3.6 -m pip install conan
conan user
echo "Building"
mkdir build  && cd build
# If you are using GCC compiler >= 5.1,
conan profile new default --detect  # Generates default profile detecting GCC and sets old ABI
conan profile update settings.compiler.libcxx=libstdc++11 default  # Sets libcxx to C++11 ABI
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
ls
rm -r build/
echo "Building"
mkdir build  && cd build
# If you are using GCC compiler >= 5.1,
conan profile new default --detect  # Generates default profile detecting GCC and sets old ABI
conan profile update settings.compiler.libcxx=libstdc++11 default  # Sets libcxx to C++11 ABI
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
conan install ..
ls
conan help install
cd ..
ls
ls
mkdir code
mv * code/
ls
cd code/
ls
cd build/
conan install ..
exit
