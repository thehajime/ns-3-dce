#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>

#define SERVER_PORT 2000

int main (int argc, char *argv[])
{
  int sock;
  sock = socket (PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons (SERVER_PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  int status;
  status = bind (sock, (const struct sockaddr *) &addr, sizeof (addr));
  status = listen (sock, 1);
  

  int fd = accept (sock, 0, 0);

  uint8_t buf[10240];

  memset (buf, 0, 10240);

  for (uint32_t i = 0; i < 10000; i++)
    {
      ssize_t n = 10240;
      while (n > 0)
	{
	  ssize_t bytes_read = read (fd, buf, 10240);
	  n -= bytes_read;
	}
      sleep (1);
    }

  std::cout << "did read all buffers" << std::endl;

  close (sock);
  close (fd);

  return 0;
}