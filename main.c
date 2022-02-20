#include <stdio.h>
#include <stdlib.h>


#define mapsizeX 11
#define mapsizeY 11
char map[mapsizeX][mapsizeY];

void drawmap();
void initmap();
void clearmap();
void swap(int* n1, int* n2);
void handleline(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, long long int (*handle_tile)(int, int));


long long int handle_tile(int x, int y)
{
	map[x][y] = '#';
}


int main(int argc, char** argv)
{
	//if (argc < 5) return 0;

	initmap();

	int x1, y1;
	int x2, y2;

	x1 = x2 = mapsizeX/2;
	y1 = y2 = mapsizeY/2;

	char quit = 0;
	while(!quit)
	{
		drawmap();

		switch (getchar())
		{
			case 'q':
				quit = 1;
				break;

			case 'w':
				if (y1 < mapsizeY-1) y1++;
				break;

			case 's':
				if (y1 >= 1) y1--;
				break;

			case 'a':
				if (x1 >= 1) x1--;
				break;

			case 'd':
				if (x1 < mapsizeX-1) x1++;
				break;

			case '8':
				if (y2 < mapsizeY-1) y2++;
				break;

			case '2':
				if (y2 >= 1) y2--;
				break;

			case '4':
				if (x2 >= 1) x2--;
				break;

			case '6':
				if (x2 < mapsizeX-1) x2++;
		}

		clearmap();
		handleline(x1,y1, x2,y2, &handle_tile);
	}

	return 0;
}


void initmap()
{
	for (int x = 0; x < mapsizeX; ++x)
		for (int y = 0; y < mapsizeY; ++y)
			map[x][y] = '.';
}


void drawmap()
{
	for (int y = 0; y < mapsizeY; ++y)
	{
		for (int x = 0; x < mapsizeX; ++x)
			putchar(map[x][mapsizeY - y - 1]);
		putchar('\n');
	}
}


void clearmap()
{
	for (int x = 0; x < mapsizeX; ++x)
		for (int y = 0; y < mapsizeY; ++y)
			map[x][y] = '.';
}


void swap(int* n1, int* n2)
{
	int t = *n1;
	*n1 = *n2;
	*n2 = t;
}


void handleline(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, long long int (*handle_tile)(int, int))
{
	if (x1 >= mapsizeX || x2 >= mapsizeX || y1 >= mapsizeY || y2 >= mapsizeY) return;

	if (x1 == x2 && y1 == y2) goto nodir;
	else if (y1 > y2 || (y1 == y2 && x1 > x2))
	{
		swap(&x1, &x2);
		swap(&y1, &y2);
	}
	if (y1 == y2) goto E;
	else if (x1 == x2) goto N;
	else if (x1 < x2)
	{
		if ((y2-y1)/(x2-x1) < 1) goto NEE;
		else if (y2-y1 == x2-x1) goto NE;
		else goto NNE;
	}
	else
	{
		if ((y2-y1)/(x1-x2) < 1) goto NWW;
		else if (y2-y1 == x1-x2) goto NW;
		else goto NNW;
	}


int dx, dy, D;

nodir:
	handle_tile(x1,y1);				/*    HERE    */
	return;


NWW:
	dx = x1 - x2;
	dy = y2 - y1;
	D = dy * 2 - dx;
	for (int x = x2, y = y1; x <= x1; ++x)
	{
		handle_tile(x1-x+x2, y);						/*    HERE    */
		if (D > 0)
		{
			y++;
			D -= dx * 2;
		}
		D += dy * 2;
	}
	return;

NW:
	for (int x = x1, y = y1; x >= x2 && x >= 0; --x, ++y)
		handle_tile(x,y);									/*    HERE    */
	return;

NNW:
	dx = x1 - x2;
	dy = y2 - y1;
	D = dx * 2 - dy;
	for (int x = x2, y = y1; y <= y2; ++y)
	{
		handle_tile(x1-x+x2, y);						/*    HERE    */
		if (D > 0)
		{
			x++;
			D -= dy * 2;
		}
		D += dx * 2;
	}
	return;

N:
	for (int y = y1; y <= y2; ++y)
		handle_tile(x1,y);						/*    HERE    */
	return;

NNE:
	dx = x2 - x1;
	dy = y2 - y1;
	D = dx * 2 - dy;
	for (int x = x1, y = y1; y <= y2; ++y)
	{
		handle_tile(x,y);							/*    HERE    */
		if (D > 0)
		{
			x++;
			D -= dy * 2;
		}
		D += dx * 2;
	}
	return;

NE:
	for (int x = x1, y = y1; x <= x2; ++x, ++y)
		handle_tile(x,y);							/*    HERE    */
	return;

NEE:
	dx = x2 - x1;
	dy = y2 - y1;
	D = dy * 2 - dx;
	for (int x = x1, y = y1; x <= x2; ++x)
	{
		handle_tile(x,y);							/*    HERE    */
		if (D > 0)
		{
			y++;
			D -= dx * 2;
		}
		D += dy * 2;
	}
	return;


E:
	for (int x = x1; x <= x2; ++x)
		handle_tile(x,y1);					/*    HERE    */
	return;
}
