#include "types.h"
#include "user.h"
#include "date.h"
int main(void){
 int pid = fork();
        if(pid==0)
                printf(1,"I am a child\n");
        ps();
        wait();
        exit();
}
