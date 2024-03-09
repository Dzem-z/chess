## chess
## my SFML chess program

This project was started in 2020. The purpose of this was to enhance my coding skills(and have fun ;]). In 2022 I rewrote the backend part to be more readable and implemented in an object-oriented way. 

## Compiling
To compile and run this program you need to have installed SFML library.
You can do this by entering:
```
apt-get install libsfml-dev
```
or download it manually from https://www.sfml-dev.org/download.php
then:  
```
g++ -c main.cpp  
g++ main.o -o chess -lsfml-graphics -lsfml-window -lsfml-system  
./chess
```
