#include<stdio.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){

    int dev = open("/dev/dev_number", O_RDONLY);
    if (dev == -1) {
        printf("Opening was not possible!!") ;
        return -1 ;    
    }
    
    printf("opening was successfully!!\n") ; 
    close(dev) ;
    return 0 ;
}