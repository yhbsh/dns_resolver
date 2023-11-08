#include <arpa/inet.h>
#include <err.h>
#include <netdb.h>      // For getaddrinfo function
#include <stdio.h>      // For printf and fprintf functions
#include <string.h>     // For memset function
#include <sys/socket.h> // For socket functions
#include <sys/types.h>  // For data types
#include <unistd.h>     // For close function

void usage() {
  printf("Usage: ./dns_resolver hostname\n");
  printf("Example: ./dns_resolver google.com\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage();
    return 0;
  }

  const char *hostname = argv[1];
  const char *servname = "http";

  struct addrinfo *result;
  int status;
  if ((status = getaddrinfo(hostname, servname, NULL, &result) < 0)) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    return 1;
  };

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
