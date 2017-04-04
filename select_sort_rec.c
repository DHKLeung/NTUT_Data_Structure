/*Question 7b in Data Structures Homework #2, select_sort_rec.c*/
/*In C Language*/
/*Compilation Environment : Linux Redhat x86_64, Windows 10 Enterprise IDE Code:Blocks*/
/*Compiler : GNU GCC version 5.3.1 20151207*/
/*Coded by Daniel Ho Kwan Leung 104360098*/
/*Finished Date : 18/10/2016 (DD/MM/YYYY)*/
#include <stdio.h>
int find_smallest(int a[], int n, int j, int k) {
    if (k <= n) {
        if (a[k] < a[j]) {	//compare the two element
            return find_smallest(a, n, k, k + 1);	//if a[k] < a[j] then, index j becomes k 
        }else {										//and recursively call itself with increment of k
            return find_smallest(a, n, j, k + 1);	//if a[k] < a[j] is invald, j remains the same
        }											//and recursively call it self with increment of k
    }else {
        return j;			//compare till the last element, return j as the smallest number's index
    }
} 
void selectsort_rec(int a[], int n, int i) {	
    int j = 0, t = 0;
    if (i <= n) {	// if i <= n, not yet the end of array
        j = find_smallest(a, n, i, i + 1);	//find the index of the smallest number among the array and return it to j
        t = a[i];			//swap the two element
        a[i] = a[j];
        a[j] = t;
        selectsort_rec(a, n, i + 1);	//recursively call itself if the increment of i
    }
}
int main(void) {
    int i = 0, loop = 0, n = 0, a[10000];
    scanf("%d", &n);	//user input the total amount of element for sorting 
    for (loop = 0; loop < n; loop++) {	//input the element
        scanf("%d", &a[loop]);
    }
    selectsort_rec(a, n - 1, i);	//call the selection sort function
    for (loop = 0; loop < n; loop++) {	//print the sorted array
        printf("%d ", a[loop]);
    }
    printf("\n");
    return 0;
}
