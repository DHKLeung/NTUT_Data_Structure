/*Question 7a in Data Structures Homework #2, select_sort_ite.c*/
/*In C Language*/
/*Compilation Environment : Linux Redhat x86_64, Windows 10 Enterprise IDE Code:Blocks*/
/*Compiler : GNU GCC version 5.3.1 20151207*/
/*Coded by Daniel Ho Kwan Leung 104360098*/
/*Finished Date : 18/10/2016 (DD/MM/YYYY)*/
#include <stdio.h>
int main(void) {
	int i = 0, j = 0, k = 0, t = 0, a[10000], n = 0, loop = 0;
	scanf("%d", &n);	//user input the total amount of element for sorting 
	for(loop = 0; loop < n; loop++) {	//input the element
		scanf("%d", &a[loop]);
	}
	for (i = 0; i < n; i++) {			//start selection sort
		j = i;
		for (k = i + 1; k < n; k++) {	//find the smallest number's index	
			if (a[k] < a[j]) {
				j = k;
			}
		}
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	for (loop = 0; loop < n; loop++) {	//print the sorted array
		printf("%d ", a[loop]);
	}
	return 0;
}
