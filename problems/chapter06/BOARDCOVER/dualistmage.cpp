#include <iostream>

using namespace std;

class Board {
    public: //  const
        static const char BLANK = '.';
        static const char FILLED = '#';
        static const int MAX_PATTERN = 4;
        static const int PATTERNS[4][2][2];

    public: // method
        int calcFreeSpace();
        bool isFreeBlock(int x, int y);
        int fillBlock(int x, int y, int pattern);
        int pullBlock(int x, int y, int pattern);
        int getNumOfBoardCoverCase(int x, int y, int pattern);
        void print(char* msg);

    public: // field
        int height_;
        int width_;
        int freeSpace_;
        string block_[20];
};

const int Board::PATTERNS[4][2][2] = {
    { { 1, 0 }, { 0, 1 } },
    { { 1, 0 }, { 1, 1 } },
    { { 0, 1 }, { 1, 1 } },
    { { -1, 1 }, { 0, 1 } },
};

int main(int argc, char* argv[])
{
	int count = 0, possibleCaseNum;
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
    freeSpace_ = 0;
	for (int y = 0; y < height_; y++)
	{
		for (int x = 0; x < width_; x++)
		{
            if( block_[y][x] == BLANK )
                freeSpace_++;
		}
	}
	return freeSpace_;
}

bool Board::isFreeBlock(int x, int y)
{
    if( x < 0 || x >= width_ )
        return false;
    if( y < 0 || y >= height_ )
        return false;
    if( block_[y][x] == BLANK )
        return true;
    return false;
}

int Board::fillBlock(int x, int y, int pattern)
{
    int x1 = PATTERNS[pattern][0][0];
    int y1 = PATTERNS[pattern][0][1];
    int x2 = PATTERNS[pattern][1][0];
    int y2 = PATTERNS[pattern][1][1];

    if( isFreeBlock(x, y) && isFreeBlock(x1, y1) && isFreeBlock(x2, y2) )
    {
        block_[y][x] = FILLED;
        block_[y1][x1] = FILLED;
        block_[y2][x2] = FILLED;
        freeSpace_ -= 3;
        return 0;
    }
    return -1;
}

int Board::pullBlock(int x, int y, int pattern)
{
    int x1 = PATTERNS[pattern][0][0];
    int y1 = PATTERNS[pattern][0][1];
    int x2 = PATTERNS[pattern][1][0];
    int y2 = PATTERNS[pattern][1][1];

    if( isFreeBlock(x, y) && isFreeBlock(x1, y1) && isFreeBlock(x2, y2) )
    {
        return -1;
    }
    block_[y][x] = BLANK;
    block_[y1][x1] = BLANK;
    block_[y2][x2] = BLANK;
    freeSpace_ += 3;
    return 0;
}

int Board::getNumOfBoardCoverCase(int x, int y, int pattern)
{
    print("init");
    if( freeSpace_ == 0 )
    {
        return 1;
    }
    if( y == (height_ - 1) )
    {
        return 0;
    }

    int restCoverCase = 0;
    for( int nextPattern = pattern; nextPattern< MAX_PATTERN; nextPattern++ )
    {
        print("fill");
        if( fillBlock(x, y, nextPattern) == -1 )
            continue;
        print("recursive");
        for( int nextY = y; nextY < height_; nextY++ )
        {
            for( int nextX = x + 1; nextX < width_; nextX++ )
            {
                restCoverCase += getNumOfBoardCoverCase(nextX, nextY, 0);
            }
        }
        pullBlock(x, y, nextPattern);
        print("pull");
    }
    return restCoverCase;
}

void Board::print(char* message) {
    cout << "Block Info - " << message << endl;
    cout << "-------------------------------------------" << endl;
    cout << "width : " << width_ << " / height : " << height_ << " / freeSpace : " << freeSpace_ << endl;
    cout << "-------------------------------------------" << endl;
	for (int y = 0; y < height_; y++)
	{
        cout << block_[y] << endl;
	}
    cout << "-------------------------------------------" << endl;
}

