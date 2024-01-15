#include <iostream>
#include <vector>


constexpr int MAZE_SIZE = 6;

std::vector<std::vector<char>> map = {
    {'1','1','1','1','1','1'},
    {'e','0','1','0','0','1'},
    {'1','0','0','0','1','1'},
    {'1','0','1','0','1','1'},
    {'1','0','1','0','0','x'},
    {'1','1','1','1','1','1'}
};


struct Location2D
{
public:
    int row;
    int col;

    Location2D(): row(0), col(0) {};
    Location2D(int r, int c): row(r), col(c) {}
    bool is_neighbor(const Location2D& p) const noexcept 
    { 
        return ((row == p.row && (col == p.col - 1 || col == p.col + 1)) ||
                (col == p.col && (row == p.row - 1 || row == p.row + 1))); 
    }
    bool operator==(const Location2D& p) const noexcept { return (row == p.row && col == p.col); }
};

bool is_valid_loc(const Location2D& p)
{
    return (p.col > 0 && p.row > 0 && p.col < MAZE_SIZE && p.row < MAZE_SIZE && 
            map[p.row][p.col] == '0' || map[p.row][p.col] == 'x');
}

Location2D ENTRY, EXIT;
bool done = false;

void search_recursive(Location2D pt)
{
    std::cout << "(" << pt.row << "," << pt.col << ")" << std::endl;
    if (done) return;
    if (pt == EXIT)
    {
        done = true;
        return;
    }
    int r = pt.row;
    int c = pt.col;
    map[r][c] = '5';

    if (is_valid_loc({r - 1, c})) search_recursive({r - 1, c});
    if (is_valid_loc({r + 1, c})) search_recursive({r + 1, c});
    if (is_valid_loc({r, c - 1})) search_recursive({r, c - 1});
    if (is_valid_loc({r, c + 1})) search_recursive({r, c + 1});
}

int main()
{
    ENTRY.row = 1;
    ENTRY.col = 0;

    EXIT.row = 4;
    EXIT.col = 5;

    search_recursive(ENTRY);

    if (done) std::cout << "출구 탐지 완료" << std::endl;
    else std::cout << "출구를 찾지 못하였습니다." << std::endl;

    for (int r = 0; r < MAZE_SIZE; r++)
    {
        for (int c = 0; c < MAZE_SIZE; c++)
            std::cout << map[r][c];
        std::cout << std::endl;
    }
}