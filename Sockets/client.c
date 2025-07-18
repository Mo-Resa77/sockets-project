#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MORESAMAX 100
#define MORESAPORT 7777

int main() {
    int moresa_sock;
    struct sockaddr_in moresa_server;

    moresa_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (moresa_sock == -1) {
        perror("Socket error");
        return 1;
    }
    printf("Moresa socket ready\n");

    moresa_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    moresa_server.sin_family = AF_INET;
    moresa_server.sin_port = htons(MORESAPORT);

    if (connect(moresa_sock, (struct sockaddr *)&moresa_server, sizeof(moresa_server)) < 0) {
        perror("Connect error");
        return 1;
    }
    printf("Moresa connected\n");

    while (1) {
        int moresa_choice;
        char moresa_input[MORESAMAX];

        printf("1 for check, 2 for flip: ");
        scanf("%d", &moresa_choice);
        printf("Enter string: ");
        scanf("%s", moresa_input);

        if (write(moresa_sock, &moresa_choice, sizeof(int)) < 0)
            break;

        int moresa_len = strlen(moresa_input);
        if (write(moresa_sock, &moresa_len, sizeof(int)) < 0)
            break;

        if (write(moresa_sock, moresa_input, moresa_len) < 0)
            break;

        if (moresa_choice == 1) {
            int moresa_result;
            read(moresa_sock, &moresa_result, sizeof(int));
            printf("Check result: %s\n", moresa_result ? "Yes" : "No");
        } else if (moresa_choice == 2) {
            char moresa_output[MORESAMAX];
            read(moresa_sock, moresa_output, MORESAMAX);
            printf("Flipped: %s\n", moresa_output);
        }
    }

    close(moresa_sock);
    return 0;
}