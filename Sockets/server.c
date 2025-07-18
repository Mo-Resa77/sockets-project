#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MORESAMAX 100
#define MORESAPORT 7777

int moresa_check(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
        if (str[i] != str[len - 1 - i])
            return 0;
    return 1;
}

void moresa_flip(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main() {
    int moresa_sock, moresa_client, moresa_size;
    struct sockaddr_in moresa_server, moresa_clientaddr;

    moresa_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (moresa_sock == -1) {
        perror("Socket error");
        return 1;
    }
    printf("Moresa socket ready\n");

    moresa_server.sin_family = AF_INET;
    moresa_server.sin_addr.s_addr = INADDR_ANY;
    moresa_server.sin_port = htons(MORESAPORT);

    if (bind(moresa_sock, (struct sockaddr *)&moresa_server, sizeof(moresa_server)) < 0) {
        perror("Bind error");
        return 1;
    }
    printf("Moresa bind complete\n");

    listen(moresa_sock, 3);
    printf("Moresa awaiting connections...\n");
    moresa_size = sizeof(struct sockaddr_in);

    moresa_client = accept(moresa_sock, (struct sockaddr *)&moresa_clientaddr, (socklen_t*)&moresa_size);
    if (moresa_client < 0) {
        perror("Accept error");
        return 1;
    }
    printf("Moresa connection established\n");

    while (1) {
        int moresa_choice, moresa_len;
        char moresa_input[MORESAMAX];

        if (read(moresa_client, &moresa_choice, sizeof(int)) <= 0)
            break;

        if (read(moresa_client, &moresa_len, sizeof(int)) <= 0)
            break;

        if (read(moresa_client, moresa_input, moresa_len) <= 0)
            break;
        moresa_input[moresa_len] = '\0';

        printf("Choice: %d, Input: %s\n", moresa_choice, moresa_input);

        if (moresa_choice == 1) {
            int moresa_result = moresa_check(moresa_input);
            write(moresa_client, &moresa_result, sizeof(int));
        } else if (moresa_choice == 2) {
            moresa_flip(moresa_input);
            write(moresa_client, moresa_input, strlen(moresa_input) + 1);
        }
    }

    close(moresa_client);
    close(moresa_sock);
    return 0;
}