#include<stdio.h>
#include<stdlib.h>


long int max(long int i, long int j) 
{
    if(i>j)
    {
        return i;
    }
    else
    {
        return j;
    }
    
}

long int kanpsack_0_1(long int maxWt, long int n, long int weight[], long int value[])
{

	if (n == 0 || maxWt == 0)
    {
		return 0;
    }

	else if (weight[n - 1] > maxWt)
    {
		return kanpsack_0_1(maxWt, n-1, weight, value );
    }

	else
    {
        long int temp1 = value[n - 1] + kanpsack_0_1(maxWt - weight[n - 1], n - 1,weight, value);
        long int temp2 = kanpsack_0_1(maxWt, n - 1, weight, value);
		return max(temp1,temp2);
    }
}

long int knapsackUnbounded(long int maxWt,long int value[], long int weight[], long int n)
{
    long int computationArr[maxWt+1];
    long int a=0;
    while(a<=maxWt)
    {
        computationArr[a] = 0;
        a++;
    }

    long int b=0;
    while(b <= maxWt)
    {
        long int c=0;
        while(c < n)
        {
            if(weight[c] <= b)
            {
                computationArr[b] = max(computationArr[b], computationArr[b - weight[c]] + value[c]);
            }
            c++;
        }
        b++;
    }
    return computationArr[maxWt];

}

void main()
{
    

    long int W1,n1,val1[100],wt1[100];
    long int W2,n2,val2[100],wt2[100];
    long int choice;

    printf("ENTER '1' FOR IMPLEMENTATION OF UNBOUNDED KNAPSACK... \n");
    printf("ENTER '2' FOR IMPLEMENTATION OF O/1 KNAPSACK...       \n");
    scanf("%ld",&choice);

    switch(choice)
    {
        case 1:
        printf("\nEnter the total capacity 'maxWt' of the unbounded knapsack : ");
        scanf("%ld",&W1);
        printf("\nEnter the no.of items 'n' of the unbounded knapsack    : ");
        scanf("%ld",&n1);
        printf("\nEnter the values of %ld items in an array  : \n ",n1);
        for(long int i=0;i<n1;i++)
        {
            scanf("%ld",&val1[i]);
        }
        printf("\nEnter the weights for corresponding %ld items in an array  : \n ",n1);
        for(long int i=0;i<n1;i++)
        {
            scanf("%ld",&wt1[i]);
        }
        long int res1 = knapsackUnbounded(W1, val1, wt1, n1) ;
        printf("\nTHE FINAL VALUE OF UNBOUNDED KNAPSACK (TOTAL) : %ld\n\n",res1);
        break;

        case 2:
        printf("\nEnter the total capacity 'maxWt' of 0/1 knapsack : ");
        scanf("%ld",&W2);
        printf("\nEnter the no.of items 'n' of 0/1 knapsack    : ");
        scanf("%ld",&n2);
        printf("\nEnter the values of %ld items in an array  : \n ",n2);
        for(long int i=0;i<n2;i++)
        {
            scanf("%ld",&val2[i]);
        }
        printf("\nEnter the weights for corresponding %ld items in an array  : \n ",n2);
        for(long int i=0;i<n2;i++)
        {
            scanf("%ld",&wt2[i]);
        }
        long int res2 = kanpsack_0_1(W2,n2,wt2,val2) ;
        printf("\nTHE FINAL VALUE OF 0/1 KNAPSACK (TOTAL) : %ld\n\n",res2);
        break;

        default:
        printf("PLEASE ENTER THE CORRECT VALUE ");
        break;

        
    }
    
    
}

