// ВАРИАНТ С СОКЕТАМИ ДЛЯ ЗАПУСКА C SPAWN-FCGI

// #include <fcgiapp.h>
#include "fcgi_stdio.h"
#include <stdio.h>

int main() {

  while (FCGI_Accept() >= 0) {
    printf("Content-Type: text/html\n\n");

    printf("<html><body><h1>Hello World!</h1></body></html>");
    printf("<html><body><h1>with spawn-fcgi</h1></body></html>");
  }

  return 0;
}
