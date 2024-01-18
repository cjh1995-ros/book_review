#include <vector>
#include <iostream>
#include <utility>
#include <queue>


using loc       = std::pair<int, int>;
using locations = std::vector<loc>;

std::vector<std::vector<int>> map = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 1}
};

locations diff = {
    {-1, 0}, {1, 0}, {0, 1}, {0, -1}
};

bool is_valid_loc(int i, int j)
{
    return (i >= 0 && i < 5 && j >= 0 && j < 5);
}


bool is_rectangle(locations locs)
{}

int main()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (map[i][j] == 0)
            {
                std::queue<loc> q;
                q.push({i, j});

                while (!q.empty())
                {
                    auto l = q.front();
                    q.pop();

                    bool is_one     = false;
                    bool is_zero    = false;

                    for (auto df : diff)
                    {
                        if (is_valid_loc(l.first + df.first, l.second + df.second))
                        {
                            if (map[l.first + df.first][l.second + df.second] == 1) is_one = true;
                            else if (map[l.first + df.first][l.second + df.second] == 0) is_zero = true;
                        }
                    }

                    if (is_one && is_zero)
                    {
                        std::cout << l.first << ", " << l.second << std::endl;
                        map[l.first][l.second] = 2;
                        break;
                    }
                    else
                    {
                        for (auto df : diff)
                        {
                            if (is_valid_loc(l.first + df.first, l.second + df.second))
                                q.push({l.first + df.first, l.second + df.second});
                        }
                    }
                }
            }
        }
    }



    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            std::cout << map[i][j] << " ";
        std::cout << std::endl;
    }

}