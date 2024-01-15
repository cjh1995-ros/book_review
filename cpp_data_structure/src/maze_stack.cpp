#include <iostream>
#include <stack>
#include <vector>


struct Location2D
{
public:
    int row;
    int col;
    Location2D(int r = 0, int c = 0): row(r), col(c) {}
    Location2D(const Location2D& p)
    {
        row = p.row;
        col = p.col;
    }

    bool is_neighbor(const Location2D& p) const noexcept
    {
        return ( (row == p.row && (col == p.col - 1 || col == p.col + 1)) 
                || (col == p.col && (row == p.row - 1 || row == p.row + 1)));
    }

    bool operator==(const Location2D& p) const noexcept
    { return (row == p.row && col == p.col); }
};

constexpr int MAZE_SIZE = 6;

char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}
};

bool is_valid_loc(int r, int c)
{
    if (r >= MAZE_SIZE || r < 0 || c >= MAZE_SIZE || c < 0) return false;
    else return (map[r][c] == '0' || map[r][c] == 'x');
}

int main()
{
    std::stack<Location2D> s_loc;

    Location2D entry(1, 0);
    s_loc.push(entry);

    while (!s_loc.empty())
    {
        // 현재 위치 파악.
        Location2D here = s_loc.top();
        s_loc.pop();

        int r = here.row;
        int c = here.col;

        std::cout << "Loc now: " << r << ", " << c << std::endl;

        if (map[r][c] == 'x')
        {
            std::cout << "탐색 끝!" << std::endl;
            return 0;
        }
        else
        {
            map[r][c] = '.'; // 지나옴 표시.
            if (is_valid_loc(r-1, c)) s_loc.push({r-1, c});
            if (is_valid_loc(r+1, c)) s_loc.push({r+1, c});
            if (is_valid_loc(r, c-1)) s_loc.push({r, c-1});
            if (is_valid_loc(r, c+1)) s_loc.push({r, c+1});
        }
    }

    std::cout << "미로탐색 실패" << std::endl;

    return -1;
}