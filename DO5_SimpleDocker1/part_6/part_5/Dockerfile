FROM nginx:latest

USER root

WORKDIR /home/
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./mini_server_+_spawn-fcgi.c /home/mini_server_+_spawn-fcgi.c
COPY ./start.sh /home/start.sh
RUN  apt-get update; \
apt-get install -y gcc libfcgi libfcgi-dev spawn-fcgi; \
apt-get clean && rm -rf /var/lib/apt/lists/*

RUN chmod ugo+x start.sh; \
 chmod u-s /usr/bin/newgrp; \
 chmod u-s /usr/bin/passwd; \
 chmod u-s /usr/bin/gpasswd; \
 chmod u-s /usr/bin/chsh; \
 chmod g-s /usr/bin/chage; \
 chmod u-s /usr/bin/mount; \
 chmod g-s /usr/sbin/unix_chkpwd; \
 chmod g-s /usr/bin/expiry; \
 chmod u-s /usr/bin/chfn; \
 chmod u-s /usr/bin/su; \
 chmod u-s /usr/bin/umount

# USER nginx

 HEALTHCHECK --interval=5m --timeout=3s \
    CMD curl -f http://localhost/ || exit 1

ENTRYPOINT ["./start.sh"]
