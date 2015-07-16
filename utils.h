#ifndef UTILS_H
#define UTILS_H

//(C++) Operations: Input/Output
#include <iostream>

//(C++) STL Operations: String, Vector, String stream
#include <string>
#include <vector>
#include <sstream>

//(C) Operations: Input/Output, String, Standard libraries(like atoi, malloc)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//(C) Operations: Socket programming
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>

//(C) Operations: Multithreading
#include <pthread.h>

using namespace std;

#define MAX_CONNECTIONS 10000
#define UE_COUNT 10
#define BUFFER_SIZE 1024

extern int g_mme_port;
extern int g_hss_port;
extern const char *g_mme_address;
extern const char *g_hss_address;
extern socklen_t g_addr_len;
extern timeval g_timeout;
extern long long g_stack_buf;

struct ClientDetails{
	int num;
	struct sockaddr_in client_sock_addr;
};

void check_conn(int&);
void report_error(int);
void report_error(int, const char*);
void print(string);
void print(int);
void print(string, int);
void print_message(string);
void print_message(string, int);
void print_message(string, unsigned long long);
const char* to_char_array(unsigned long long);
char* allocate_str_mem(int);
uint8_t* allocate_uint8_mem(int);

#endif //UTILS_H