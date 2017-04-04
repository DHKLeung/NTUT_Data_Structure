/*Question 6 in Data Structures Homework #5*/
/*In C Language*/
/*Compilation Environment : Linux Redhat x86_64 vim, Windows 10 Enterprise IDE : Code::Blocks, Atom Editor*/
/*Compiler : GNU GCC version 5.3.1 20151207*/
/*Coded by Daniel Ho Kwan Leung 104360098*/
/*Finished Date : 24/12/2016 (DD/MM/YYYY)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define TREEMAX 1025    //for the max amount of tree elements
#define INPUTMAX 512    //for the max characters input
typedef enum _operation operation;
enum _operation {   //enumerate the operation
    create,
    delete,
    change,
    insert,
    print,
    printcontent
};
void inputcommand(char input[]) {
    int stringlength, i;
    if (fgets(input, INPUTMAX, stdin) != NULL) {    //input command
        stringlength = strlen(input);
        for (i = 0; i < stringlength; i++) {    //cut the '\r' and '\n'
            if (input[i] == '\r' || input[i] == '\n') {
                input[i] = '\0';
            }
        }
    }else { //if EOF is entered, exit program
        exit(EXIT_SUCCESS);
    }
}
operation figurefunc(char input[]) {    //figure out the function
    if (strncmp(input, "create-min-heap ", 16) == 0) {
        return create;
    }else if (strncmp(input, "delete-min", 10) == 0 && strlen(input) == 10) {
        return delete;
    }else if (strncmp(input, "change-key ", 11) == 0) {
        return change;
    }else if (strncmp(input, "insert ", 7) == 0) {
        return insert;
    }else if (strncmp(input, "print-content", 13) == 0 && strlen(input) == 13) {
        return printcontent;
    }else if (strncmp(input, "print", 5) == 0 && strlen(input) == 5) {
        return print;
    }else {
        return -1;  //return -1 as wrong command
    }
}
void printproperties(int heaptree[], int length) {  //print the properties of the heaptree
    printf("The min-heap is of size %d and the current minimum is %d.\n", length, heaptree[0]);
}
void cleartree(int heaptree[], int *length) {    //clear the element and the length
    int i;
    for (i = 0; i < *length; i++) {
        heaptree[i] = 0;
    }
    *length = 0;
}
void swapelementbyindex(int heaptree[], int i, int j) { //swap the two element
    int temp;
    temp = heaptree[i];
    heaptree[i] = heaptree[j];
    heaptree[j] = temp;
}
void minheapify(int heaptree[], int root, int length) { //heapify function
    int leftchild, rightchild, minone;
    leftchild = root * 2 + 1;   //the index of leftchild
    rightchild = root * 2 + 2;  //the index of rightchild
    minone = root;  //initially assigned as root
    if (leftchild < length && heaptree[leftchild] < heaptree[root]) {   //if leftchild element is smaller than the root element, assign it to be minone
        minone = leftchild;
    }
    if (rightchild < length && heaptree[rightchild] < heaptree[minone]) {   //if rightchild element is smaller than the minone element, assign it to be minone
        minone = rightchild;
    }
    if (minone != root) {   //if one of the element from rightchild and leftchild is smaller than the root, swap and heap down
        swapelementbyindex(heaptree, root, minone); //swap the minone element and the root element
        minheapify(heaptree, minone, length);   //call itself, heap down from minone as the root
    }
}
void createheap_elementin(int heaptree[], char input[], int *length) {  //put all the elements directly into heaptree
    int spaceplace = 0, i;
    bool negative = false;
    while (input[spaceplace] != ' ') {   //find the index of first space
        spaceplace++;
    }
    for (i = spaceplace + 1; i < strlen(input); i++) {  //analysis the inputted string and assign the num to heaptree
        if (input[i] == '-') {  //negative marker
            negative = true;
        }else if (isdigit(input[i])) {  //process the digit
            heaptree[*length] *= 10;
            heaptree[*length] += input[i] - 48;
        }
        if (input[i] == ' ' || i == strlen(input) - 1) {    //num ended, check the negative, add length by 1
            if (negative == true) {
                heaptree[*length] = 0 - heaptree[*length];
                negative = false;
            }
            *length = *length + 1;
        }
    }
}
void createheap(int heaptree[], char input[], int *length) {    //creating heap
    int i;
    createheap_elementin(heaptree, input, length);  //put the element into the heaptree first
    for (i = (*length / 2) - 1; i >= 0; i--) {  //perform min heapify bottom-up
        minheapify(heaptree, i, *length);
    }
    printproperties(heaptree, *length); //print the properties
}
void deleteminfromheap(int heaptree[], char input[], int *length) { //delete the min
    if (*length == 0) { //if heaptree is empty, return
        return;
    }else {
        heaptree[0] = heaptree[*length - 1];    //perform the remove min action for heap
        heaptree[*length - 1] = 0;
        *length = *length - 1;
        minheapify(heaptree, 0, *length);   //heapify it
        if (*length != 0) {
            printproperties(heaptree, *length); //print the properties
        }
    }
}
void changeelement_extraction(char input[], int *changer, int *beingchanger) {  //extract the changer and beingchanger
    int spaceplace = 0, i;
    bool negative = false;
    while (input[spaceplace] != ' ') {   //find the index of first space
        spaceplace++;
    }
    for (i = spaceplace + 1; i < strlen(input) && input[i] != ' '; i++) {   //extract the beingchanger
        if (input[i] == '-') {
            negative = true;
        }else if (isdigit(input[i])) {
            *beingchanger *= 10;
            *beingchanger += input[i] - 48;
        }
        if (i == strlen(input) - 1 || input[i + 1] == ' ') {
            if (negative == true) {
                *beingchanger = 0 - *beingchanger;
            }
        }
    }
    for (i = i + 1; i < strlen(input); i++) {   //extract the changer
        if (input[i] == '-') {
            negative = true;
        }else if (isdigit(input[i])) {
            *changer *= 10;
            *changer += input[i] - 48;
        }
        if (i == strlen(input) - 1) {
            if (negative == true) {
                *changer = 0 - *changer;
            }
        }
    }
}
int searchindex(int heaptree[], int element, int length) {  //serach the element, return the index
    int i;
    for (i = 0; i < length; i++) {  //search the element
        if (heaptree[i] == element) {
            return i;   //return its index
        }
    }
    return -1;  //if no such element, return -1
}
void changeelement(int heaptree[], char input[], int length) {  //perform the change-key operation
    int changer = 0, beingchanger = 0, beingchangerindex, i;
    changeelement_extraction(input, &changer, &beingchanger);   //extract the changer and the beingchanger
    beingchangerindex = searchindex(heaptree, beingchanger, length);    //get the index of beingchanger
    if (beingchangerindex == -1) {  //if no such element, alert
        printf("No such Key !\n");
        return;
    }else { //element found
        heaptree[beingchangerindex] = changer;  //change key
        for (i = (length / 2) - 1; i >= 0; i--) {  //perform min heapify bottom-up
            minheapify(heaptree, i, length);
        }
    }
    printproperties(heaptree, length);  //print the properties
}
void inserttoheap_insertelement(int heaptree[], char input[], int *length) {    //insert the element into the end of heaptree
    int spaceplace = 0, i;
    bool negative = false;
    while (input[spaceplace] != ' ') {  //find the index of first space
        spaceplace++;
    }
    for (i = spaceplace + 1; i < strlen(input); i++) {  //analysis the string and extract the num need to be inserted to the tree
        if (input[i] == '-') {  //negative marker
            negative = true;
        }else if (isdigit(input[i])) {  //process the digit
            heaptree[*length] *= 10;
            heaptree[*length] += input[i] - 48;
        }
        if (i == strlen(input) - 1) {   //comes to the end of string, insert finished, check the negative, add length by 1
            if (negative == true) {
                heaptree[*length] = 0 - heaptree[*length];
            }
            *length = *length + 1;
        }
    }
}
void inserttoheap(int heaptree[], char input[], int *length) {  //perform insertion of element
    int i;
    inserttoheap_insertelement(heaptree, input, length);    //insert the element into the end of the heaptree
    for (i = (*length / 2) - 1; i >= 0; i = ((i + 1) / 2) - 1) {
        minheapify(heaptree, i, *length);
    }
    printproperties(heaptree, *length); //print the properties
}
void printheaptreecontent(int heaptree[], int length) { //print the content of the heaptree
    int i;
    for (i = 0; i < length; i++) {
        printf("%d ", heaptree[i]);
    }
    printf("\n");
}
int main(int argc, char **argv){    //program started
    int heaptree[TREEMAX] = { 0 }, length = 0;
    char input[INPUTMAX];
    operation func;
    do {
        if (length == 0) { //no element in tree, size is of zero
            printf("The min-heap is empty with size=0.\n");
        }
        inputcommand(input);    //input command and element, if EOF then program exit
        if (strlen(input) == 0) {   //user inputs nothing but entered, don't process, just continue
            continue;
        }
        func = figurefunc(input);   //figure out which function did the user input
        switch (func) {
            case create :
                cleartree(heaptree, &length);    //clear the existed element and length
                createheap(heaptree, input, &length);   //enter the function of creating heap
                break;
            case delete :
                deleteminfromheap(heaptree, input, &length);   //delete min from heap
                break;
            case change :
                changeelement(heaptree, input, length); //change key
                break;
            case insert :
                inserttoheap(heaptree, input, &length); //insert element
                break;
            case print :
                printproperties(heaptree, length);  //print the properties of the heaptree
                break;
            case printcontent :
                printheaptreecontent(heaptree, length); //print the content of the heaptree
                break;
            case -1 :   //user inputted a wrong command
                printf("Wrong Command !\n");
                break;
        }
    } while (true);
    return 0;   //program ended
}
