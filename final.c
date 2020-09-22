/*Written by Esteban Brugal*/

/*This is a fee invoice application for students. You can add students and what courses
they're taking. You can also print their fee invoice and add or delete courses.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct{
    int course;
    int credit;
    char prefix[1000];
}room;

typedef struct{
    int id;
    char name[1000];
    room course[4];
}student;

int check(int, student lol[], int); //check if courses exist and add to student
int addStudent(student lol[]); //adds new student
void set(student lol[]); //sets all ids and courses to -1
int find(student lol[]); //find student with specific id
int addCourse(student lol[]);   //add or delete a course from the student
void setCred(student lol[], int pos);     //set credits and prefixes of the course
void newfee(student lol[], int);    //print fee invoice after adding or deleting a course
int fee(student lol[]);
int realCourse(int c1); //check if course is real
void printAllCourses(); //prints all available courses

int main()
{
    int selection;
    int n=1;
    student list[100];
    set(list);
    printf("Welcome!\n");
    while(n){
    fflush(stdin);
    selection = -1;
    printf("Choose from the following options:\n");
    printf("\t1- Add a new student\n\t2- Add/Delete a course for a student\n\t3- Search for a student\n\t4- Print fee invoice\n\t0- Exit program\n\n");
    printf("Enter your selection: ");
    scanf("%d", &selection);
    if(selection >=0 && selection<=4){
    switch (selection){
            case 0: printf("\nGoodbye!"); n=0; break;
            case 1: addStudent(list); break;
            case 2: addCourse(list);  break;
            case 3: find(list);       break;
            case 4: fee(list);           break;
        }
    }else{
        fflush(stdin);
    }
    printf("\n\n---------------\n\n");
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int addStudent(student std[]){
    int id;
    int position;
    char name[1000];
    int course;
    printf("\nEnter the student's id (max is 9999): ");
    if(scanf("%d", &id)==0){
      id = id - '0';
    }
    while(id<0|| id>9999){
        printf("\nId must be less than 9999 and cant be negative. Enter again: ");
        fflush(stdin);
        scanf("%d", &id);
    }
    for(int i=0; i<100; i++){
        if (id==std[i].id){
            printf("\nSorry, someone else already has that id.");
            return 1;
        }
    }
    for(int i=0; i<100; i++){
        if(std[i].id==-1){
            std[i].id = id;
            position = i;
            break;
        }
    }
    printf("Enter student's name: ");
    fflush(stdin);
    gets(name);
    strcpy (std[position].name, name);
    printf("\n\nEnter how many courses [%s] is taking(up to 4 courses)?\n\t", name);
    scanf("%d", &course);
    while(course<1 || course>4){
        printf("\nSorry, wrong amount of courses. Enter again: ");
        scanf("%d", &course);
    }
        printAllCourses();
        printf("\nEnter the %d course numbers\n\t", course);
        check(course, std, position);

    return 1;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void set(student std[]){
    for(int i=0; i<100; i++){
        std[i].id=-1;
        for(int j=0; j<4; j++){
           std[i].course[j].course = -1;
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int check(int num, student std[], int pos){
    int c1, c2, c3, c4;
    switch(num){
        case 1:
            scanf("%d", &c1);
            while(c1!=4587 && c1!=4599 && c1!=8997 && c1!=9696 && c1!=1232 && c1!=9856 && c1!=8520 && c1!=8977){
                printf("Sorry, you entered the wrong courses. Try again:\n\t");
                scanf("%d", &c1);
            }
                std[pos].course[0].course = c1;
                setCred(std, pos);

            break;
        case 2:
            scanf("%d %d", &c1, &c2);
            while(((c1!=4587 && c1!=4599 && c1!=8997 && c1!=9696 && c1!=1232 && c1!=9856 && c1!=8520 && c1!=8977)||(c2!=4587 && c2!=4599 && c2!=8997 && c2!=9696 && c2!=1232 && c2!=9856 && c2!=8520 && c2!=8977))|| c1==c2){
                printf("Sorry, you entered the wrong courses or a duplicate course. Try again:\n\t");
                scanf("%d %d", &c1, &c2);
            }
                std[pos].course[0].course = c1;
                std[pos].course[1].course = c2;
                setCred(std, pos);

            break;
        case 3:
            scanf("%d %d %d", &c1, &c2, &c3);
            while(((c1!=4587 && c1!=4599 && c1!=8997 && c1!=9696 && c1!=1232 && c1!=9856 && c1!=8520 && c1!=8977)||(c2!=4587 && c2!=4599 && c2!=8997 && c2!=9696 && c2!=1232 && c2!=9856 && c2!=8520 && c2!=8977)||(c3!=4587 && c3!=4599 && c3!=8997 && c3!=9696 && c3!=1232 && c3!=9856 && c3!=8520 && c3!=8977))|| (c1==c2 || c1==c3 || c2==c3)){
                printf("Sorry, you entered the wrong courses or a duplicate course. Try again:\n\t");
                scanf("%d %d %d", &c1, &c2, &c3);
            }
                std[pos].course[0].course = c1;
                std[pos].course[1].course = c2;
                std[pos].course[2].course = c3;
                setCred(std, pos);

            break;
        case 4:
            scanf("%d %d %d %d", &c1, &c2, &c3, &c4);
            while(((c1!=4587 && c1!=4599 && c1!=8997 && c1!=9696 && c1!=1232 && c1!=9856 && c1!=8520 && c1!=8977)||(c2!=4587 && c2!=4599 && c2!=8997 && c2!=9696 && c2!=1232 && c2!=9856 && c2!=8520 && c2!=8977)||(c3!=4587 && c3!=4599 && c3!=8997 && c3!=9696 && c3!=1232 && c3!=9856 && c3!=8520 && c3!=8977)||(c4!=4587 && c4!=4599 && c4!=8997 && c4!=9696 && c4!=1232 && c4!=9856 && c4!=8520 && c4!=8977))||(c1==c2 || c1==c3 || c1==c4 || c2==c3 || c2==c4 || c3==c4)){
                printf("Sorry, you entered the wrong courses or a duplicate course. Try again:\n\t");
                scanf("%d %d %d %d", &c1, &c2, &c3, &c4);
            }
                std[pos].course[0].course = c1;
                std[pos].course[1].course = c2;
                std[pos].course[2].course = c3;
                std[pos].course[3].course = c4;
                setCred(std, pos);

    }
    printf("\nStudent added successfully!");
    return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int find(student std[]){
    int id;
    printf("Enter the student's id: ");
    scanf("%d", &id);
    for(int i=0; i<100; i++){
        if(std[i].id==id){
            printf("\n\nStudent found. Their name is %s", std[i].name );
            return 1;
        }
    }
    printf("\n\nNo Student found!");
    return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int addCourse(student std[]){
    int id;
    int position;
    printf("\nEnter the student's id: ");

    if(scanf("%d", &id)==0){
      id = id - '0';
    }
    fflush(stdin);
    if(id>-1 && id<9999){
    for(int i=0; i<100; i++){
        if(std[i].id==id){
            position = i;
            printf("\nHere are the courses [%s] is taking:\n", std[i].name);
            printf("\t\tCRN   CR_PREFIX   CR. HOURS\n");
            for(int i=0; i<4; i++){
                if(std[position].course[i].course>1000)
                printf("\t\t%d  %s\t    %d\n", std[position].course[i].course, std[position].course[i].prefix, std[position].course[i].credit);
            }
            printf("\nChoose from:\n");
            printf("A- Add a new course for [%s]\n", std[position].name);
            printf("D- Delete a course from [%s]'s schedule\n", std[position].name );
            printf("C- Cancel operation\n\n");
            fflush(stdin);
            printf("Enter your selection: ");
            char ans;
            scanf("%c", &ans);
            ans = tolower(ans);
            while (ans != 'a' && ans != 'd' && ans != 'c'){
                fflush(stdin);
                printf("\nInvalid Entry (it has to be a, d or c): ");
                scanf("%c", &ans);
            }
            int change;
            switch(ans){
                case 'a':
                    printAllCourses();
                    printf("\nEnter course Number to add: ");
                    fflush(stdin);
                    int bruh = scanf("%d", &change);
                    while(bruh==0){
                        printf("\nPlease enter a number. Try again: ");
                        fflush(stdin);
                        bruh = scanf("%d", &change);
                    }
                    for(int i=0; i<4; i++){
                        if(std[position].course[i].course==change){
                            printf("\nCourse already taken.");
                            return 1;
                        }
                    }
                        if (realCourse(change)){
                        for(int i=0; i<4; i++){
                        if(std[position].course[i].course==-1){

                            std[position].course[i].course=change;
                            setCred(std, position);
                            printf("\n[%d %s] is added succesfully!", std[position].course[i].course, std[position].course[i].prefix);
                            char answer;
                            fflush(stdin);
                            printf(" Want to display the new invoice? Y/N: ");
                            scanf("%c", &answer);
                            answer = tolower(answer);
                            while (answer != 'n' && answer != 'y'){
                                fflush(stdin);
                                printf("\nInvalid Entry (it has to Y or N): ");
                                scanf("%c", &answer);
                            }
                            if(answer == 'y') newfee(std, position);
                            return 1;

                        }else if (i==3){
                            printf("\nStudent is already taking the maximum amount of courses.");
                            return 1;
                        }
                        }
                    }
                    printf("\nCourse doesn't exist.");
                    return 1; break;
                case 'd':
                    printf("\nEnter course Number to delete: ");
                    fflush(stdin);
                    int bruhh = scanf("%d", &change);
                    while(bruhh==0){
                        printf("\nPlease enter a number. Try again: ");
                        fflush(stdin);
                        bruhh = scanf("%d", &change);
                    }
                    for(int i=0; i<4; i++){
                        if(std[position].course[i].course==change){
                            printf("\n[%d %s] is deleted succesfully!", std[position].course[i].course, std[position].course[i].prefix);
                            std[position].course[i].course=-1;
                            std[position].course[i].credit=0;
                            strcpy(std[position].course[i].prefix, "");
                            char answer;
                            fflush(stdin);
                            printf("Want to display the new invoice? Y/N: ");
                            scanf("%c", &answer);
                            answer = tolower(answer);
                            while (answer != 'n' && answer != 'y'){
                                fflush(stdin);
                                printf("\nInvalid Entry (it has to Y or N): ");
                                scanf("%c", &answer);
                            }
                            if(answer == 'y') newfee(std, position);
                            return 1;
                        }else if (i==3){
                            printf("\nStudent isn't taking this course.");
                            return 1;
                        }
                    }
                case 'c': printf("\nOperation canceled."); return 1; break;
            }
        }
    }
}
    printf("\n\nStudent doesn't exist");
    return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setCred(student std[], int pos){
    for(int i=0; i<4; i++){
        switch (std[pos].course[i].course){
            case 4587 : std[pos].course[i].credit = 4; strcpy(std[pos].course[i].prefix, "MAT 236"); break;
            case 4599 : std[pos].course[i].credit = 3; strcpy(std[pos].course[i].prefix, "COP 220"); break;
            case 8997 : std[pos].course[i].credit = 1; strcpy(std[pos].course[i].prefix, "GOL 124"); break;
            case 9696 : std[pos].course[i].credit = 3; strcpy(std[pos].course[i].prefix, "COP 100"); break;
            case 1232 : std[pos].course[i].credit = 5; strcpy(std[pos].course[i].prefix, "MAC 531"); break;
            case 9856 : std[pos].course[i].credit = 2; strcpy(std[pos].course[i].prefix, "STA 100"); break;
            case 8520 : std[pos].course[i].credit = 5; strcpy(std[pos].course[i].prefix, "TNV 400"); break;
            case 8977 : std[pos].course[i].credit = 1; strcpy(std[pos].course[i].prefix, "CMP 100"); break;
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void newfee(student std[], int pos){
    puts("\n\t\tVALENCE COMMUNITY COLLEGE\n\t\tORLANDO FL 10101\n\t\t---------------------\n");
    printf("\t\tFee Invoice Prepared for Student: \n\t\t%d-%s\n\n", std[pos].id, std[pos].name);
    printf("\t\t1 Credit Hour = $120.25\n\n");
    printf("\t\tCRN   CR_PREFIX   CR_HOURS\n");
    float total;
    for(int i=0; i<4; i++){
        if(std[pos].course[i].course>1000){
            printf("\t\t%d  %s\t    %d", std[pos].course[i].course, std[pos].course[i].prefix, std[pos].course[i].credit);
            printf("\t %6c %.2f\n", '$', (float)std[pos].course[i].credit * 120.25);
            total += (float)std[pos].course[i].credit * 120.25;
       }
    }
    printf("\n\t\t\t    Health & id fees  $  35.00\n\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t\t    Total Payments    $  %.2f\n", total + 35);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int fee(student std[]){
    int id;
    int position;
    printf("\nEnter the student's id: ");
    scanf("%d", &id);
    for(int i=0; i<100; i++){
        if(std[i].id==id){
            position = i;
            newfee(std, position);
            return 1;
        }
    }
    printf("\nThis student doesn't exist.");
    return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int realCourse(int c1){
    if (c1!=4587 && c1!=4599 && c1!=8997 && c1!=9696 && c1!=1232 && c1!=9856 && c1!=8520 && c1!=8977){
        return 0;
    }
    return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void printAllCourses(){
    printf("\nCourse List:\n");
    printf("\t4587\t4599\t8997\t9696\t1232\t9856\t8520\t8977");
}
