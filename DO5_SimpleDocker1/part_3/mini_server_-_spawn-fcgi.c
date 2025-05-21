// ВАРИАНТ С СОКЕТАМИ ДЛЯ ЗАПУСКА БЕЗ SPAWN-FCGI

#include <fcgiapp.h>
#include <stdio.h>

int main() {

  FCGX_Init();
  int sockfd = FCGX_OpenSocket("127.0.0.1:8080", 100);

  FCGX_Request req;
  FCGX_InitRequest(&req, sockfd, 0);

  while (FCGX_Accept_r(&req) >= 0) {
    FCGX_FPrintF(req.out, "Content-Type: text/html\n\n");
    // FCGX_FPrintF(req.out, "Hello World!");
    FCGX_FPrintF(req.out, "<html><body><h1>Hello World!</h1></body></html>");
    FCGX_Finish_r(&req);
    printf("Without spawn-fcgi\n");
  }

  return 0;
}
