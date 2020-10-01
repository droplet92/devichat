echo "killall -9 devichat_server"
killall -9 devichat_server
cd server
rm -rf devichat_server
make
make clean
echo "./devichat_server $1 >> chatlog 2>&1 &"
echo "===================================" >> chatlog
echo "server restarts a" >> chatlog
date >> chatlog
echo "===================================" >> chatlog
./devichat_server $1 >> chatlog 2>&1 &
