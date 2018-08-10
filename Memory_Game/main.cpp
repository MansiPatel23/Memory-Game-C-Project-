
#include <iostream>
#include<string>
#include <conio.h>
#include <dos.h>
#include<stdlib.h>
#include<windows.h>
#include "RandomGeneration.h"
//#include "stdafx.h"

using namespace std;

void gotoxy(short x, short y)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(hCon, pos);
}

class Game
{
	char boardDefault[5][4]; // board with @
	char boardSet[5][4]; // board with values.
	char boardCurrent[5][4]; //current values held in the board
	char cmp1, cmp2; // comparing the cell values.
	int tries; // No of attempts;
	int t1, t2; // holds the temp cell numbers
	int t3, t4; // holds the temp cell numbers
	int i;

public:
	Game()
	{
		i = 0;
		tries = 0;
	}

	void CreateBoard()
	{
		int k = 0;
		cout << "\n\n\n\n";
		cout << "\t\t";

		// Printing the column headings.

		for (int j = 0; j < 4; j++)
		{
			cout << "\t" << j;
		}
		cout << endl << endl;
		cout << "\t\t\t";

		// Underlining the column headings.
		for (int j = 0; j < 25; j++)
		{
			cout << "*";

		}
		cout << endl << endl;
		cout << "\t";

		// Filling the board with the default characters

		char row = 'A';
		for (int i = 0; i < 5; i++)
		{
			cout << "\t" << row;
			for (int j = 0; j < 4; j++)
			{
				boardDefault[i][j] = '@';
				boardCurrent[i][j] = boardDefault[i][j];
				cout << "\t" << boardDefault[i][j];
			}
			cout << endl << endl;
			cout << "\t";
			row++;
		}
	}

	void FillBoard()
	{
		char a[10];

		int randno[10];
		int rno;
		RandomGeneration *rg;
		rg = new RandomGeneration();

		rno = rg->DrawRandomNumber();
		//cout<<rno;

		for (int k = 0; k < 10; k++)
		{
			randno[k] = rno * k;
			a[k] = randno[k];

			if (a[k] == '\0')
				a[k] = '%';
			//cout<<a[k]<<endl;

		}

		//Filling the values for the board.
		//This symbol in the values gets opened when the user
		//enters the respective cell number.
		int k = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				boardSet[i][j] = a[k];
				//cout<<boardSet[i][j]<<"\t";
				if (k == 9)
					k = 0;
				else
					k++;

			}
			//cout<<endl;

		}
	}

	void ChangeCell()
	{
		int bb, cnt = 0;
		int counter = 0;
		int cell_1 = 0, cell_2 = 0;

		char cellno[2];
		char choice;
		//cout<<endl;

		do
		{
			tries = 0;
			cout << "Enter -1 to exit";
			CreateBoard();
			i = 0;
			while (true)
			{
				i++;

				//gotoxy(1,22);

				int flag = 0;
				for (int m = 0; m < 5; m++)
				{
					for (int n = 0; n < 4; n++)
					{
						if (boardCurrent[m][n] == '@')
						{
							flag = 1;
							continue;
						}
					}
				}

				if (flag == 0)
				{
					system("cls");
					gotoxy(24, 9);
					cout << " CONGRATULATION!!!!!" << endl << endl;
					gotoxy(26, 10);
					cout << "You have completed in " << tries << " Tries.";
					gotoxy(28, 13);
					cout << endl << " PLAY AGAIN (Y/N) ";
					goto bb;
				}
				else
				{
				cc: if (counter > 2)
				{
					system("cls");
					CurrentMatrix();
					counter = 0;
					cnt = 0;
					goto dd;
				}
				dd:cout << "Enter the cell number to be opened: ";
					cin >> cellno;
					counter++;
					if (strlen(cellno) > 2)
					{
						cout << "\n Enter valid cell no..";
						counter++;
						goto cc;
					}
					else
					{
						tries++;
						if (i == 3)
						{
							if (cmp1 != cmp2)
							{
								ReplaceWithDefault(t1, t2);
								boardCurrent[t1][t2] = '@';
								ReplaceWithDefault(t3, t4);
								boardCurrent[t3][t4] = '@';
								t1 = t2 = t3 = t4 = 0;
								i = 1;
							}
							else
								i = 1;
						}

						if (cellno[0] == '-' && cellno[1] == '1')
						{
							system("cls");
							gotoxy(28, 13);
							cout << endl << " PLAY AGAIN (Y/N) ";
							goto bb;
							break;
						}
						else
						{
							//cout<<cellno<<endl;

							// CONVERTING 'A','B','C','D','E' TO 0,1,2,3,4

							switch (cellno[0])
							{
							case 'A':
							case'a':
								cell_1 = 0;
								break;
							case 'B':
							case'b':
								cell_1 = 1;
								break;
							case 'C':
							case'c':
								cell_1 = 2;
								break;
							case 'D':
							case'd':
								cell_1 = 3;
								break;
							case 'E':
							case'e':
								cell_1 = 4;
								break;

							default:

								gotoxy(1, 22 + cnt);
								cout << "\nEnter valid cell no..";
								//gotoxy(1, 22 + cnt);
								counter++;
								goto cc;
								break;

							}
							//cout<<cell_1<<endl;

							// CONVERTING 'A','B','C','D' TO 0,1,2,3

							switch (cellno[1])
							{
							case '0':
								cell_2 = 0;
								break;
							case'1':
								cell_2 = 1;
								break;
							case'2':
								cell_2 = 2;
								break;
							case'3':
								cell_2 = 3;
								break;
							default:
							{
								gotoxy(1, 22 + cnt);
								cout << "\nEnter valid cell no..";
								counter++;
								goto cc;
								break;
							}

							}

							if (boardCurrent[cell_1][cell_2] != '@')
							{
								gotoxy(1, 22 + cnt);
								cout << "Cell is already open... \n";
								goto dd;
							}

							else
							{
								IdentifyLocation(cell_1, cell_2, cnt);
								if (i == 1)
								{
									cmp1 = boardSet[cell_1][cell_2];
									t1 = cell_1;
									t2 = cell_2;
								}
								if (i == 2)
								{
									cmp2 = boardSet[cell_1][cell_2];
									t3 = cell_1;
									t4 = cell_2;
								}
								cout << boardSet[cell_1][cell_2];

								//sorting the current instance of the matrix
								boardCurrent[cell_1][cell_2] = boardSet[cell_1][cell_2];
								gotoxy(1, 22 + cnt); // to go to next line
								cnt++;

							}//else for re-entry of opened cell

						} //else
					}//else for strlen(cellno)
				}//else
			}//while
		bb:cin >> choice;
			system("cls");
		} while (choice == 'Y' || choice == 'y');
	}

	void CurrentMatrix()
	{
		int i, j;

		cout << "\n\n\n\n";
		cout << "\t\t";

		for (j = 0; j < 4; j++)
		{
			cout << "\t" << j;
		}
		cout << endl << endl;
		cout << "\t\t\t";

		for (j = 0; j < 25; j++)
		{
			cout << "*";
		}
		cout << endl << endl;
		cout << "\t";
		char row = 'A';
		for (i = 0; i < 5; i++)
		{
			cout << "\t" << row;

			for (j = 0; j < 4; j++)
			{
				if (boardCurrent[i][j] != '\0')
					cout << "\t" << boardCurrent[i][j];
				else
				{
					boardCurrent[i][j] = '@';
					cout << "\t" << boardCurrent[i][j];
				}
			} // for j
			cout << "\n";
			row++;
			cout << "\n\t";
		} //for i
	}

	void IdentifyLocation(int cell_1, int cell_2, int cnt)
	{
		if (cell_1 == 0) // 'A'
		{
			switch (cell_2)
			{
			case 0:
				gotoxy(25, 9);
				break;
			case 1:
				gotoxy(33, 9);
				break;
			case 2:
				gotoxy(41, 9);
				break;
			case 3:
				gotoxy(49, 9);
				break;
			default:
			{
				gotoxy(1, 22 + cnt);
				cout << "\nEnter valid cell no";
				break;

			}
			} // if k=0, 'A'

			if (cell_1 == 1) // 'B'
			{
				switch (cell_2)
				{
				case 0:
					gotoxy(25, 11);
					break;
				case 1:
					gotoxy(33, 11);
					break;
				case 2:
					gotoxy(41, 11);
					break;
				case 3:
					gotoxy(49, 11);
					break;

				}
			} // if k=1, 'B'

			if (cell_1 == 2) // 'C'
			{
				switch (cell_2)
				{
				case 0:
					gotoxy(25, 13);
					break;
				case 1:
					gotoxy(33, 13);
					break;
				case 2:
					gotoxy(41, 13);
					break;
				case 3:
					gotoxy(49, 13);
					break;
				}
			} // if k=2, 'C'

			if (cell_1 == 3) // 'D'
			{
				switch (cell_2)
				{
				case 0:
					gotoxy(25, 15);
					break;
				case 1:
					gotoxy(33, 15);
					break;
				case 2:
					gotoxy(41, 15);
					break;
				case 3:
					gotoxy(49, 15);
					break;

				}
			} // if k=3, 'D'

			if (cell_1 == 4) // 'E'
			{
				switch (cell_2)
				{
				case 0:
					gotoxy(25, 17);
					break;
				case 1:
					gotoxy(33, 17);
					break;
				case 2:
					gotoxy(41, 17);
					break;
				case 3:
					gotoxy(49, 17);
					break;

				}
			} // if k=4, 'E'
		}
	}
		void ReplaceWithDefault(int val1, int val2)
		{
			switch (val1)
			{
			case 0:
			{
				// 'A'
				switch (val2)
				{
				case 0: gotoxy(25, 9); cout << "@"; break;
				case 1: gotoxy(33, 9); cout << "@"; break;
				case 2: gotoxy(41, 9); cout << "@"; break;
				case 3: gotoxy(49, 9); cout << "@"; break;
				default:
					break;
				}
			}
			case 1:
			{
				//'B'
				switch (val2)
				{
				case 0:
				{
					gotoxy(25, 11); cout << "@"; break;
				}
				case 1:
				{
					gotoxy(33, 11); cout << "@"; break;
				}
				case 2:
				{
					gotoxy(41, 11); cout << "@"; break;
				}
				case 3:
				{
					gotoxy(49, 11); cout << "@"; break;
				}
				}
			}

			case 2:
			{//'C'
				switch (val2)
				{
				case 0: gotoxy(25, 13); cout << "@"; break;
				case 1: gotoxy(33, 13); cout << "@"; break;
				case 2: gotoxy(41, 13); cout << "@"; break;
				case 3: gotoxy(49, 13); cout << "@"; break;
				default:
					break;
				}
			}

			case 3:
			{//'D'
				switch (val2)
				{
				case 0: gotoxy(25, 15); cout << "@"; break;
				case 1: gotoxy(33, 15); cout << "@"; break;
				case 2: gotoxy(41, 15); cout << "@"; break;
				case 3: gotoxy(49, 15); cout << "@"; break;

				default:
					break;
				}
			}
			case 4:
			{
				switch (val2)
				{
				case 0: gotoxy(25, 17); cout << "@"; break;
				case 1: gotoxy(33, 17); cout << "@"; break;
				case 2: gotoxy(41, 17); cout << "@"; break;
				case 3: gotoxy(49, 17); cout << "@"; break;
				default:
					break;
				}

			}
			}
		
		}
	
};

int main()
	{
		Game g;
		g.FillBoard(); // board with values
		g.ChangeCell();
	}