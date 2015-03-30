#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

struct L
{
	std::pair<int, int> first;
	std::pair<int, int> second;
	std::pair<int, int> third;
};

void print(const std::vector<std::vector<bool> >& board);
void find(std::vector<std::vector<bool> >& board, int& x, int& y, int& totalWhite, int& answer);
std::vector<L> getLs(std::vector<std::vector<bool> >& board, int& x, int& y);
bool getNextPoint(const std::vector<std::vector<bool> >& board, const int& x, const int& y, int& nx, int& ny);

static const std::pair<std::pair<int, int>, std::pair<int, int> > MOVE[] = {
	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(1, 0), std::pair<int, int>(0, 1)),
	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(0, 1), std::pair<int, int>(-1, 0)),

	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(-1, 0), std::pair<int, int>(0, -1)),
	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(0, -1), std::pair<int, int>(1, 0)),

	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(1, 0), std::pair<int, int>(1, -1)),
	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(1, 0), std::pair<int, int>(1, 1)),

	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(0, 1), std::pair<int, int>(1, 1)),
	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(0, 1), std::pair<int, int>(-1, 1)),

	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(-1, 0), std::pair<int, int>(-1, 1)),
	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(-1, 0), std::pair<int, int>(-1, -1)),

	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(0, -1), std::pair<int, int>(-1, -1)),
	std::pair<std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(0, -1), std::pair<int, int>(1, -1))
};

int main(int args, char** argv)
{
	static const char* INPUT = "./data/input";
	static const int BUFFER_SIZE = 512;

	FILE* fp = fopen(INPUT, "r");

	if(fp == NULL)
	{
		fprintf(stderr, "Failed to read input data. FILE[%s]", INPUT);
		exit(1);
	}

	int totalTestCase = 0;
	char line[BUFFER_SIZE];
	if(fgets(line, sizeof(line), fp) != NULL)
	{
		totalTestCase = atoi(line);
	}

	for(int i = 0; i < totalTestCase; i++)
	{
		int width = 0, height = 0;

		if(fgets(line, sizeof(line), fp) != NULL)
		{
			char* token = strtok(line, " ");
			height = atoi(token);
			token = strtok(NULL, " ");
			width = atoi(token);
		}
		else
		{
			fprintf(stderr, "Failed to read input data. FILE[%s]", INPUT);
			exit(1);
		}

		int totalWhite = 0;
		std::vector<std::vector<bool> > board;

		for(size_t j = 0; j < height; j++)
		{
			if(fgets(line, sizeof(line), fp) != NULL)
			{
				std::vector<bool> row;
				for(size_t k = 0; k < width; k++)
				{
					if(line[k] == '.')
					{
						row.push_back(true);
						totalWhite++;
					}
					else
					{
						row.push_back(false);
					}
				}
				board.push_back(row);
			}
			else
			{
				fprintf(stderr, "Failed to read input data. FILE[%s]", INPUT);
				exit(1);
			}
		}

		int answer = 0;
		if(totalWhite % 3 != 0)
		{
			printf("TC%d=%d\n", i, answer);
			continue;
		}

		bool flag = false;
		for(int j = 0; j < board.size(); j++)
		{
			for(int k = 0; k < board[j].size(); k++)
			{
				if(board[j][k])
				{
					find(board, j, k, totalWhite, answer);
					flag = true;
					break;
				}
			}
			if(flag)
			{
				break;
			}
		}
		printf("TC%d=%d\n", i, answer);

		//print(board);
	}

	fclose(fp);

	return 0;
}

void print(const std::vector<std::vector<bool> >& board)
{
	for(size_t x = 0; x < board.size(); x++)
	{
		for(size_t y = 0; y < board[x].size(); y++)
		{
			printf("%d", board[x][y]);
		}
		printf("\n");
	}
}

void find(std::vector<std::vector<bool> >& board, int& x, int& y, int& totalWhite, int& answer)
{
	std::vector<L> ls = getLs(board, x, y);

	for(size_t i = 0; i < ls.size(); i++)
	{
		board[ls[i].first.first][ls[i].first.second] = board[ls[i].second.first][ls[i].second.second] = board[ls[i].third.first][ls[i].third.second] = false;
		totalWhite -= 3;

		if(totalWhite == 0)
		{
			answer++;
		}

		int nx, ny;
		if(getNextPoint(board, x, y, nx, ny))
		{
			find(board, nx, ny, totalWhite, answer);
		}

		board[ls[i].first.first][ls[i].first.second] = board[ls[i].second.first][ls[i].second.second] = board[ls[i].third.first][ls[i].third.second] = true;
		totalWhite += 3;
	}
}

std::vector<L> getLs(std::vector<std::vector<bool> >& board, int& x, int& y)
{
	std::vector<L> ls;

	if(x >= 0 && y >= 0 && x < board.size() && y < board[x].size() && board[x][y])
	{
		for(size_t i = 0; i < sizeof(MOVE) / sizeof(MOVE[0]); i++)
		{
			int fx = x + MOVE[i].first.first;
			int fy = y + MOVE[i].first.second;

			if(fx >= 0 && fy >= 0 && fx < board.size() && fy < board[fx].size() && board[fx][fy])
			{
				int sx = x + MOVE[i].second.first;
				int sy = y + MOVE[i].second.second;

				if(sx >= 0 && sy >= 0 && sx < board.size() && sy < board[sx].size() && board[sx][sy])
				{
					L l;
					l.first = std::pair<int, int>(x, y);
					l.second = std::pair<int, int>(fx, fy);
					l.third = std::pair<int, int>(sx, sy);
					ls.push_back(l);
				}
			}

		}
	}

	return ls;
}

bool getNextPoint(const std::vector<std::vector<bool> >& board, const int& x, const int& y, int& nx, int& ny)
{
	if(x + 1 == board.size())
	{
		if(y + 1 == board[x].size())
		{
			nx = ny = -1;
			return false;
		}
		else
		{
			int tx = 0;
			int ty = y + 1;
			if(board[tx][ty])
			{
				nx = tx;
				ny = ty;
				return true;
			}
			else
			{
				return getNextPoint(board, tx, ty, nx, ny);
			}
		}
	}
	else
	{
		int tx = x + 1;
		int ty = y;
		if(board[tx][ty])
		{
			nx = tx;
			ny = ty;
			return true;
		}
		else
		{
			return getNextPoint(board, tx, ty, nx, ny);
		}
	}
}
