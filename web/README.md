# Own tips
## How I started xampp [linux]
I. I started by installing [MySQL Connector/C++](https://askubuntu.com/questions/165868/installing-mysql-connector-c), I used 
`
apt-get install libmysqlcppconn-dev
`<br/><br/>
II. Error while writing c++ program [here](http://stackoverflow.com/questions/14604228/mysql-h-file-cant-be-found), it was about header instead of ~~mysql.h~~ -> mysql/mysql.h.<br/><br/>
III. I forgot about [linker](http://stackoverflow.com/questions/9645844/mysql-with-c-error-undefined-reference-to-mysql-init), I added -lmysqlclient.<br/><br/>
IV. Then I realized that if I want to do database stuff I need to do it local, sending ready-made php file into your online 
website is time-consuming. I installed [xampp](https://www.apachefriends.org/pl/index.html). Then mysql didn't wanted to start. Here is the [reason](http://stackoverflow.com/questions/22971248/xampp-phpmyadmin-access-denied-error2002). Afterward how to change .txt file with sudo [here](http://www.linuxforums.org/forum/ubuntu-linux/108324-how-do-i-open-edit-text-file-sudo.html).
`
sudo nano /path-to-file/file-name
`<br/><br/>
V. Now I move on with [this](https://www.youtube.com/watch?v=siQCWPxDtMo&t=1179s)

## C++, MySQL
I. So i tried connect via c++ with online mySQL database. I ended by "Error: 2003, Can't connect to MySQL server" - 02.05.2017. <br/>
Linker:`-lmysqlclient` <br/>

## MySQL C++ connector
I. I tried with C++ connector but this also doent's seem to work. I laid back by "ERR: Can't connect to MySQL server on (110)" -03.05.2017. <br/>
Linker: `-lmysqlcppconn` <br/>

## SFML Network
I. Still without any experience I started sfml network. I quickly got sneaky and agan laid back with this -04.05.2017. <br/>
Linker: `;-lsfml-network` <br/>

## Curl - Final Solution
I. 
