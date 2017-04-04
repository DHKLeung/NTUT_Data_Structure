/*Question 6b in Data Structures Homework #2, product_ite.c*/
/*In C Language*/
/*Compilation Environment : Linux Redhat x86_64, Windows 10 Enterprise IDE Code:Blocks*/
/*Compiler : GNU GCC version 5.3.1 20151207*/
/*Coded by Daniel Ho Kwan Leung 104360098*/
/*Finished Date : 17/10/2016 (DD/MM/YYYY)*/
#include <stdio.h>
int main(void) {	//main function
    int m = 0, n = 0, temp = 0, i = 0, sum = 0;
    scanf("%d %d", &m, &n);
    if (m < n) {	//ensure the n to be the smallest number among m & n,
        temp = n;   //so that the number of times calling function will be least
        n = m;
        m = temp;
    }
    for (i = 0; i < n; i++) {	//loop iteratively and accumulate the sum with m
        sum += m;	
    }
    printf("%d\n", sum);	//print the sum
    return 0;
}
