/*Written by Esteban Brugal*/

/*This program reads a in.txt file, prints it all out, and prints the number of characters in it.
This includes spaces and newlines*/

#include <stdio.h>
#include <stdlib.h>

int count(FILE *);           //returns how many letters in file
void print(char *, int);     //prints file

int main()
{
    FILE *fl;
    fl = fopen("in.txt", "r");

    if(fl == NULL){
        printf("Error opening file.");
        return EXIT_FAILURE;
    }

    int length = count(fl);
    rewind(fl);
    char *text = malloc(length);
    char c = fgetc(fl);
    *text = c;

    int i = 1;
    while(c != EOF){          //this loop stores file into array
        c = fgetc(fl);
        text[i] = c;
        i++;
    }

    print(text, length);  //prints content of file
    printf("\n\nNumber of characters in file: %d", length);
    fclose(fl);           //closes file

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int count(FILE *t){
    int count = 0;
    char c = fgetc(t);

    while (c != EOF){
        count++;
        c = fgetc(t);
    }
    return count;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void print(char *arr, int size){

    for(int i=0; i<size; i++){
        printf("%c", arr[i]);
    }

}
