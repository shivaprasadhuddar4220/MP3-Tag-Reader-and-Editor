/*
Name:-Shivaprasad H
Staring Date:-02/02/2026
Ending Date:-06/02/2026
Desccription:-Project on MP3 TAG Reader and Editor
*/
#include<stdio.h> 
#include<string.h>
#include "header.h" 
#include<unistd.h>

int main()
{
    printf("***********************************************************\n");
    printf("*            WELCOME TO MP3 TAG READER                    *\n");
    printf("***********************************************************\n");

    FILE *fptr;

    char choice;

    // Loop runs until user selects Exit option
    do
    {
    printf("\nMp3 Tag Reader Menu:\n");
    printf("\n-v. For View\n");
    printf("-e. For Edit\n");
    printf("-h. For help\n");
    printf("-E. Exit\n");
    
    //Read user input
    printf("\nEnter your choice : ");
    scanf(" -%c",&choice);

    // Switch case to execute based on user choice
    switch(choice)
    {
         // Case for viewing MP3 tags
        case 'v':
        {
            char file_name[20];
            printf("\nEnter the file name you want to view : ");
            scanf(" %[^\n]",file_name);

            // Open the file in read mode
            if((fptr = fopen(file_name,"r")) == NULL)
            {    
                printf("\n------> File not found <------\n");
                return 1;
            }

            char buffer[5];    // Buffer to store first 3 characters of MP3 file

            // Read first 3 bytes of the file
            fread(buffer,3,1,fptr);
            buffer[3] = '\0';
                    
        // Check if first 3 characters are "ID3"
        if(strcmp(buffer,"ID3") != 0)
            {
                printf("\n------> It is not mp3 file <------\n");
                return 0;
            }
            Mp3_view(fptr);    // Call function to display MP3 tag information
            fclose(fptr);
            break;
        }
        
        // Case for editing MP3 tags
        case 'e':
        {
            char file_name[20];
            // Read file name
            printf("\nEnter the file name you want to view : ");
            scanf(" %[^\n]",file_name);

            // Open file in read mode
            if((fptr = fopen(file_name,"r")) == NULL)
            {    
                printf("\n------> File not found <------\n");
                return 1;
            }

            // Buffer to store header information
            char buffer[5];

            // Read first 3 bytes from the file
            fread(buffer,3,1,fptr);
            buffer[3] = '\0';
    
            // Check if file contains "ID3" tag
            if(strcmp(buffer,"ID3") != 0)
                {
                    printf("\n-----> It is not mp3 file <------\n");
                    return 0;
                }
            Mp3_edit(fptr);   // Call function to edit MP3 tags
            fclose(fptr);
            break;
        }

        // Case for help menu
        case 'h':
        {
            Mp3_help();  // Call help function
        }

        // Case to exit program
        case 'E':
        {
            printf("\rExited successfully\n");
            break;
        }

        // If user enters invalid option
        default: 
            printf("\n------> Invalid Option <------\n");
            return 1;
    }
    }while(choice != 'E');   // Loop continues until user selects Exit


    return 0;
} 