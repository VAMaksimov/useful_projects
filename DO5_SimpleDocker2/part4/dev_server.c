#include <fcgi_stdio.h>
#include <stdlib.h>

int main(){
    while(FCGI_Accept() >= 0){
        printf("Content-Type: text/html\r\n");
        printf("\r\n");

        printf("Hello World!\n");
    }
    return 0;
}