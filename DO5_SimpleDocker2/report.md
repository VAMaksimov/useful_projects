## Part 1. Ready-made docker

- Устанавливаем docker-образ с nginx:
> sudo docker pull nginx

![install docker](screenshots/part.1/part_1.1.png)

- Далее смотрим образ через команду:
>sudo docker images

![view images](screenshots/part.1/part_1.2.png)

- Запускаем контейнер nginx, флаг -d в фоновом режиме (detached mode).
- Это означает, что контейнер будет работать в фоновом режиме, 
- и командная строка будет освобождена для дальнейшего использования.
>sudo docker run -d nginx

![run image_id](screenshots/part.1/part_1.3.png)


- Удостоверимся что контейнер успешно запустился через команду:
> sudo docker ps

![check start docker](screenshots/part.1/part_1.4.png)

- Получаем информацию о контейнере в JSON формате:
> sudo docker inspect container_id|container_name

![check info docker](screenshots/part.1/part_1.5.png)

- Выводим размер контейнера

![size docker](screenshots/part.1/part_1.6.png)

- Выводим список замапленных портов

![exposed docker](screenshots/part.1/part_1.7.png)

- Выводим IP контейнера

![id docker](screenshots/part.1/part_1.8.png)

- Остановим docker-образ командой: 
> docker stop \[container_id|container_name\].
- Проверим образ через команду docker ps

![stop docker](screenshots/part.1/part_1.9.png)

- Запустим docker-образ с портами 80 и 443 через команду docker run

![start docker](screenshots/part.1/part_1.10.png)

- Проверяем что порт работает, открываем в браузере страницу по адресу localhost

![port docker](screenshots/part.1/part_1.11.png)

- Перезапускаем контейнер через команду:
>docker restart \[container_id|container_name\]
- и проверим что контейнер снова запустился командой docker ps

![restart docker](screenshots/part.1/part_1.12.png)

## Part 2. Operations with container

- Читаем конфигурационный файл nginx.conf внутри docker-контейнера:
>docker exec

![read conf docker](screenshots/part.2/part_2.1.png)

- Создаем локальный файл nginx.conf

![create nginx.conf](screenshots/part.2/part_2.2.png)

- Прописываем в конфиге отдачу сервера
- stub_status on; — включает страницу статуса.

![status nginx.conf](screenshots/part.2/part_2.3.png)

- Переносим созданный конфиг внутрь docker-образа:
>docker cp

![transfer nginx.conf](screenshots/part.2/part_2.4.png)

- Перезапускаем nginx внутри docker-образа:
>docker exec

![restart nginx.conf](screenshots/part.2/part_2.5.png)

- Проверяем localhost/status что конфиг работает 

![status nginx.conf](screenshots/part.2/part_2.6.png)

- Экспортируем наш контейнер в файл container.tar:
>docker export 
- Так как продолжил заниматься дальнейшей настройкой на след. день, занового 
  перезапускал докер образ, тем самым изменился как id так и name контейнера

- После экспорта останавливаем контейнер

![export stop conrainer](screenshots/part.2/part_2.7.png)

- Удаляем образ, не удаляя перед этим контейнеры:
>docker rmi -f \[image_id|repository\]

![remove image](screenshots/part.2/part_2.8.png)


- После чего удалим остановленный контейнер:
>docker rm 

![remove conrainer name](screenshots/part.2/part_2.9.png)

- Ипортируем контейнер обратно :
>docker import 
- и запустим ипортированный контейнер:
>docker run

![impoer start image](screenshots/part.2/part_2.10.png)

- Проверяем нашу страничку localhost/status 

![status nginx](screenshots/part.2/part_2.11.png)

## Part 3. Mini web server

- Для создания мини веб-сервера необходимо создать .с файл, в котором опишем логику(вывод сообщения "Hello World")

![create dev server](screenshots/part.3/part_3.1.png)

- Настраиваем конфиг где с помощью дерективы fastcgi_pass направляем
запросы на FastCGI-сервер

![create config](screenshots/part.3/part_3.2.png)

- Запускаем новый образ на 81 порту

![run port81](screenshots/part.3/part_3.3.png)

- После перекидываем конфиг и логику сервера в новый контейнер

![transfer conf and devSer](screenshots/part.3/part_3.4.png)

- Для успешного запуска мини веб-сервера на FastCGI нужно подгрузить нужные утилиты
>spawn-fcgi libfcgi-dev

![inst libs](screenshots/part.3/part_3.5.png)

- Скомпилируем и запустим наш веб-сервер через команду:
>spawn-fcgi

![start server](screenshots/part.3/part_3.6.png)

- В адресной строке прописываем http://localhost:81 и радуемся что все работает

![check server](screenshots/part.3/part_3.7.png)

## Part 4. Your own docker

- Реализуем свой docker-образ, на базе 3-го тз.
- Создаём свой Dockerfile, и run.sh для указания целей
- конфиг и скрипт копируем из 3-го тз

![create dockerfile](screenshots/part.4/part_4.1.png)

![create bash](screenshots/part.4/part_4.2.png)

- Собираем написанный docker-образ через команду:
>docker build
- -t указываем имя и :тег нашего контейнера

![build conteiner](screenshots/part.4/part_4.3.png)

- Удостоверимся что все скомпилировалось проверкой образа

![check conteiner](screenshots/part.4/part_4.4.png)

- Запускаем docker-образ с маппингом порта 81 на порт 80 локальной машины и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а

![error conteiner](screenshots/part.4/part_4.5.png)

- Видим что при успешном запуске нам потребуется образ из 
  папки nginx для последующего маппинга
- Создадим временный образ, и скопируем его в директорию nginx.
- Временный образ останавливаем

![fix error](screenshots/part.4/part_4.6.png)

- Снова пробуем запустить

![build nginx](screenshots/part.4/part_4.7.png)

- Видим что сборка собралась пробуем перейти на localhost

![check localhost](screenshots/part.4/part_4.8.png)

- Видим что страничка с "Hello World" отобразилась.
- Далее меняем конфиг, пересобираем dev:server, и смотрим уже статус 

![add new con](screenshots/part.4/part_4.9.png)

![check status](screenshots/part.4/part_4.10.png)

## Part 5. Dockle
- Для проверки образов контейнеров для обеспечения безопасности
нам потребуется Dockle 
>https://github.com/goodwithtech/dockle

![inst dockle](screenshots/part.5/part_5.1.png)

- После установки вводим команду 
>dockle dev:server 
- на проверку нашего контейнера и у меня появилась такая ошибка 

![error one](screenshots/part.5/part_5.2.png)
- ошибка нам говорит что dockle интерпретируер dev:server как образ из DOCKER_HUB,
а не как локальный образ

- Решение данной проблемы-> созраняем образ в tar-архив
>sudo docker save dev:server -o dev_server.tar
- Далее уже от образа запускаем dockle
>sudo dockle --input ./dev_server.tar
- И наблюдаем уже ошибки по безопасности

![error two.1](screenshots/part.5/part_5.3.png)
![error two.2](screenshots/part.5/part_5.4.png)

- Для их устранения используем дистрибутив Alpine.
- Alpine Linux — это мощный инструмент для создания 
оптимизированных, безопасных и легковесных контейнеров. 
- Добавляем новые правила в docker-file

![conf dockerfile](screenshots/part.5/part_5.5.png)

- Билдим новый контейнер

![builf new cont](screenshots/part.5/part_5.6.png)

- Проверяем на наличие ошибок

![ckeck dockle](screenshots/part.5/part_5.7.png)

- Остается одна ошибка которая связана с включением Docker Content Trust (DCT).
это механизм, который обеспечивает подпись и проверку образов Docker, чтобы 
гарантировать их подлинность и целостность.
- Отключать данный механизм не рекомендуется, т.к. снижает безопасность.

## Part6. Basic Docker Compose

- Для начала установим compose
>sudo curl -L "https://github.com/docker/compose/releases/download/v2.20.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose

![change bash](screenshots/part.6/part_6.1.png)

- Далее перепишем скрипт для второго контейнера, иначе он будет завершать работу после 
docker-compose up

![change bash](screenshots/part.6/part_6.2.png)

- Так же перепишем конфиг для проксирования 

![change conf1](screenshots/part.6/part_6.3.png)

![change conf2](screenshots/part.6/part_6.3.1.png)

- Напишем docker-compose.yml

![yaml conf](screenshots/part.6/part_6.4.png)

- Останавливаем все запущенные контейнеры

![tak stop naxyi](screenshots/part.6/part_6.5.png)

- Запускаем docker-compose build и docker-compose up.

![statrt docker-compose](screenshots/part.6/part_6.6.png)

- Проверяем localhost и localhost/status

![statrt docker-compose](screenshots/part.6/part_6.7.png)