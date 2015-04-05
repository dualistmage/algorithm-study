#include <iostream>
#include <string>

using namespace std;

class Board {
public: //  const
	static const char BLANK = '.';
	static const char FILLED = '#';
	static const int MAX_PATTERN = 4;
	static const int PATTERNS[4][2][2];
	static const int MAX_LENGTH = 21;

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
	char block_[MAX_LENGTH][MAX_LENGTH];
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

		if (board.calcFreeSpace() % 3 != 0)
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
			if (block_[y][x] == BLANK)
				freeSpace_++;
		}
	}
	return freeSpace_;
}

bool Board::isFreeBlock(int x, int y)
{
	if (x < 0 || x >= width_)
		return false;
	if (y < 0 || y >= height_)
		return false;
	if (block_[y][x] == BLANK)
		return true;
	return false;
}

int Board::fillBlock(int x, int y, int pattern)
{
	int x1 = x + PATTERNS[pattern][0][0];
	int y1 = y + PATTERNS[pattern][0][1];
	int x2 = x + PATTERNS[pattern][1][0];
	int y2 = y + PATTERNS[pattern][1][1];

	if (isFreeBlock(x, y) && isFreeBlock(x1, y1) && isFreeBlock(x2, y2))
	{
		block_[y][x] = FILLED;
		block_[y1][x1] = FILLED;
		block_[y2][x2] = FILLED;
		freeSpace_ -= 3;
		//print("fill");
		return 0;
	}
	return -1;
}

int Board::pullBlock(int x, int y, int pattern)
{
	int x1 = x + PATTERNS[pattern][0][0];
	int y1 = y + PATTERNS[pattern][0][1];
	int x2 = x + PATTERNS[pattern][1][0];
	int y2 = y + PATTERNS[pattern][1][1];

	if (isFreeBlock(x, y) && isFreeBlock(x1, y1) && isFreeBlock(x2, y2))
	{
		return -1;
	}
	block_[y][x] = BLANK;
	block_[y1][x1] = BLANK;
	block_[y2][x2] = BLANK;
	freeSpace_ += 3;
	//print("pull");
	return 0;
}

int Board::getNumOfBoardCoverCase(int x, int y, int pattern)
{
	//print("init");
	if (freeSpace_ == 0)
	{
		print("solution");
		return 1;
	}
	if (y == (height_ - 1))
	{
		return 0;
	}

	int restCoverCase = 0;
	int curX;
	for (int curY = y; curY < height_; curY++)
	{
		if (y == curY)
			curX = x;
		else
			curX = 0;
		for (; curX < width_; curX++)
		{
			if (!isFreeBlock(curX, curY))
				continue;
			for (int curPattern = 0; curPattern < MAX_PATTERN; curPattern++)
			{
				if (fillBlock(curX, curY, curPattern) == -1)
				{
					cout << "====================================================== Failed : " << curX << "," << curY << "," << curPattern << endl;
					continue;
				}
				print("Filled");
	 			restCoverCase += getNumOfBoardCoverCase(curX + 1, curY, 0);
				pullBlock(curX, curY, curPattern);
				print("Pulled");
			}
		}
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
