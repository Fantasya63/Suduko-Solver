#include <stdio.h>

void PrintTable(int* table);
void ParseTable(int* table);
void Propagate(int xPos, int yPos, int value, void* items);


typedef struct
{
    int posibleStates[9];
    int length;

} Superposition;


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

	ParseTable(table);
    PrintTable(table);

    getchar(); //Not required but program exits immediately on Visual Studio without it
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


void ParseTable(int* table)
{
    Superposition items[9][9];
    int superPositionsLeft = 81;

	//Create items for all and collapse those which are now given,
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            //read the table
            int value = table[y * 9 + x];
            
            if (value != 0)
            {
                superPositionsLeft -= 1;
                Propagate(x, y, value, items);
                continue;
            }

            //set superposition defaults
            items[x][y].length = 9;

            //Dirty?
            for (int i = 0; i < 9; i++)
            {
                items[x][y].posibleStates[i] = i;
            }
        }
    }
    printf("Number of superpositions left: %d\n", superPositionsLeft);
}


void Collapse()
{
	
}


void _PropagateBox(int xPos, int yPos, int value, Superposition* items)
{
    //get box id
    int xBox = xPos / 3;
    int yBox = yPos / 3;

    //Get components in the box,
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            int xPos = x + xBox;
            int yPos = y + yBox;

            //Get Item
            Superposition* item = items + yPos * 9 + xPos;

            for (int i = 0; i < item->length; i++)
            {
                if (item->posibleStates[i] == value)
                {
                    item->posibleStates[i] = -1; // -1 means invalid
                    item->length -= 1;
                    break;
                }
            }
        }
    }
    //Update each component's possible states
}


void _PropagateRow(int yPos, int value, Superposition* items)
{
    for (int x = 0; x < 9; x++)
    {
        Superposition* item = items + yPos * 9 + x;

        for (int i = 0; i < item->length; i++)
        {
            if (item->posibleStates[i] == value)
            {
                item->posibleStates[i] = -1; // -1 means invalid
                item->length -= 1;
                break;
            }
        }
    }
}


void _PropagateColumn(int xPos, int value, Superposition* items)
{
    for (int y = 0; y < 9; y++)
    {
        Superposition* item = items + y * 9 + xPos;

        for (int i = 0; i < item->length; i++)
        {
            if (item->posibleStates[i] == value)
            {
                item->posibleStates[i] = -1; // -1 means invalid
                item->length -= 1;
                break;
            }
        }
    }
}


void Propagate(int xPos, int yPos, int value, Superposition* items)
{
    _PropagateBox(xPos, yPos, value, items);
    _PropagateRow(yPos, value, items);
    _PropagateColumn(xPos, value, items);
}
