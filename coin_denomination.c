/*
 	PROBLEM DEFINITION: 
 	
 	You are given n types of coin denominations of values v1 < v2 < ... < vn (all integers). Assume

	v1 = 1, so you can always make change for any integer amount of money C. Design an algo-
	rithm that makes change for an integer amount of money C with as few coins as possible. 
	
	Your algorithm should be as efficient as possible.
	
	Input format
	
	n # type of coins
	Next n lines having n values corresponding to v1 < v2 < ... < vn in the same order (v1 = 1 always true)
	m # number of test cases Next m lines having m test cases
	
	Output format
	For each test case output the list of denominations in a line. So, m lines for m test cases.

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define inf 100000

void returnChange(int deno[], int n, int t)
{
	int i,j;
	int* seq = (int*)malloc(sizeof(int)*(t + 1)); // to keep track of which coins are used to get to a value
	int* min = (int*)malloc(sizeof(int)*(t + 1)); // to hold the minimum number of coins required to get to that value
	for (i = 1; i <= t; i++)
	{
		min[i] = inf;
	}

	min[0] = 0; // the minimum number of coins to get a value of "0" (minimum[i]) will always be 0.

	for (i = 1; i <= t; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i >= deno[j] && 1 + min[i - deno[j]] < min[i])
			{
				min[i] = 1 + min[i - deno[j]]; // update
				seq[i] = j; // record what coin we used to get to this value
			}
		}
	}
	while (t)
	{
		// look at the coin needed to get to target value, print it, then look at the coin needed to get to target value - printed coin 
		printf("%d ",deno[seq[t]]);
		t-=deno[seq[t]];
	}
	printf("\n");

	free(seq);
	free(min);
}

int main()
{
	int* denominations;
	int num_diff_coins,t,n,i,penalties,m;
	char filename[25];
	printf("Enter the number of different coins: ");
	scanf("%d",&num_diff_coins);
	
	denominations = (int*)malloc(sizeof(int)*num_diff_coins);
	
	printf("Enter the denominations of %d coins line by line (first strictly being 1)\n",num_diff_coins);

	for (i = 0; i < num_diff_coins; i++)
	{
		scanf("%d",&denominations[i]);
		if(i==0)
		{
			denominations[i]=1;
		}
	}
	printf("\nEnter the number of test cases: ");
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
		printf("\nEnter the total amount for minimum coin combination: ");
		scanf("%d",&t);
		printf("Here's the resultant combination: ");
		returnChange(denominations, num_diff_coins, t);
	}
	free(denominations);
	return 0;
}
/*
 	Sample input and its output
 	
 	:~/Hacktober21/Hacktoberfest$ gcc coin_denomination.c 
	:~/Hacktober21/Hacktoberfest$ ./a.out
	Enter the number of different coins: 5
	Enter the denominations of 5 coins line by line (first strictly being 1)
	1
	3
	4
	7
	10
	
	Enter the number of test cases: 4

	Enter the total amount for minimum coin combination: 8
	Here's the resultant combination: 1 7 

	Enter the total amount for minimum coin combination: 9
	Here's the resultant combination: 1 1 7 

	Enter the total amount for minimum coin combination: 11
	Here's the resultant combination: 1 10 

	Enter the total amount for minimum coin combination: 27
	Here's the resultant combination: 7 10 10 


*/

