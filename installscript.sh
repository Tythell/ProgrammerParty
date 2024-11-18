sudo apt-get update
sudo apt-get install -y build-essential gdb
sudo apt install -y cmake
mkdir projects
cd projects
git clone https://github.com/Tythell/ProgrammerParty
echo Please enter your github username
read usrName
git config --global user.name $usrName

echo Please enter your email assosiated with your github commits
read usrEmail
git config --global user.email $usrEmail

echo Thank you. Your github globals are $usrName and $usrEmail

cd ProgrammerParty

cmake -S . -B build
cmake --build build

cd build && ctest