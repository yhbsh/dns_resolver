# A simple dns resolver in pure c

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
