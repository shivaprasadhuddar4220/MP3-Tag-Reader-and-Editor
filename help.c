#include<stdio.h>
#include "header.h"
#define HEADER_SIZE 10
void Mp3_help()
{
     printf("-----------------------------\n");
     printf("     MP3 TAG READER HELP\n");
     printf("-----------------------------\n");

     printf("-v : View MP3 tag\n");
     printf("-e : Edit MP3 tag\n");
     printf("-h : Help\n\n"); 

     printf("Tag Options:\n");
     printf("-t : Title\n");
     printf("-y : Year\n");
     printf("-a : Artist\n");
     printf("-A : Album\n");
     printf("-c : Comment\n");
     printf("-g : Genre\n");
}