#include <stdio.h>

void PrintTable(int* table);

//Wave Function Collapse
struct item
{
	bool isSuperposition = true;
	int[9] posibleStates;
	int length;
}

int main()
{   
    int table[9][9] = {
    	{5,0,6, 0,0,9, 3,0,2},
    	{0,0,0, 0,6,0, 0,5,0},
    	{9,0,2, 5,0,0, 0,0,4},
    	
    	{0,4,3, 0,8,7, 0,0,5},
    	{0,0,0, 0,0,0, 0,0,0},
    	{0,9,0, 2,5,0, 0,0,0},
    	
    	{0,0,0, 3,0,0, 7,0,0},
    	{0,7,4, 0,9,1, 0,0,0},
    	{1,5,0, 0,0,6, 4,0,9}
	};

    PrintTable(table);
}


void PrintTable(int *table)
{
    printf("\t+-------+-------+-------+\n");
    for (int y = 0; y < 9; y++)
    {
        printf("\t");
        
        printf("|");
        //Print details here:)
        for (int x = 0; x < 9; x++)
        {	
        	printf(" %d", table[y * 9 + x]);
        	if ((x + 1) % 3 == 0)
        	{
        		printf(" |");
        	}
        }
        
        printf("\n");
        if ((y + 1) % 3 == 0)
        {
            printf("\t+-------+-------+-------+\n");
        }
       
    }
}

void ParseTable()
{
	//Create items for all and collapse those which are now given,
	printf("Table parsed");
}

void Collapse()
{
	
}

void Propagate()
{
	
}
