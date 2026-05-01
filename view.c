#include<stdio.h>
#include<string.h>
#include"header.h"

// Function to display MP3 tag information
void Mp3_view(FILE *fptr)
{
    // Move the file pointer 7 bytes forward from current position
    fseek(fptr,7,SEEK_CUR);
    int count = 0;
    char tag[5];

    // Infinite loop to read each frame until break condition
    while(1)
    {
        // Read 4 bytes from file (frame ID)
        if(fread(tag,4,1,fptr) != 1)
            break;

        tag[4] = '\0';

        // If frame ID is empty (padding area), stop reading
        if(tag[0]==0 && tag[1]==0 &&tag[2]==0 && tag[3]==0)
            break;

        int size;
        fread(&size,4,1,fptr);   // Read 4 bytes of frame size

        int len = bigtolittle(size);
        // Convert frame size from big endian to little endian

    
        fseek(fptr, 2, SEEK_CUR);       // Skip 2 bytes of frame flags
        char data[len + 1];            // Array to store frame data (+1 for null terminator)
        
        fread(data,len,1,fptr);     // Read frame data from the file
        data[len] = '\0';          // Add null character to convert it into a string

        // Check if frame is TITLE
        if((strcmp(tag,"TIT2")) == 0)
        {
            printf("\nTITLE   : %s\n",data + 1);
        }
                
        // Check if frame is YEAR
        else if (strcmp(tag, "TYER") == 0)
        {
            printf("YEAR    : %s\n", data + 1);
        }

        // Check if frame is ARTIST
        else if (strcmp(tag, "TPE1") == 0)
        {
            printf("ARTIST  : %s\n", data + 1);
        }

        // Check if frame is ALBUM
        else if (strcmp(tag, "TALB") == 0)
        {
            printf("ALBUM   : %s\n", data + 1);
        }

        // Check if frame is GENRE
        else if(strcmp(tag, "TCON") == 0)
        {
            printf("GENRE   : %s\n", data + 1);
        }

        // Check if frame is COMMENT
        else if(strcmp(tag, "COMM") == 0)
        {
            printf("COMMENT : %s\n", data + 1);
        }

    }
}