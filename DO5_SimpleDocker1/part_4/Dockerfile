FROM nginx:latest
WORKDIR /home/
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./mini_server_+_spawn-fcgi.c /home/mini_server_+_spawn-fcgi.c
COPY ./start.sh /home/start.sh
RUN  apt-get update; \
apt-get install -y gcc libfcgi libfcgi-dev spawn-fcgi; \
chmod ugo+x start.sh

ENTRYPOINT ["./start.sh"]
