#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"


int
readcommand(char *buf, int nbuf)
{
    fprintf(2, "$ ");
    memset(buf, 0, nbuf);
    gets(buf, nbuf);
    if(buf[0] == 0) // EOF
        return -1;
    return 0;
}

int
main(int argc, char *argv[])
{
    int n;
    char *args[MAXARG];
    char buf[512];
    int space = 0;
    if(argc < 2){
        fprintf(2, "Usage: xargs command...\n");
        exit();
    }

    /*for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    printf("Number of arguments: %d\n", argc);*/
    while((n = read(0, buf, sizeof(buf))) > 0){
        for(int k = 0; k < n; k++){
            if(buf[k] == '\n'){
                buf[k]= space; //make the new line essentially null
                //printf("buf[%d]: %s\n", k, buf[k]);
                for(int j = 1; j < argc; j++){
                    args[j-1] = argv[j]; //ignore initial xargs call
                }
                args[argc-1] = buf; //slot no longer used, so the space is included in buf
                int pid = fork();
                if(pid == 0){
                    exec(args[0], args);
                    exit();
                }
                else {
                    wait();
                }
            }
        }
    }
    exit();
}