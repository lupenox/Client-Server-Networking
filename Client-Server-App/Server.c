#include "Server.h"

// Helper method decrypts the message using the Caesar Cipher with the key generated earlier
void decryptMessage(char *message, int key) {

    for (int i = 0; message[i] != '\0'; ++i) {

        if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = (message[i] - 'A' - key + 26) % 26 + 'A';
        } 
        
        else if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = (message[i] - 'a' - key + 26) % 26 + 'a';
        }
    }
}

void handleClient(int clientSocket, int clientCount) {

    char buffer[BUFFER_SIZE];
    int key;

    // Read greeting message
    if (read(clientSocket, buffer, BUFFER_SIZE) == -1) {
        perror("Read failed");
        close(clientSocket);
    }

    printf("Client is connecting... %d\n", clientCount);
    printf("%s\n", buffer);

    //rand returns a random number between 1 and 25 for the encryption key
    int seedValue = 123;
    srand(seedValue);
    key = rand() % 25 + 1;
    
    if (write(clientSocket, &key, sizeof(key)) == -1) {
        perror("write failed");
        close(clientSocket);
    }

    while (1) {
        int byteCount = read(clientSocket, buffer, BUFFER_SIZE);
        buffer[byteCount] = '\0';

        if (strcmp(buffer, "quit") == 0) {
            printf("Goodbye.");
            break;
        }

        decryptMessage(buffer, key);
        
        if (write(clientSocket, buffer, strlen(buffer)) == -1) {
            perror("Write failed");
            break;
        }

    }

    close(clientSocket);
}

int main() {

    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientCount = 0;

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        return -1;
    }

    //setup for network address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Bind failed");
        close(serverSocket);
        return -1;
    }

    // llisten for connections 
    //there can only be a max of 5
    if (listen(serverSocket, 5) == -1) {
        perror("Listen failed");
        close(serverSocket);
        return -1;
    }

    printf("Server is running\n");

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

        if (clientSocket == -1) {
            perror("Accept failed");
            //skip to next iteration if accept failed
            continue;
        }

        ++clientCount;

        // Child process
        if (fork() == 0) {
            close(serverSocket);
            handleClient(clientSocket, clientCount);
        } 
        
        // Parent process
        else { 
            close(clientSocket);
        }

    }

    close(serverSocket);
    return 0;
}
