FROM nginx
USER root
WORKDIR /home/
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./dev_server.c /home/dev_server.c
COPY ./run.sh  /home/run.sh
RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
RUN apt-get install -y gcc spawn-fcgi libfcgi-dev
RUN chmod +x /home/run.sh
ENTRYPOINT ["/home/run.sh"]