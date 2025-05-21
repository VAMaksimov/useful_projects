#!/bin/bash

systemctl enable nginx
service nginx start
nginx -s reload

gcc ./mini_server_+_spawn-fcgi.c -o mini_server_+_spawn-fcgi -lfcgi
spawn-fcgi -p 8080 -n ./mini_server_+_spawn-fcgi
