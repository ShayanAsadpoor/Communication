# How to run the program
Project structure:
1) app.c
2) appService.c
3) dataService.c
4) phyService.c
5) libApp.c
6) encDec.h

   
- main application contains producer & consumer
using fork and two pipes to create a new process and communicate parent / child process
compile:
gcc -o app app.c libApp.c
run:
./app
test:
create a file which is named "filename.inpf"
save lower case data in it.
run ./app
related file(s) according to instruction (pdf) will be created


- appService / dataService / phyService
these are services which are described in instruction (pdf)
all of these are application and can run separately.
compile:
gcc -o appService appService.c
gcc -o dataService dataService.c
gcc -o phyService phyService.c


run:
./appService -e [data-to-encode]

./appService -d [data-to-decode]

./dataService -e [data-to-encode]

./dataService -d [data-to-decode]

./phyService -e [data-to-encode]

./phyService -d [data-to-decode]

output of each service prints on terminal screen.
sample:

./phyService -e ABC


oputput:
110000011100001001000011


- libApp library of functions to call services by fork / execlp system calls.
prototype of functions is defined in encDec.h
