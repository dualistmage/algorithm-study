#include <iostream>

using namespace std;

class Board {
    public: //  const
        const char BLANK = '.';
        const char FILLED = '#';

    public: // method
        int calcFreeSpace();
        int getNumOfBoardCoverCase(int x, int y);

    public: // field
        int height_;
        int width_;
        int freeSpace_;
        string block_[20];
};

int main(int argc, char* argv[])
{
	int count = 0;
    Board board;

	cin >> count;

	while (count > 0)
	{
		// read test case
		cin >> board.height_ >> board.width_;
		for (int y = 0; y < board.height_; y++)
			cin >> board.block_[y];

        if( board.calcFreeSpace() % 3 != 0 )
        {
            possibleCaseNum = 0;
        }
        else
        {
            // process
            possibleCaseNum = board.getNumOfBoardCoverCase(0, 0, 0);
        }

		// print an answer
		cout << possibleCaseNum << endl;

		count--;
	}
	return 0;
}

int Board::calcFreeSpace()
{
    int freeSpace_ = 0;
	for (int y = 0; y < height_; y++)
	{
		for (int x = 0; x < width_; x++)
		{
            if( block_[y][x] == BLANK )
                freeSpace++;
		}
	}
	return freeSpace;
}

int Board::getNumOfBoardCoverCase(int x, int y, int pattern)
{
    if( freeSpace_ == 0 )
    {
        return 1;
    }
    if( y == (height_ -1) )
    {
        return 0;
    }

    int restCoverCase = 0;
    for( int nextY = y; nextY < height_; nextY++ )
    {
        for( int nextX = x + 1; nextX < width_; nextX++ )
        {
        }
    }
}

