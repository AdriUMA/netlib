if [ ! -d "bin" ]; then
    mkdir bin
fi

gcc -g client.c udp/sender.c udp/listener.c -o ./bin/client.out
./bin/client.out