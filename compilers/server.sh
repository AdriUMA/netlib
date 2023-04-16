if [ ! -d "bin" ]; then
    mkdir bin
fi

gcc server.c udp/listener.c udp/sender.c linkedlist/addressList.c -o ./bin/server.out
./bin/server.out