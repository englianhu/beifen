/*

  ## ============== 一个简单的本地客户 ============== ##
  
  （一）包含一些必要的头文件并设置变量
  sudo apt install -y lib*curses*
  gcc 客户甲.c -o 客户甲 -lcurses
  gcc -I/usr/include/ncurses 客户甲.c -o 客户甲 -lncurses
  

*/

#include <curses.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int server_sockfd, client_sockfd;
	int server_len, client_len;
  struct sockaddr_un server_address;
  struct sockaddr_un client_address;
  
  /* （二）删除以前的套接字，为服务器创建一个为命名的套接字。 */
  unlink("server_socket");
  server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  
  /* （三）命名套接字 */
  server_address.sun_family = AF_UNIX;
  strcpy(server_address.sun_path, "server_socket");
  server_len = sizeof(server_address);
  bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
  
  /* （四）创建一个连接队列，开始等待客户进行连接。 */
  listen(server_sockfd, 5);
  while(1) {
    char ch;
    printf("服务器等待中！\n");
    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, 
                          (struct sockaddr *)&client_address, &client_len);
    
    /* （五）对client_sockfd套接字商的客户进行读写操作。 */
    read(client_sockfd, &ch, 1);
    ch++;
    write(client_sockfd, &ch, 1);
    close(client_sockfd);
  }
}










