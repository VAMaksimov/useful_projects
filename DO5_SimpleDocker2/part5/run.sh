#!/bin/bash

gcc -o dev_part5 dev_part5.c -lfcgi
spawn-fcgi -p 8080 ./dev_part5
nginx -g "daemon off;"
