#include <vector>
#include <queue>
#include <utility>
#include <iostream>



std::vector<std::vector<int>> map = {
    {1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1},
    {1, 1, 0, 0, 1},
    {0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0}
};

bool is_valid_loc(int i, int j)
{
    return (i >= 0 && i < 5 && j >= 0 && j < 5 );   // in matrix?

    // return ((i >= 0 && i < 5 && j >= 0 && j < 5 )||   // in matrix?
    //         map[i][j] == 0 ||                       // basic constraints => 0이면 갈 수 있고, 1 이면 못가는 곳.
    //         map[i][j] == 2 || map[i][j] == 3);      // 2는 거리가 1인 0. 3은 거리가 2인 0.
}

// && map[i][j] != 1

std::vector<std::vector<int>> neighbor = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

int main()
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (map[i][j] == 0)
            {
                std::cout << "Zero Loc now: ";
                std::cout << i << ", " << j << " " << std::endl;
                
                std::queue<std::pair<std::pair<int, int>, int>> q;
                q.push({{i, j}, 0});

                while (!q.empty())
                {
                    auto loc = q.front();
                    q.pop();

                    std::pair<int, int> location = loc.first;
                    int count = loc.second;

                    bool is_one = false;

                    for (auto n_diff : neighbor)
                    {
                        int neighbor_i = location.first + n_diff[0];
                        int neighbor_j = location.second + n_diff[1];

                        std::cout << "Neighbors: ";
                        std::cout << neighbor_i << ", " << neighbor_j << " " << std::endl;


                        if (is_valid_loc(neighbor_i, neighbor_j))
                        {
                            if (map[neighbor_i][neighbor_j] == 1) is_one = true;
                        }
                    }

                    if (is_one)
                    {
                        map[i][j] = count + 2;
                        std::cout << "There is one: " << map[i][j] << std::endl;
                        break;
                    }
                    else
                    {
                        if (is_valid_loc(location.first - 1, location.second)) q.push({{location.first - 1, location.second}, count + 3});
                        if (is_valid_loc(location.first + 1, location.second)) q.push({{location.first - 1, location.second}, count + 3});
                        if (is_valid_loc(location.first, location.second - 1)) q.push({{location.first, location.second - 1}, count + 3});
                        if (is_valid_loc(location.first, location.second + 1)) q.push({{location.first, location.second + 1}, count + 3});
                    }
                }
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}