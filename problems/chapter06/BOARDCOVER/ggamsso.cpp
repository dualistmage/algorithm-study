#include <iostream>
#include <cstring>

#ifdef _DEBUG
#include <fstream>
std::ifstream debug_stream( "input.txt", std::ios_base::in );
#define input debug_stream
#else
#define input std::cin
#endif

// define data structure
struct Board_t
{
    static const int MAX_CASES = 20;
    bool data_[MAX_CASES][MAX_CASES];
    int height_;
    int width_;

    Board_t() : height_(0), width_(0)
    {
        memset(data, 0, sizeof(data));
    }
};

const int ROTATION_COUNT = 4;
const int RORATION_PAIR_COUNT = 3;
static int ROTATE_CASES[ROTATION_COUNT][RORATION_PAIR_COUNT][2] = {
    { { 0, 0 }, { 1, 0 }, { 0,  1 } },
    { { 0, 0 }, { 0, 1 }, { 1,  1 } },
    { { 0, 0 }, { 1, 0 }, { 1,  1 } },
    { { 0, 0 }, { 1, 0 }, { 1, -1 } }
};

static int count_cases(Board_t& board);
static bool find_empty_pos(Board_t& board, int& empty_y, int& empty_x);
static bool check_and_fill(Board_t& board, int start_y, int start_x, int rotate);
static void remove(Board_t& board, int start_y, int start_x, int rotate);

int main(int argc, char* argv[])
{
    int count = 0;
    input >> count;
    while (count-- > 0)
    {
        // allocate and input board (with margin)
        Board_t board;
        input >> board.height_ >> board.width_;

        // input table (skip margin)
        for (int y = 0; y < board.height_; ++y)
        {
            for (int x = 0; x < board.width_; ++x)
            {
                char marker;
                input >> marker;
                board.data_[y][x] = marker == '.';
            }
        }

        // solve problem
        int count = count_cases(board);
        std::cout << count << std::endl;
    }
    return 0;
}

static int count_cases(Board_t& board)
{
    int y = 0, x = 0;

    // when all blocks is filled, problem is solved.
    if (!find_empty_pos(board, y, x))
        return 1;

    // put, count, and remove with iterating rotatable blocks
    int count = 0;
    for (int rotate = 0; rotate < ROTATION_COUNT; ++rotate)
    {
        if (!check_and_fill(board, y, x, rotate))
            continue;

        count += count_cases(board);
        remove(board, y, x, rotate);
    }
    return count;
}

static bool find_empty_pos(Board_t& board, int& empty_y, int& empty_x)
{
    for (int y = 0; y < board.height_; ++y)
    {
        for (int x = 0; x < board.width_; ++x)
        {
            // find a start point (empty cell)
            if (board.data_[y][x])
            {
                empty_y = y;
                empty_x = x;
                return true;
            }
        }
    }
    return false;
}

template <typename _Func>
static bool work_with_rotating(Board_t& board, int y, int x, int rotate, _Func&& functor)
{
    for (int offset = 0; offset < RORATION_PAIR_COUNT; ++offset)
    {
        int rotate_y = y + ROTATE_CASES[rotate][offset][0];
        int rotate_x = x + ROTATE_CASES[rotate][offset][1];
        if (rotate_y < 0 || rotate_x < 0 || rotate_y >= board.height_ || rotate_x >= board.width_)
            return false;

        if (!functor(board, rotate_y, rotate_x))
            return false;
    }
    return true;
}

static bool check_and_fill(Board_t& board, int y, int x, int rotate)
{
    // check if fillable
    bool is_empty = work_with_rotating(board, y, x, rotate, 
        [](const Board_t& board, int y, int x) { return board.data_[y][x]; });
    if (!is_empty)
        return false;

    // fill
    return work_with_rotating(board, y, x, rotate, 
        [](Board_t& board, int y, int x) { board.data_[y][x] = false; return true; });
}

static void remove(Board_t& board, int y, int x, int rotate)
{
    work_with_rotating(board, y, x, rotate, 
        [](Board_t& board, int y, int x) { board.data_[y][x] = true; return true; });
}