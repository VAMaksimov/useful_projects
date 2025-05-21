sudo apt-get install libfcgi libfcgi-dev
sudo apt-get install spawn-fcgi
gcc ./mini_server_+_spawn-fcgi.c -o mini_server_+_spawn-fcgi -lfcgi
spawn-fcgi -p 8080 -n ./mini_server_+_spawn-fcgi

docker build -t my-nginx:latest .

docker run -d -p 80:81 my-nginx
docker run -d -p 80:81 -v ./nginx:/etc/nginx my-nginx

удалить нахер все контейнеры:
docker stop ID
docker container prune
