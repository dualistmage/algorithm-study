#include <iostream>

using namespace std;

int getNumOfBoardCover(int height, int width, string* board);

int main(int argc, char* argv[])
{
	int count = 0, height, width, possibleCaseNum;
	string board[20];

	cin >> count;

	while (count > 0)
	{
		// read test case
		cin >> height >> width;
		for (int y = 0; y < height; y++)
			cin >> board[y];

		// process
		possibleCaseNum = getNumOfBoardCover(height, width, board);

		// print an answer
		cout << possibleCaseNum << endl;

		count--;
	}
	return 0;
}

int getNumOfBoardCover(int height, int width, string* board)
{
	cout << "height : " << height << endl;
	cout << "width  : " << width << endl;
	cout << "board" << endl;
	cout << "--------------------" << endl;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cout << board[y][x];
		}
		cout << endl;
	}
	cout << "--------------------" << endl;
	return 0;
}