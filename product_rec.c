/*Question 6a in Data Structures Homework #2, product_rec.c*/
/*In C Language*/
/*Compilation Environment : Linux Redhat x86_64, Windows 10 Enterprise IDE Code:Blocks*/
/*Compiler : GNU GCC version 5.3.1 20151207*/
/*Coded by Daniel Ho Kwan Leung 104360098*/
/*Finished Date : 17/10/2016 (DD/MM/YYYY)*/
#include <stdio.h>
int product_rec(int m, int n) { 
    if (n == 1) {   //return the value m if n equals 1
        return m;
    }else {
        return m + product_rec(m, n - 1);   //recursively call itself with the decrement of n
    }
}
int main(void) {	//main function
    int m = 0, n = 0, temp = 0;
    scanf("%d %d", &m, &n); //input m & n
    if (m < n) {    //ensure the n to be the smallest number among m & n,
        temp = n;   //so that the number of times calling function will be least
        n = m;
        m = temp;
    }
    printf("%d\n", product_rec(m, n));  //print the value returned by the function called
    return 0;
}
