# A simple dns resolver in pure c for educational purposes

# Demo

https://github.com/HoussemBousmaha/dns_resolver/assets/86262467/adf17344-0e0f-4db0-bbcf-b76d70d1dc31

# Features
- input: example.com
- output: (List of ip addresses IPV4 & IPV6 of example.com)
	93.184.216.34
	93.184.216.34

# Build
```console
$ mkdir -p build && cd build && cmake .. && make
```

# How to understand the code
- I highly suggest you read manpages of the following functions:
    - getaddrinfo
    - inet_ntop
```console
$ man getaddrinfo
```
```console
$ man inet_ntop
```
