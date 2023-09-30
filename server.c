// Headers
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<netinet/tcp.h>
 
// Codes Start Here
#define SERV_PORT 6000
#define MAXLEN 512
int main(int argc,char**argv){
char buff1[MAXLEN];
struct sockaddr_in servaddr,cliaddr;
int servfd,clifd;
socklen_t clilen;
servfd=socket(AF_INET,SOCK_STREAM,0);
 
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(SERV_PORT);
 
if(bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
perror("Error binding socket");
exit(1);
}
 
if(listen(servfd,5)<0) {
perror("Error listening on socket");
exit(1);
}
while(1){
// puts("Listening.....");
clilen=sizeof(cliaddr);
clifd=accept(servfd,(struct sockaddr*)&cliaddr,&clilen);
if (clifd < 0) {
perror("Error accepting connection");
exit(1);
}
if(fork()==0){
printf("CHILD PID %d\n",getpid());
close(servfd);
int n=read(clifd,buff1,MAXLEN);
puts("Message from client");
puts(buff1);
if (n < 0) {
perror("Error reading from socket");
exit(1);
}
if (n == 0) {
// Client closed the connection
break;
}
n=write(clifd,buff1,50);
if (n < 0) {
perror("Error writing to socket");
exit(1);
}
close(clifd);
exit(0);
}
close(clifd);
}
return 0;
}
//TCP SERVER