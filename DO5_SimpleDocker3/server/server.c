#include <fcgiapp.h>

int main(void) {
    FCGX_Init();
    FCGX_Request request;
    FCGX_InitRequest(&request, 0, 0); // важно: socket = 0

    while (FCGX_Accept_r(&request) >= 0) {
        FCGX_FPrintF(request.out,
                     "Content-Type: text/html\r\n\r\n"
                     "<html><body><h1>Hello World!</h1></body></html>");
        FCGX_Finish_r(&request);
    }

    return 0;
}
