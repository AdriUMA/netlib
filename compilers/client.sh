if [ ! -d "bin" ]; then
    mkdir bin
fi

gcc client.c udp/listener.c udp/sender.c -o ./bin/client.out
./bin/client.out