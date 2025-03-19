# Client-Server Networking Application

## Overview
This project is a **client-server networking application** written in **C**, designed to demonstrate inter-process communication (IPC) using **sockets**. The client and server communicate over a network, exchanging messages based on a simple protocol.

## Features
- **Uses TCP sockets** for reliable communication.
- **Client and server architecture** for bidirectional message exchange.
- **Makefiles included** for easy compilation.
- **Error handling** to manage connection issues.
- **Modular structure** with separate header files.

## How It Works
### **Architecture**
1. **Server** listens for incoming connections on a specified port.
2. **Client** connects to the server and sends messages.
3. **Server processes requests** and sends responses.
4. **Communication continues** until termination conditions are met.

### **Setup & Usage**
#### **Prerequisites**
- **GCC compiler** (for Linux/macOS: `sudo apt install gcc` | for Windows: use MinGW)
- **Make utility** (for Linux/macOS: `sudo apt install make`)

#### **Compiling the Application**
To build both the client and server, run:
```bash
make -f Makefile_Client
make -f Makefile_server
```

#### **Running the Server**
```bash
./server <port>
```
Example:
```bash
./server 8080
```

#### **Running the Client**
```bash
./client <server_ip> <port>
```
Example:
```bash
./client 127.0.0.1 8080
```

## Why This Project?
- Demonstrates **network programming fundamentals** in C.
- Useful for learning **socket programming, inter-process communication (IPC), and client-server architecture**.
- Provides a **strong foundation for cybersecurity, penetration testing, and system programming.**

## Future Enhancements
- Implement **UDP support** alongside TCP.
- Add **encryption** for secure communication.
- Introduce **multi-threading** for handling multiple clients.

## Author
**Logan Lapierre**  
[GitHub](https://github.com/lupenox) | [LinkedIn](https://linkedin.com/in/logan-lapierre)

## License
MIT License - Free to use and modify.
