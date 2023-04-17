if [ ! -d "bin" ]; then
    mkdir bin
fi

gcc -g server.c linkedlist/senderList.c udp/sender.c udp/listener.c -o ./bin/server.out
./bin/server.out