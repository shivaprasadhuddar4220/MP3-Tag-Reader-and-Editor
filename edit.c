#include<stdio.h>
#include<string.h>
#include "header.h"
#include<unistd.h>
#include<stdlib.h>

// Function to select which MP3 tag to edit
void Mp3_edit(FILE *fptr)
{
    char option;
    char new_data[100];

    // Display edit menu
    printf("\nWhat you want to edit : \n");
    printf("-t. Title\n-a. Artist\n-A. Album\n-y. Year\n-g. Genre\n-c. Comment\n");

    // Read user option
    printf("\nEnter your choice : ");
    scanf(" -%c",&option);

    // Switch case to check which tag user wants to edit
    switch(option)
    {
        // Edit Title
        case 't':
        printf("\nEnter what you want to edit in title : ");
        scanf(" %[^\n]",new_data);    // Read new title
        edit_tag(fptr,"TIT2",new_data);
        break;

        // Edit Artist
        case 'a':
        printf("\nEnter what you want to edit in artist name : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"TPE1",new_data);
        break;

        // Edit Album
        case 'A':
        printf("\nEnter what you want to edit in album : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"TALB",new_data);
        break;

         // Edit Year
        case 'y':
        printf("\nEnter what you want to edit in year : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"TYER",new_data);
        break;

        // Edit Genre
        case 'g':
        printf("\nEnter what you want to edit in genre : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"TCON",new_data);
        break;

        // Edit Comment
        case 'c':
        printf("\nEnter what you want to edit in comment : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"COMM",new_data);
        break;

        default:
            printf("\n-------> Invalid option <-------\n");

    }
}

// Function to modify a specific MP3 tag
void edit_tag(FILE *fptr,char *tag,char *new_data)
{
    // Pointer for temporary file
    FILE *new_file;

    // Create a temporary MP3 file
    if((new_file = fopen("temp.mp3","w")) == NULL)
    {
        printf("\n------> File not found <------\n");
        return ;
    }

    rewind(fptr);  // Move file pointer to beginning of original file

    char copy[100];   // Buffer to copy first 10 bytes of ID3 header

    fread(copy,10,1,fptr);         // Read ID3 header from original file
    fwrite(copy,10,1,new_file);   // Write header into new file

    char name[5],flag[2];int size;
        
    // Loop to read each frame from MP3 file
    while((fread(name,4,1,fptr)) == 1)
    {
        name[4] = '\0';   // Converting frame ID to string

        // If empty frame reached (padding area)]
        if(name[0]==0 && name[1]==0 && name[2]==0 && name[3]==0)
        {
            break;
        }

        fread(&size,4,1,fptr);   // Read frame size
        fread(flag,2,1,fptr);    // Read frame flags

        int new_len = bigtolittle(size); // Convert big endian to little endian
        char *data = malloc(new_len);    // Dynamically allocate memory for frame data
        if (data == NULL)
        {
            printf("-----> Memory allocation failed <-----\n");
            return;
        }

        fread(data,new_len,1,fptr);   //Read frame data

        // If frame matches the tag user wants to edit
        if((strcmp(name,tag)) == 0)
        {
            fwrite(name,4,1,new_file);       // Write frame name
            int len = strlen(new_data) + 1;   // text + null
            int frame_size = len + 1;         // +1 for encoding
            int big_len = littletobig(frame_size); // Convert to big endian
           
            fwrite(&big_len,4,1,new_file);  // Write new frame size
            fwrite(flag,2,1,new_file);      // Write same flag

            char enc = 0x00;
            fwrite(&enc,1,1,new_file);
            fwrite(new_data,len,1,new_file); // Write updated data
        }
        else
        {
            // If frame is not the one being edited, copy it as it is
            fwrite(name,4,1,new_file);
            fwrite(&size,4,1,new_file);
            fwrite(flag,2,1,new_file);
            fwrite(data,new_len,1,new_file);
        }

        free(data);   // Free dynamically allocated memory
    }

    // ---- copy remaining audio part ----
    char buffer[1024];
    unsigned int r;

    // Read and write audio data until end of file
    while((r = fread(buffer,1,1024,fptr)) > 0)
    {
        fwrite(buffer,1,r,new_file);
    }   

    // Delete old MP3 file
    remove("sample.mp3");
        
    // Rename temp file as original file
    rename("temp.mp3","sample.mp3");
    fclose(new_file);    // Close new file
    printf("\n");

    for(int i = 0; i <= 100; i++)
    {
        printf("Editing..%d%%\r",i);
        fflush(stdout);
    }
    printf("\rEdited successfully\n");
}

// Function to convert Big Endian to Little Endian
int bigtolittle(int num)
{
   return ((num & 0xFF000000) >> 24) |
    ((num & 0x00FF0000) >> 8)  |
    ((num & 0x0000FF00) << 8)  |
    ((num & 0x000000FF) << 24);
}

// Function to convert Little Endian to Big Endian
int littletobig(int num)
{
    return ((num & 0x000000FF) << 24) |
    ((num & 0x0000FF00) << 8)  |
    ((num & 0x00FF0000) >> 8)  |
    ((num & 0xFF000000) >> 24);
}
