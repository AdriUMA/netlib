# Chat Application using Netlib

## Ports
| Port    | Type       | From     | To       |
| ------- | ---------- | -------- | -------- |
| 55154   | Listener   | Server   | ✗       |
| 55155   | Sender     | Server   | Client   |
| 55155   | Listener   | Client   | ✗       |
| 55154   | Sender     | Client   | Server   |

## Compile and Run

Server

```bash
chmod u+x compilers/server.sh
./compilers/server.sh
```

Client

```bash
chmod u+x compilers/client.sh
./compilers/client.sh
```
