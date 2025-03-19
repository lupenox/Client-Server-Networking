/* Author: Logan Lapierre
*  Date: 8/4/2024
*  
*  Description: This program uses a client and server to encrypt and decrypt
*  Messages entered in through the command line. The key, encrypted, and decrypted 
*  messages will be printed out into the console if succesful.
*/

#include "Client.h"

// Helper Method for Encrypting the message using the Caesar Cipher
void encryptMessage(char *message, int key) {
    //as long as you dont reach a null char the loop will continue
    for (int i = 0; message[i] != '\0'; ++i) {

        //encrypting uppercase
        if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = (message[i] - 'A' + key) % 26 + 'A';
        } 
        
        //encrypting lowercase
        else if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = (message[i] - 'a' + key) % 26 + 'a';
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    int key;

    // if socket creation failes print an error
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        return -1;
    }

    //setup for the network address
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server if it failes to connect print an error
    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("Connection failed");
        close(sockfd);
        return -1;
    }

    // Send greeting and get the key
    strcpy(buffer, "Greetings from the client");
    write(sockfd, buffer, strlen(buffer));

    //if read failes return -1
    if (read(sockfd, &key, sizeof(key)) == -1) {
        perror("read failed");
        close(sockfd);
        return -1;
    }

    //prints the key that was generated from srand
    printf("Key from server: %d\n", key);

    //loop continues untill the user enters quit
    while (1) {
        printf("Enter message, enter quit to exit: ");
        //get input from command line
        fgets(buffer, BUFFER_SIZE, stdin);
        // Remove trailing newline with strcspn
        buffer[strcspn(buffer, "\n")] = '\0';  

        if (strcmp(buffer, "quit") == 0) {
            send(sockfd, buffer, strlen(buffer), 0);
            break;
        }

        //encrypt the message then print to console
        encryptMessage(buffer, key);
        printf("Encrypted Message: %s\n", buffer);

        write(sockfd, buffer, strlen(buffer));
        read(sockfd, buffer, BUFFER_SIZE);
        printf("Server response: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
