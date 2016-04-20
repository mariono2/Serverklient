#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_net/SDL_net.h>

#define PORT 80
#define MAXLEN 1024

int program()
{
    IPaddress ip;
    TCPsocket sd;
    char server[25] = "", msg2[MAXLEN] = "quit";
    int port, result;
    
    strcpy(server, "130.237.84.89");
    port = PORT;
    
    if (SDLNet_ResolveHost(&ip, server, port) < 0)
    {
        fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    
    if (!(sd = SDLNet_TCP_Open(&ip)))
    {
        fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    
    int len;
    
    len = (int) strlen(msg2)+1;
    
    if (SDLNet_TCP_Send(sd, msg2,len) < len)
    {
        fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    
    result=SDLNet_TCP_Recv(sd,msg2,MAXLEN);
    if(result<=0) {
    }
    printf("Received: \"%s\"\n",msg2);
    
    SDL_Delay( 1000 );
    
    
    return 0;
}
