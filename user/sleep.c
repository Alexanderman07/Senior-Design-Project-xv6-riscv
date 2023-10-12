#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int k;

    if(argc < 2){
    fprintf(2, "Usage: sleep files...\n");
    exit();
  }

    k = atoi(argv[1]);
    sleep(k);
    exit();
}