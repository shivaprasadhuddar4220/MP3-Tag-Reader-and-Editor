// declearation of function
#include<stdio.h>
#ifndef HEADER_H
#define HEADER_H

void Mp3_view(FILE *fptr); //decleration of view function
void Mp3_edit(FILE *fptr); //declaration of edit function
void Mp3_help(); //declaration for help function
void edit_tag(FILE *fptr,char *tag,char *new_data); //for editing the tags.
int bigtolittle(int num);
int littletobig(int num);

#endif