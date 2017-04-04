/*Question 5 in Data Structures Homework #4*/
/*In C Language*/
/*Compilation Environment : Linux Redhat x86_64 vim, Windows 10 Enterprise IDE Code::Blocks*/
/*Compiler : GNU GCC version 5.3.1 20151207*/
/*Coded by Daniel Ho Kwan Leung 104360098*/
/*Finished Date : 9/12/2016 (DD/MM/YYYY)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct _treenode treenode;  //typedef the _treenode as the new name treenode
struct _treenode {  //set the struct of _treenode
    treenode *parent;
    char name[21];
    treenode *leftchild;
    treenode *rightchild;
};
void input_process(char str[], char mother[], char child1[], char child2[]) {   //string processing of the input line, separate the entire line into mother, child1 and child2
    bool donemo = false, donec1 = false, donec2 = false;
    int i, eachindex;
    mother[0] = child1[0] = child2[0] = '\0';
    for (i = 0, eachindex = 0; i < strlen(str); i++) {  //separate the mother, child1 and child2
        if (str[i] != ' ') {
            if (donemo == false) {
                mother[eachindex] = str[i];
            }else if (donec1 == false) {
                child1[eachindex] = str[i];
            }else if (donec2 == false) {
                child2[eachindex] = str[i];
            }
            eachindex++;
        }else if (str[i] == ' ') {  //after each separation, complement a '\0' at the end of string'
            if (donemo == false) {
                mother[eachindex] = '\0';
                donemo = true;
                eachindex = 0;
            }else if (donec1 == false) {
                child1[eachindex] = '\0';
                donec1 = true;
                eachindex = 0;
            }
        }
    }
    if (donec1 == false) {  //for the case of only one child, or complementing '\0' at the end of child2
        child1[eachindex] = '\0';
    }else if (donec2 == false) {
        child2[eachindex] = '\0';
    }
}
void preorder(treenode *temp) { //print the tree in preorder
    if (temp != NULL) {
        printf("%s ", temp->name);
        preorder(temp->leftchild);
        preorder(temp->rightchild);
    }
}
void inorder(treenode *temp) {  //print the tree in inorder
    if (temp != NULL) {
        inorder(temp->leftchild);
        printf("%s ", temp->name);
        inorder(temp->rightchild);
    }
}
void postorder(treenode *temp) {    //print the tree in postorder
    if (temp != NULL) {
        postorder(temp->leftchild);
        postorder(temp->rightchild);
        printf("%s ", temp->name);
    }
}
treenode* search_preorder(treenode *temp, char str[]) { //search the treenode, if searched, return the address of the element
    treenode *target = NULL;
    if (temp != NULL) {
        if (strcmp(temp->name, str) == 0) { //if it matches the target string, return the address
            target = temp;
            return target;
        }else {
            target = search_preorder(temp->leftchild, str); //go to the left child and search
            if (target == NULL) {   //if can't find the matching target, then go to the right child and search
                target = search_preorder(temp->rightchild, str);
            }
            return target;  //after searching, return. if it search successfully, it returns the address. if no matches, return NULL
        }
    }else {
        return NULL;    //NULL node, return NULL
    }
}
treenode* create_node(char str[]) { //create a new treenode, return the address of the new treenode
    treenode *temp;
    temp = (treenode*)malloc(sizeof(treenode)); //dynamic allocating memories for the new node
    strcpy(temp->name, str);    //initialize the node
    temp->parent = NULL;
    temp->leftchild = NULL;
    temp->rightchild = NULL;
    return temp;    //return the address of the node
}
void insert_node(treenode *ptr, char mother[], char child[]) {  //insert the newly created treenode under a parent
    treenode *target, *newchild;
    newchild = create_node(child);
    target = search_preorder(ptr, mother);
    if ((child[strlen(child) - 1] - 48) % 2 == 0) { //if the last digit is even, then it's right child, connect to the parent's right
        target->rightchild = newchild;
        newchild->parent = target;
    }else if ((child[strlen(child) - 1] - 48) % 2 == 1) {   //if the last digit is odd, then it's left child, connect to the parent's left
        target->leftchild = newchild;
        newchild->parent = target;
    }
}
int height_preorder(treenode *temp) {   //find out and return the height + 1 value of the tree using preorder traversal
    int tempheight, leftrec, rightrec;
    if (temp != NULL) {
        leftrec = 1 + height_preorder(temp->leftchild); //find the left subtree's height
        rightrec = 1 + height_preorder(temp->rightchild);   //find the right subtree's height
        return ((leftrec > rightrec) ? leftrec : rightrec); //return the highest height
    }else {
        return 0;   //NULL node, return 0 height
    }
}
int get_height(treenode *ptr) { //get the height
    int height;
    height = height_preorder(ptr);  //call height_preorder function and save the returned value
    return height - 1; //return height - 1
}
int balancefactor(treenode *root) { //find out the balancefactor, which is the height of left subtree minus the height of the right subtree
    int leftheight = 0, rightheight = 0;
    leftheight = get_height(root->leftchild);
    rightheight = get_height(root->rightchild);
    return leftheight - rightheight;
}
void printtree(treenode *ptr) { //print what the question has required
    printf("Preorder:\t");  //print preorder
    preorder(ptr);
    printf("\n");
    printf("Inorder:\t");   //print inorder
    inorder(ptr);
    printf("\n");
    printf("Postorder:\t"); //print postorder
    postorder(ptr);
    printf("\n");
    printf("The balance factor is:\t%d", balancefactor(ptr));   //print balance factor
    printf("\n");
}
int main(int argc, char **argv) {   //main program, read the following string in command line in argv[1]
    char str[201], mother[21], child1[21], child2[21];
    treenode *root = NULL, *temp = NULL;
    int i, originlength;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {   //can't open file, no file inputted
        printf("No Input binaryTree.txt file!\n");
        fclose(fp);
    }else {
        while(fgets(str, sizeof(str), fp) != NULL) {    //get the whole line in the binaryTree.txt
            if (str[0] == '\n') {   //if the file ended with extra newline, break
                break;
            }else {   //change the character '\n' and '\r' that the fgets got into '\0'
                originlength = strlen(str); //save the original length, not affected by replacing the character by '\0'
                for (i = 0; i < originlength; i++) {
                    if (str[i] == '\r' || str[i] == '\n') {
                        str[i] = '\0';
                    }
                }
            }
            input_process(str, mother, child1, child2); 	//call input_process for stirng processing
            if (strcmp(mother, "r") == 0) { //if it is the root, create root
                root = create_node(mother);
            }
            if (strcmp(child1, "\0") != 0) {    //create and insert left child
                insert_node(root, mother, child1);
            }
            if (strcmp(child2, "\0") != 0) {    //create and insert right child
                insert_node(root, mother, child2);
            }
        }
        fclose(fp); //close FILE pointer
        printtree(root);    //print what the question required
    }
    return 0;   //program ended
}
