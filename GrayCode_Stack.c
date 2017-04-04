/*Question 5 in Data Structures Homework #3*/
/*In C Language*/
/*Compilation Environment : Linux Redhat x86_64, Windows 10 Enterprise IDE Code::Blocks*/
/*Compiler : GNU GCC version 5.3.1 20151207*/
/*Coded by Daniel Ho Kwan Leung 104360098*/
/*Finished Date : 28/10/2016 (DD/MM/YYYY)*/
#include <stdio.h>
struct stack_char {	//define a struct for stack
	char element[1048576];
	int top_index;
};
typedef struct stack_char stack_char_adt;	//typedef the struct a new name "stack_char_adt"
void scadt_initialize(stack_char_adt *s_process) {	//initializing the stack
	int i = 0;
	for (i = 0; i < 1048576; i++) {
		s_process->element[i] = ' ';	//set all non-used space into ' '
	}
	s_process->top_index = -1;	//-1 means that the stack is empty
}
void scadt_push(char input, stack_char_adt *s_process) {	//push function of the stack
	s_process->top_index += 1;
	s_process->element[s_process->top_index] = input;
}
char scadt_pop(stack_char_adt *s_process) {		//pop function of the stack
	char output;
	output = s_process->element[s_process->top_index];
	s_process->element[s_process->top_index] = '+';
	s_process->top_index -= 1;
	return output;
}
int scadt_size(stack_char_adt s_process) {		//return the size of the function
	return s_process.top_index + 1;
}
int scadt_isEmpty(stack_char_adt s_process) {		//return value of whether the stack is empty or not
	if (s_process.top_index == -1) {
		return 1;
	}
	else {
		return 0;
	}
}
char scadt_top(stack_char_adt s_process) {		//return the top element of the stack
	return s_process.element[s_process.top_index];
}
int main(void) {	//main function starts
	stack_char_adt inis, ref, carry;	//define 4 stack
	int n = 0, i = 0, j = 0, k = 0, power = 0;	//define the iterative counter and the power for bit calculation
	scadt_initialize(&inis);	//initializing the stack
	scadt_initialize(&ref);
	scadt_initialize(&carry);
	scadt_push('1', &inis);		//push the initial element to the stack which is for the compulsory element when 1 bit
	scadt_push('0', &inis);
	printf("Enter an integer n: ");		//user input, enter the integer n,
	scanf("%d", &n);					//so that the program will figure out the gray code of n bits
	printf("The list of %d-bit Gray code is: ", n);		//print the question required statement
	if (n == 1) {	//if n is 1, then just print out the 0 and 1
		printf("%c ", scadt_pop(&inis));
		printf("%c\n", scadt_pop(&inis));
	}
	else {	//n is not equal to 1
		power = 2;	//set the power to 2, because we have to build gray code from 2 bits to n bits
		for (i = 2; i <= n; i++) {	//i means the bit that is current processing
			power *= 2;	//power increase with a square
			for (j = 1; j <= power / 2; j++) {	//processing the upper part of gray code which the first bit is '0'
				scadt_push('0', &carry);	//push a bit to stack carry
				for (k = 1; k <= i - 1; k++) {	//keep the top element of inis in carry, pop the top element of inis and push it  to ref for later reflection
					scadt_push(scadt_top(inis), &carry);
					scadt_push(scadt_pop(&inis), &ref);
				}
			}
			for (j = 1; j <= power / 2; j++) {	//processing the lower part of gray code which the first bit is '1'
				scadt_push('1', &carry);	//push a bit to stack carry
				for (k = 1; k <= i - 1; k++) {	//push the i - 1 times element popped from ref to inis
					scadt_push(scadt_pop(&ref), &inis);
				}
				for (k = 1; k <= i - 1; k++) {	//push the i - 1 times element popped from inis to carry
					scadt_push(scadt_pop(&inis), &carry);
				}
			}
			while (!scadt_isEmpty(carry)) {	//push all element popped from carry to inis, they are the finished element, and ready for the next bit processing
				scadt_push(scadt_pop(&carry), &inis);
			}
		}
		i = 1;	//i for controling the space printed
		while (!scadt_isEmpty(inis)) {
			printf("%c", scadt_pop(&inis));	//print the element popped from inis
			if (i % n == 0) {	//if the amount of printed element = n, then print a space
				printf(" ");
				i = 1;
			}
			else {	//else, increment
				i++;
			}
		}
		printf("\n");	//program finishing with an \n
	}
	return 0;	//program terminated
}
