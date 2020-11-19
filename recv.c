#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[]) {
int socd;
struct sockaddr_in server;
char *message;
char server_reply[2000];

//CREATE SOCKET
socd = socket(AF_INET, SOCK_STREAM, 0);
if(socd == -1) {
printf("Could not create socket");
}

server.sin_addr.s_addr = inet_addr("192.168.208.9"); 
//PLEASE ENTER THE IP ADDRESS OF YOUR SERVER VM
server.sin_family = AF_INET;
server.sin_port =  htons(22);

//CONNECT TO REMOVE SERVER
if(connect(socd, (struct sockaddr *)&server, sizeof(server))<0) {
puts("connect error");
return 1;
}

puts("Connected");

//SEND SOME DATA
message = "connect";

if( send(socd, message, strlen(message), 0)<0) {
puts("Send failed");
return 1;
}

puts("Data Sent\n");

//RECEIVE A REPLY FROM THE SERVER
if(recv(socd, server_reply, 2000, 0)<0) {
puts("Receive failed");

close(socd);
return 1;
}

puts("Receive Data");

return 0;
}
