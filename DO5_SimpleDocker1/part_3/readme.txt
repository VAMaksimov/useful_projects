sudo apt-get install libfcgi libfcgi-dev
gcc ./mini_server_-_spawn-fcgi.c -o mini_server_-_spawn-fcgi -lfcgi

sudo apt-get install spawn-fcgi
gcc ./mini_server_+_spawn-fcgi.c -o mini_server_+_spawn-fcgi -lfcgi
spawn-fcgi -p 8080 -n ./mini_server_+_spawn-fcgi
