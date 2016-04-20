#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>

#define FILENAME "startskript.txt"

int main(int argc, char const *argv[])
{
    pid_t getpid();
    int PORT;
    char IP[30];
    
    FILE *fp;
    
    if(!fork())
    {
        if(!(fp=fopen(FILENAME, "r")))
        {
            syslog(LOG_INFO, "unable to open file %s, code %d (%s)", FILENAME, errno, strerror(errno));
            exit(1);
        }
    if(fp != NULL)
    {
        fgets(IP, 22, fp);
        printf("IP: %s", IP);
        fscanf(fp, "%d", &PORT);
        printf("PORT: %d", PORT);
    }
    fclose(fp);
        
    execlp("/bin/sh", "sh", "-c", "./server", IP, PORT, NULL);
    syslog(LOG_ERR, "%s", strerror(errno));
    exit(1);
    }
    wait(0);
    return 0;
}