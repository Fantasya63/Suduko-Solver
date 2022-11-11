#include <stdio.h>

#define true 1
#define false 0

typedef int bool;

typedef struct
{
    int posibleStates[9];
    int length;
    bool isCollapsed;
} Superposition;


void PrintTable(int table[9][9]);
void ParseTable(int table[9][9]);
void Propagate(int xPos, int yPos, int value, Superposition items[9][9]);
void Collapse(int xPos, int yPos, int value, Superposition items[9][9], int table[9][9]);

// TODO: Use linked lists to avoid looping through all 81 items
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


void InitSuperpositions(Superposition items[9][9])
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            Superposition* item = &items[y][x];
            item->length = 9;
            item->isCollapsed = 0;

            //Dirty?
            for (int i = 0; i < 9; i++)
            {
                items[y][x].posibleStates[i] = i + 1;
            }
        }
    }
}


void PrintTable(int table[9][9])
{
    printf("\t+-------+-------+-------+\n");
    for (int y = 0; y < 9; y++)
    {
        printf("\t");
        
        printf("|");
        //Print details here:)
        for (int x = 0; x < 9; x++)
        {	
        	printf(" %d", table[y][x]);
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


void ParseTable(int table[9][9])
{
    Superposition items[9][9];
    int numSuperpositionsLeft = 81;

    InitSuperpositions(items);

	//Find and collapse those which are now given,
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            //read the table
            int value = table[y][x];
            
            if (value != 0)
            {
                // TODO: Refactor to avoid setting values twice during init and propagate
                Collapse(x, y, value, items, table);
                Propagate(x, y, value, items);
                numSuperpositionsLeft -= 1;
            }
        }
    }

    //Wave Function Collapse
    while (numSuperpositionsLeft > 0)
    {
        //pick the one with smallest possible states
        int minState = 100;
        int minX = 0, minY = 0;

        for (int y = 0; y < 9; y++)
        {
            for (int x = 0; x < 9; x++)
            {
                Superposition* item = &items[y][x];

                if (item->isCollapsed)
                    continue;

                if (minState > item->length)
                {
                    minState = item->length;
                    minX = x;
                    minY = y;
                }
            }
        }

        int value = 0;
        //Pick a state to collapse to
        for (int i = 0; i < 9; i++)
        {
            Superposition* item = &items[minY][minX];

            if (item->posibleStates[i] == 0)
                continue;

            value = i + 1;
        }

        Collapse(minX, minY, value, items, table);
        Propagate(minX, minY, value, items);
        numSuperpositionsLeft -= 1;
    }
}


void Collapse(int xPos, int yPos, int value, Superposition items[9][9], int table[9][9])
{
    Superposition* item = &items[yPos][xPos];
    if (item->isCollapsed)
        return;

    item->length = 1000;
    item->posibleStates[value - 1] = 0;
    item->isCollapsed = 1;

    table[yPos][xPos] = value;
}


void _PropagateBox(int xPos, int yPos, int value, Superposition items[9][9])
{
    //get box id
    int xBox = xPos / 3;
    int yBox = yPos / 3;

    //Get components in the box,
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            int xPos = x + xBox * 3;
            int yPos = y + yBox * 3;

            //Get Item
            Superposition* item = &items[yPos][xPos];
            if (item->isCollapsed)
                continue;

            if (item->posibleStates[value - 1] == value)
            {
                item->posibleStates[value - 1] = 0;
                item->length -= 1;
            }
        }
    }
    //Update each component's possible states
}


void _PropagateRow(int yPos, int value, Superposition items[9][9])
{
    for (int x = 0; x < 9; x++)
    {
        Superposition* item = &items[yPos][x];

        if (item->isCollapsed)
            continue;

        if (item->posibleStates[value - 1] == value)
        {
            item->posibleStates[value - 1] = 0;
            item->length -= 1;
        }
    }
}


void _PropagateColumn(int xPos, int value, Superposition items[9][9])
{
    for (int y = 0; y < 9; y++)
    {
        Superposition* item = &items[y][xPos];

        if (item->isCollapsed)
            continue;

        if (item->posibleStates[value - 1] == value)
        {
            item->posibleStates[value - 1] = 0;
            item->length -= 1;
        }
    }
}


void Propagate(int xPos, int yPos, int value, Superposition items[9][9])
{
    _PropagateBox(xPos, yPos, value, items);
    _PropagateRow(yPos, value, items);
    _PropagateColumn(xPos, value, items);
}
