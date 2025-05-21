# DO5_SimpleDocker

## Part 1. Ready-made docker

- Take the official docker image from nginx and download it using `docker pull`
  - ![Рис. 1: docker pull nginx](./img/01_docker_pull.png)
  - *`docker pull nginx`*
&nbsp;
- Check for the docker image with `docker images`
  - ![Рис. 2: docker images](./img/02_docker_images.png)
  - *`docker images`*
&nbsp;
- Run docker image with `docker run -d [image_id|repository]`
  - ![Рис. 3: docker run -d nginx](./img/03_docker_run_d_nginx.png)
  - *`docker run -d nginx`*
&nbsp;
- Check that the image is running with `docker ps`
  - ![Рис. 4: docker ps](./img/04_docker_ps.png)
  - *`docker ps`*
&nbsp;
- View container information with `docker inspect [container_id|container_name]`
  - ![Рис. 5: docker inspect [container_id]](./img/05_docker_inspect_container.png)
  - *`docker inspect [container_id]`*
&nbsp;
- From the command output define and write in the report the container size, list of mapped ports and container ip
  - ![Рис. 6: docker ps s](./img/05_docker_inspect_container_size.png)
  - **Container size:** 81.9kB (207MB virtual)
  - **Mapped ports:** "80/tcp": null
  - **IPAddress:** 172.17.0.2
&nbsp;
- Stop docker container with `docker stop [container_id|container_name]`
  - ![Рис. 7: docker stop [container_id]](./img/06_docker_stop_container.png)
  - *`docker stop [container_id]`*
&nbsp;
- Check that the container has stopped with docker ps.
  - ![Рис. 8: docker ps](./img/07_docker_ps.png)
  - *`docker ps`*
&nbsp;
- Run docker with ports 80 and 443 in container, mapped to the same ports on the local machine, with run command.
  - ![Рис. 9: docker run -d -p 80:80 -p 443:443 nginx](./img/08_docker_map_ports.png)
  - *`docker run -d -p 80:80 -p 443:443 nginx`*
&nbsp;
- Check that the nginx start page is available in the browser at localhost:80
  - ![Рис. 10: localhost:80](./img/09_nginx_index.png)
  - *`localhost:80`*
&nbsp;
- Restart docker container with `docker restart [container_id|container_name]`.
  - ![Рис. 11: docker restart [container_id]](./img/10_docker_restart.png)
  - *`docker restart [container_id]`*
&nbsp;
- Check in any way that the container is running.
  - ![Рис. 12: docker ps](./img/11_docker_restart_ps.png)
  - *`docker ps`*
&nbsp;

## Part 2. Operations with container

- Read the nginx.conf configuration file inside the docker container with the `exec` command.
  - ![Рис. 12: docker exec [container_id] cat /etc/nginx/nginx.conf](./img/12_docker_exec_nginx_conf.png)
  - *`docker exec [container_id] cat /etc/nginx/nginx.conf`*
&nbsp;
- Create a nginx.conf file on a local machine.
- Configure it on the /status path to return the nginx server status page.

  ```nginx
    user nginx;
    worker_processes auto;

    error_log /var/log/nginx/error.log notice;
    pid /var/run/nginx.pid;

    events {
        worker_connections 1024;
    }

    http {
        include /etc/nginx/mime.types;
        default_type application/octet-stream;

        server {
            listen 80;
            server_name  localhost;

            location /status {
                stub_status on;
                allow all;
            }
        }

        log_format main '$remote_addr - $remote_user [$time_local] "$request" '
        '$status $body_bytes_sent "$http_referer" '
        '"$http_user_agent" "$http_x_forwarded_for"';

        access_log /var/log/nginx/access.log main;

        sendfile on;
        keepalive_timeout 65;
    }
  ```

- Copy the created nginx.conf file inside the docker image using the `docker cp` command.
  - ![Рис. 13: docker cp ./nginx.conf [container_id]:/etc/nginx/nginx.conf](./img/13_docker_cp_nginx_conf.png)
  - *`docker cp ./nginx.conf [container_id]:/etc/nginx/nginx.conf`*
&nbsp;
- Restart nginx inside the docker image with `exec`.
  - ![Рис. 14: docker exec [container_id] nginx -s reload](./img/14_docker_nginx_restart.png)
  - *`docker exec [container_id] nginx -s reload`*
&nbsp;
- Check that `localhost:80/status` returns the nginx server status page.
  - ![Рис. 15: localhost:80/status](./img/15_localhost_status.png)
  - *`localhost:80/status`*
&nbsp;
- Export the container to a `container.tar` file with the export command.
  - ![Рис. 16: docker export [container_id] > container.tar](./img/16_docker_export.png)
  - *`docker export [container_id] > container.tar`*
&nbsp;
- Stop the container.
  - ![Рис. 17: docker stop [container_id]](./img/17_docker_stop.png)
  - *`docker stop [container_id]`*
&nbsp;
- Delete the image with `docker rmi [image_id|repository]` without removing the container first.
  - ![Рис. 18: docker rmi -f [repository]](./img/18_docker_rmi.png)
  - *`docker rmi -f [repository]`*
&nbsp;
- Delete stopped container.
  - ![Рис. 19: docker rm [container_id]](./img/19_docker_rm_container.png)
  - *`docker rm [container_id]`*
&nbsp;
- Import the container back using the import command.
  - ![Рис. 20: docker import container.tar [image_name]](./img/20_docker_import_container.png)
  - *`docker import container.tar [image_name]`*
&nbsp;
- Run the imported container.
  - ![Рис. 21: docker run -d -p 80:80 -p 443:443 [image_name] nginx](./img/21_docker_import_container_run.png)
  - *`docker run -d -p 80:80 -p 443:443 [image_name] nginx`*
&nbsp;
- Check that localhost:80/status returns the nginx server status page.
  - ![Рис. 22: localhost:80/status](./img/22_localhost_status.png)
  - *`localhost:80/status`*


docker run -d -p 80:80 -v "$(pwd)/server/nginx.conf:/etc/nginx/nginx.conf" --name fcgi-app school21-fcgi-server:1.0

## Part 3. Mini web server

- Write a mini server in C and FastCgi that will return a simple page saying `Hello World!`
  - ![Рис. 23: mini sever compile](./img/23_mini_server_gcc.png)
  - *`gcc server.c -o server.fcgi -lfcgi`*
&nbsp;
- Run the written mini server via spawn-fcgi on port 8080
  - ![Рис. 24: start mini sever on port 8080](./img/24_spawn_8080.png)
  - *`spawn-fcgi -p 8080 -f ./server.fcgi`*
&nbsp;
- Write your own nginx.conf that will proxy all requests from port 81 to 127.0.0.1:8080
  - ![Рис. 25: nginx.conf proxy](./img/25_nginx_conf.png)
  - *`cat /etc/nginx/nginx.conf`*
&nbsp;
- Check that browser on localhost:81 returns the page you wrote
  - ![Рис. 26: localhost:81 hello world](./img/26_localhost_81.png)
  - *`localhost:81`*

## Part 4. Your own docker

- Write your own docker image that:
  1) builds mini server sources on FastCgi from [Part 3];
  2) runs it on port 8080;
  3) copies inside the image written ./nginx/nginx.conf;
  4) runs nginx.
  - ![Рис. 27: Dockerfile](./img/27_dockerfile.png)
  - *`Dockerfile`*
&nbsp;
- Build the written docker image with docker build, specifying the name and tag
  - ![Рис. 28: docker build](./img/28_docker_image_fastcgi.png)
  - *`docker build -t fcgi-nginx:alpine .`*
&nbsp;
- Check with docker images that everything is built correctly
  - ![Рис. 29: docker images](./img/29_docker_image_fastcgi_done.png)
  - *`docker images | findstr "fcgi-nginx"`*
&nbsp;
- Run the built docker image by mapping port 81 to 80 on the local machine and mapping the ./nginx folder inside the container to the address where the nginx configuration files are located (see Part 2)
  - ![Рис. 30: docker images](./img/30_docker_run_01.png)
  - *`docker run -d -p 80:81 -v ${PWD}/nginx:/etc/nginx fcgi-nginx:alpine`*
&nbsp;
- Check that the page of the written mini server is available on localhost:80
  - ![Рис. 31: localhost](./img/31_docker_run_localhost.png)
  - *`localhost`*
&nbsp;
- Add proxying of /status page in ./nginx/nginx.conf to return the nginx server status.
  - ![Рис. 32: update nfinx.conf](./img/32_docker_update_nginx.png)
  - *`update nfinx.conf`*
&nbsp;
- Restart docker image.
  - ![Рис. 33: docker restart [container_id]](./img/33_docker_update_and_restart.png)
  - *`docker restart [container_id]`*
&nbsp;
- Check that localhost:80/status now returns a page with nginx status
  - ![Рис. 34: localhost/status](./img/34_docker_localhost_status.png)
  - *`localhost/status`*

## Part 5. Dockle

- Check the image from the previous task with dockle [image_id|repository]
  - ![Рис. 35: docker run --rm -v /var/run/docker.sock:/var/run/docker.sock goodwithtech/dockle:latest fcgi-nginx:alpine](./img/35_dockle_warn.png)
  - *`docker run --rm -v /var/run/docker.sock:/var/run/docker.sock goodwithtech/dockle:latest fcgi-nginx:alpine`*
&nbsp;
- Fix the image so that there are no errors or warnings when checking with dockle
  - ![Рис. 36: docker run --rm -v /var/run/docker.sock:/var/run/docker.sock goodwithtech/dockle:latest fcgi-nginx:alpine](./img/36_dockle_warn_no.png)
  - *`docker run --rm -v /var/run/docker.sock:/var/run/docker.sock goodwithtech/dockle:latest fcgi-nginx:alpine`*

## Part 6. Basic Docker Compose

- Write a docker-compose.yml file, using which:
  1) Start the docker container from Part 5 (it must work on local network, i.e., you don't need to use EXPOSE instruction and map ports to local machine).
  2) Start the docker container with nginx which will proxy all requests from port 8080 to port 81 of the first container.
  - ![Рис. 37: docker-compose](./img/37_docker_compose.png)
  - *`docker-compose.yml`*
&nbsp;
- Map port 8080 of the second container to port 80 of the local machine
  - ![Рис. 38: proxy-nginx.conf to map ports](./img/38_map_ports.png)
  - *`proxy-nginx.conf to map ports`*
&nbsp;
- Stop all running containers
  - ![Рис. 39: docker stop $(docker ps -q)](./img/39_docker_stop.png)
  - *`docker stop $(docker ps -q)`*
&nbsp;
- Build and run the project with the docker-compose build and docker-compose up commands
  - ![Рис. 40: docker-compose build](./img/40_docker_compose_build.png)
  - *`docker-compose build`*
  - ![Рис. 41: docker-compose -p fcgi-school21 up -d](./img/41_docker_compose_up.png)
  - *`docker-compose -p fcgi-school21 up -d`*
&nbsp;
- Check that the browser returns the page you wrote on localhost:80 as before
  - ![Рис. 42: localhost](./img/42_localhost.png)
  - *`localhost`*
