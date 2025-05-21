#!/bin/bash

gcc -o dev_server dev_server.c -lfcgi
spawn-fcgi -p 8080 ./dev_server
nginx -g "daemon off;"
