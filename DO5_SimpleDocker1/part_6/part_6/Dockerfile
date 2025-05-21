FROM nginx:latest

USER root

WORKDIR /home/
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./start.sh /home/start.sh

RUN chmod ugo+x start.sh

ENTRYPOINT ["./start.sh"]
