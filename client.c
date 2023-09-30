//CLIENT
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
 
#define SERV_PORT 6000
#define MAXLEN 512
 
int main(int argc,char *argv[]){
char sendline[MAXLEN];
char recvline[MAXLEN];
 
int sockfd;
struct sockaddr_in servaddr;
socklen_t len;
if(argc!=2)printf("usage tcpcli <ipaddress>\n");
sockfd=socket(AF_INET,SOCK_STREAM,0);
 
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[1]);
servaddr.sin_port=htons(SERV_PORT);
 
if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)perror("Error");
 
puts("Enter the Sendline");
fgets(sendline,MAXLEN,stdin);
int n=strlen(sendline);
write(sockfd,sendline,n);
n=read(sockfd,recvline,MAXLEN);
if(n<0)puts("Error Reading");
recvline[n]=0;
fputs(recvline,stdout);
exit(0);
return 0;
}