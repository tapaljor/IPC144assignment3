/*
IPC144 N1F - Assignment3 
Group #2
Sheba Birhanu
Tashi Paljor

C CODE
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define MAX_APPLICATION 10 
#define NAME_SIZE 200

typedef struct passport {
    unsigned long int id;
    char *firstName;
    char *lastName;
    unsigned long int age;
} Passport;

void allocateMemory(Passport *data[]);
void getFirstNameFromApplicant(Passport *data[], unsigned int);
void getLastNameFromApplicant(Passport *data[], unsigned int);
void getAgeFromApplicant(Passport *data[], unsigned int);
void displayData(const Passport *data[]);
void freeMemory(Passport *data[]);
char * getString();
int checkName(const char *);
unsigned int checkAge(const unsigned int);
void clearInputBuffer(void);
//Function generates unique ID with help of 
//time stamp (seconds starting from 1970-01-01 00000);
unsigned long int generateUniqueId();

int main(void) {

    Passport *data[MAX_APPLICATION];

    allocateMemory(data);
    for(size_t a = 0; a < MAX_APPLICATION; a++) {
        data[a]->id = generateUniqueId(a); 
        getFirstNameFromApplicant(data, a);
        getLastNameFromApplicant(data, a);
        getAgeFromApplicant(data, a);
    }
    displayData((const Passport**) data);
    freeMemory(data); 

    return 0;
}
void allocateMemory(Passport *data[]) {

    for(size_t a = 0; a < MAX_APPLICATION; a++) {
        data[a] = malloc(sizeof(Passport));

        if ( data[a] == NULL) {
            printf("Mello allocation error\n");
        }
        data[a]->firstName = malloc(NAME_SIZE*sizeof(char));
        data[a]->lastName = malloc(NAME_SIZE*sizeof(char));
    }
}
void getFirstNameFromApplicant(Passport *data[], unsigned int a) {

    printf("Enter first name: ");
    char *str =  getString();
    strcpy(data[a]->firstName, str); 
}
void getLastNameFromApplicant(Passport *data[], unsigned int a) {

    printf("Enter last name: ");
    char *str = getString();
    strcpy(data[a]->lastName, str); 
}
void getAgeFromApplicant(Passport *data[], unsigned int a) {

    unsigned int check = 0;
    unsigned int age = 0;

    printf("Enter age (older than 16): ");
    scanf("%d", &age);
    clearInputBuffer();

    check = checkAge(age);

    if (check == 1) {
        data[a]->age = age;
    } else {
        getAgeFromApplicant(data, a);
    } 
}
unsigned int checkAge(const unsigned int age) {

        if ( age > 16) {
            return 1;
        } else {
            return 0;
        }
}
char * getString() {

    static char str[NAME_SIZE];
    unsigned int check = 0;

    scanf("%199[^\n]", str);
    clearInputBuffer();

    check = checkName(str);

    if ( check == 0) {
        printf("Enter again: ");
        getString(); //calls function until all conditions met
    } 
    return str;
}
int checkName(const char *str) {

    int checkCharacter = 0;
    int checkAlpha = 0;

    if (strlen(str) < 2 || strlen(str) > 200) {
        printf("Name should be more than one and less than 200 character\n");
        checkCharacter++;
    }
    while(*str != '\0') { //checking string until last character
        if (!isalpha(*str) || isspace(*str)) { // checks for alphas only
            checkAlpha++;
        }
        str++;
    }
    if (checkAlpha > 0) {
        printf("Name should be only a-z or A-Z\n");
    }
    if (checkCharacter > 0 || checkAlpha > 0) {
        return 0;
    } else {
        return 1;
    }
}
void displayData(const Passport *data[]) {

    unsigned int serialNo = 1;

    printf("%-3s%-20s%-20s%-20s%2s\n", "---", "---------", "----------", "----------", "---");
    printf("%-3s%-20s%-20s%-20s%2s\n", "#", "ID", "First Name", "Last Name", "Age");
    printf("%-3s%-20s%-20s%-20s%2s\n", "---", "----------", "----------", "----------", "---");
    for(size_t a = 0; a < MAX_APPLICATION; a++) {
        printf("%-3d%-20lu%-20s%-20s%2d\n", serialNo++, data[a]->id,
                                         data[a]->firstName, 
                                         data[a]->lastName, 
                                         data[a]->age
                                         );
    }
    printf("%-3s%-20s%-20s%-20s%2s\n", "---", "----------", "----------", "----------", "---");
}
void freeMemory(Passport *data[]) {

    for(size_t a = 0; a < MAX_APPLICATION; a++) {
        free(data[a]);
    }
}
unsigned long int generateUniqueId() {
    return (unsigned long int)time(NULL); //seconds from 1970s till now is unque
}
void clearInputBuffer(void) {

    while (getchar() != '\n') {
        ; // On purpose: do nothing
    }
}