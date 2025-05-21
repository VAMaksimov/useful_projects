FROM alpine:latest AS builder

RUN apk add --no-cache gcc libc-dev fcgi-dev

WORKDIR /app
COPY ./server/server.c .
RUN gcc server.c -o server.fcgi -lfcgi

FROM alpine:latest

RUN apk add --no-cache nginx fcgi spawn-fcgi tini && \
    addgroup -S appgroup && \
    adduser -S -D -H -u 1000 -G appgroup appuser && \
    mkdir -p /var/run/nginx /var/log/nginx /var/lib/nginx && \
    chown -R appuser:appgroup /var/lib/nginx /var/log/nginx && \
    chmod -R 775 /var/log/nginx /var/lib/nginx && \
    rm -f /etc/nginx/conf.d/default.conf && \
    ln -sf /dev/stdout /var/log/nginx/access.log && \
    ln -sf /dev/stderr /var/log/nginx/error.log && \
    mkdir -p /run/nginx && \
    chown appuser:appgroup /run/nginx && \
    chmod 775 /run/nginx && \
    ln -sf /var/run/nginx/nginx.pid /run/nginx.pid

COPY --from=builder --chown=appuser:appgroup /app/server.fcgi /usr/local/bin/
COPY --chown=appuser:appgroup ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY --chown=appuser:appgroup ./nginx/fastcgi_params /etc/nginx/fastcgi_params
COPY --chown=appuser:appgroup ./nginx/mime.types /etc/nginx/mime.types

RUN sed -i 's|pid /run/nginx.pid;|pid /var/run/nginx/nginx.pid;|' /etc/nginx/nginx.conf && \
    chown -R appuser:appgroup /etc/nginx && \
    chmod -R 755 /etc/nginx && \
    chmod 755 /usr/local/bin/server.fcgi

HEALTHCHECK --interval=30s --timeout=3s \
    CMD wget -q --spider http://localhost/status || exit 1

ENTRYPOINT ["/sbin/tini", "--"]
USER appuser

CMD ["sh", "-c", "spawn-fcgi -p 8080 -f /usr/local/bin/server.fcgi && nginx -g 'daemon off;'"]

EXPOSE 81
