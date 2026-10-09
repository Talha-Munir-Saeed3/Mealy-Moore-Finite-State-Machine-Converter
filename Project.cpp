#include <stdio.h>
#include <string.h>
#define MAX_STATES 100
void Mealy_Moore()
{
	printf("MEALY TO MOORE CONVERSION\n");
	printf("*************************\n\n\n");
	printf("STATES\n");
	printf("******\n");
	//cannot use 0
	int s,i,j,k;
	int flag1=0;
	int flag2=0;
    printf("Enter The Number Of States :");
    scanf("%d",&s);
    int mat[s][5];
	int count=0;
    int ar[s][2];
    int asso[s+1];
    printf("\nMEALY TABLE\n");
	printf("***********\n\n");
	printf("Enter The Mealy Machine Table\n\n"); 
    printf("State | Input 0 | Output 0 | Input 1 | Output 1\n");
    for(i=0;i<s;i++)
    {   
        for(j=0;j<5;j++)
        {
            scanf("%d",&mat[i][j]);  
        }
    }
    for(k=1;k<=s;k++)
    {
        for(i=1;i<5;i+=2)
        {
            for(j=0;j<4;j++)
            {
                if(mat[j][i]==k && mat[j][i+1]==0)
                { 
	                flag1=1; 
					asso[k]=0; 
				}
                if(mat[j][i]==k && mat[j][i+1]==1)
                { 
				    flag2=1; 
					asso[k]=1; 
				}
            }
        }       
        if(flag1==1 && flag2==1)
        {
            ar[k-1][0]=k;
            ar[k-1][1]=2;
        }
        else
        {
            ar[k-1][0]=k;
            ar[k-1][1]=1;
        }
        flag1=0; 
        flag2=0;
    }

    int sum=0;
    for(i=0;i<s;i++)
    {
        printf("%d %d\n",i+1,ar[i][1]);
        sum+=ar[i][1];
    }
        printf("\nTOTAL STATES\n");
        printf("************\n");
        printf("Total States Will Be : %d",sum);
        printf("\n\nNEW STATES\n");
        printf("**********\n");
        printf("New States : %d",sum-s);
        int mat2[sum][5],l;
        k=0;
   for(i=0;i<sum;i++)  
   {
        count=ar[mat[k][0]-1][1];
        while(count)
        {
            for(j=0,l=0;j<5;j++,l++)
            {
                mat2[i][j]=mat[k][l];
            }
            count--;
            if(count==0)
            { 
                k++;
            }
            else
			{
			    i++;
		    }
        }
   }
   for(i=0;i<sum;i++)   
   {
        for(j=1;j<5;j+=2)
        {
            if(ar[mat2[i][j]-1][1]!=1)
            {
                mat2[i][j]=(mat2[i][j]*10)+mat2[i][j+1];
            }
        }
   }
   for(i=0;i<sum;i++)  
   {
        if(ar[mat2[i][0]-1][1]!=1)
        { 
            mat2[i][0]=mat2[i][0]*10;
            i++;
            mat2[i][0]=(mat2[i][0]*10)+1;;
        }
    }
    printf("\n\nNEW MEALY TABLE\n");
    printf("***************\n\n");
    printf("The New Table\n\n");
	printf("State | Input 0 | Output 0 | Input 1 | Output 1\n"); 
    for(i=0;i<sum;i++)
    {
        printf("\n");
        for(j=0;j<5;j++)
        {
            printf("%d ",mat2[i][j]);
        }
    }
    int momat[sum][4]; 
    for(i=0;i<2;i++)
    {
        for(j=0;j<sum;j++)
        {
            momat[j][i]=mat2[j][i];
        }
    }
    for(i=3,j=0;j<sum;j++)  
    {
        momat[j][i-1]=mat2[j][i];
    }
    for(i=3,j=0;j<sum;j++)  
    {
        if(momat[j][0]>=10)
        {
		
            momat[j][i]=momat[j][0]%10;
        }
        else if(momat[j][0]<10)
        {
            momat[j][i]=asso[momat[j][0]];
        }
    }
    printf("\n\nMOORE TABLE\n");
    printf("***********\n");
    printf("The Moore Table\n\n");
    printf("State 0 1 Output\n");
    if(momat[0][3]==1)
    { 
        printf("s ");
        for(j=1;j<3;j++)
        {
            printf("%d ",momat[0][j]);
            printf("%d",0);
		}
    }
    for(i=0;i<sum;i++)
    {
        printf("\n");
        for(j=0;j<4;j++)
        {
            printf("%d ",momat[i][j]);
        }
    }
}
void Moore_Mealy()
{
	//can use 0
	int num_states,i,j;
    printf("MOORE TO MEALY CONVERSION\n");
    printf("*************************\n\n\n");
    printf("STATES\n");
    printf("******\n");
    printf("Enter The Number Of States : ");
    scanf("%d",&num_states);
    int moore_table[MAX_STATES][4];
	printf("\nMOORE TABLE\n");
	printf("***********\n\n"); 
    printf("Enter The Moore Machine Table\n\n"); 
	printf("State 0 1 Output\n");
    for(i=0;i<num_states;i++) 
	{
        for(j=0;j<4;j++) 
		{
            scanf("%d",&moore_table[i][j]);
        }
    }
    printf("\n\n\n");
    printf("MEALY MACHINE\n");
    printf("*************\n\n");
    printf("State | Input 0 | Output 0 | Input 1 | Output 1\n");
    for (i=0;i<num_states;i++) 
	{
        printf("  %d\t   %d\t      %d\t        %d\t  %d\n",moore_table[i][0], 
               moore_table[moore_table[i][1]][0],moore_table[moore_table[i][1]][3],
               moore_table[moore_table[i][2]][0],moore_table[moore_table[i][2]][3]);
    }
}
int main()
{
	int choice;
	for(;;)
	{
		printf("MENU\n");
		printf("****\n");
		printf("1-MEALY TO MOORE CONVERSION\n");
		printf("2-MOORE TO MEALY CONVERSION\n");
		printf("EXIT\n");
		printf("\nChoice : ");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("\n\n");
			Mealy_Moore();
			printf("\n\n\n");
		}
		else if(choice==2)
		{
			printf("\n\n");
			Moore_Mealy();
			printf("\n\n\n");
		}
		else
		{
			break;
		}
	}
}