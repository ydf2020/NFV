#include "client.h"

Client::Client(){
	client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	report_error(client_socket);
	server_address = allocate_str_mem(INET_ADDRSTRLEN);
	signal(SIGPIPE, SIG_IGN);			
	//status = 0;
	//setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&g_timeout, sizeof(timeval));
}

void Client::fill_server_details(int server_port, const char *server_address){
	this->server_port = server_port;
	strcpy(this->server_address, server_address);
	bzero((char*)&server_sock_addr, sizeof(server_sock_addr));
	server_sock_addr.sin_family = AF_INET;
	server_sock_addr.sin_port = htons(server_port);
	status = inet_aton(server_address, &server_sock_addr.sin_addr);
	if(status == 0){
		cout<<"ERROR: Invalid IP address"<<endl;
		exit(EXIT_FAILURE);
	}
}

void Client::connect_with_server(int client_num){
	int new_server_port;
	char *new_server_address = allocate_str_mem(INET_ADDRSTRLEN);
	pkt.fill_data(0, sizeof(int), client_num);
	write_data(pkt.data, pkt.data_len);
	read_data(pkt.data, BUFFER_SIZE);
	memcpy(&new_server_port, pkt.data, sizeof(int));
	memcpy(new_server_address, pkt.data+sizeof(int), strlen((const char*)pkt.data)-sizeof(int));
	fill_server_details(new_server_port, new_server_address);
	cout<<"Client side: Client-"<<client_num<<" connected with server"<<endl;	
}

void Client::read_data(char *data, int len){
	status = recvfrom(client_socket, data, len, 0, (sockaddr*)&server_sock_addr, &g_addr_len);
	check_conn(status);
	report_error(status);
}

void Client::write_data(const char *data, int len){
	status = sendto(client_socket, data, len, 0, (sockaddr*)&server_sock_addr, g_addr_len);
	report_error(status);
}

Client::~Client(){
	free(server_address);
	close(client_socket);
}