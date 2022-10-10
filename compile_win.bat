rm -rf build
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build .
cp ./Debug/RarBrutForce.exe ../