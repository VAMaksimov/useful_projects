FROM alpine:latest
WORKDIR /home/
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./run.sh  /home/run.sh
RUN apk update && apk add --no-cache gcc spawn-fcgi fcgi fcgi-dev musl-dev nginx curl
RUN addgroup nginx root
RUN chmod +x /home/run.sh
ENTRYPOINT ["sh", "/home/run.sh"]
HEALTHCHECK --interval=1m --timeout=5s --retries=3 CMD curl -f http://localhost/ || exit 1