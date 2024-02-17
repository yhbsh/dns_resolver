#include <arpa/inet.h>
#include <err.h>
#include <netdb.h> // For getaddrinfo function
#include <stdio.h> // For printf and fprintf functions
#include <stdlib.h>
#include <string.h>     // For memset function
#include <sys/socket.h> // For socket functions
#include <sys/types.h>  // For data types
#include <unistd.h>     // For close function

void usage(const char *program) {
    printf("Usage: %s hostname\n", program);
    printf("Example: %s google.com\n", program);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }

    const char *hostname = argv[1];
    const char *servname = "http";

    struct addrinfo *result;
    int status = getaddrinfo(hostname, servname, NULL, &result);
    if (status != 0) {
        fprintf(stderr, "Error resolving hostname \"%s\": %s\n", argv[1], gai_strerror(status));
        return EXIT_FAILURE;
    }

    if (result == NULL) {
        printf("The hostname \"%s\" is syntactically valid but does not have an IP address.\n", argv[1]);
        return EXIT_SUCCESS;
    }

    printf("IP addresses for %s:\n\n", hostname);

    struct addrinfo *p;
    for (p = result; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        // Get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (result->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)result->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // Convert the IP to a string and print it:
        char ip[INET6_ADDRSTRLEN];
        inet_ntop(result->ai_family, addr, ip, sizeof(ip));
        printf("  %s: %s\n", ipver, ip);
    }

    freeaddrinfo(result); // Free the linked list

    return 0;
}
