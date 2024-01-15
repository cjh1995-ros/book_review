#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <queue>





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





class Maze
{
private:
    int width_;
    int height_;
    std::vector<std::vector<int>> map;
    Location2D entry_;
public:
    Maze() {}
    ~Maze() {}

    void load(std::string file_path)
    {
        std::ifstream file(file_path);

        if (file.is_open())
        {
            file >> height_ >> width_;

            // resize map
            map.resize(height_, std::vector<int>(width_));

            std::string line;
            std::getline(file, line); // 첫번째 줄 읽어서 줄바꿈함.

            for (int i = 0; i < height_; i++)
            {
                std::getline(file, line);
                for (int j = 0; j < width_; j++)
                {
                    map[i][j] = std::stoi(std::string(1, line.at(j)));
                    if (map[i][j] == 5)
                    {
                        entry_.row = i;
                        entry_.col = j;
                    }
                }
                    
            }
            
            file.close();

        }
        else
        {
            std::cout << "Can't open this file" << std::endl;
        }
    }

    void print()
    {
        std::cout << "Show Map Info" << std::endl;
        std::cout << "Width: " << width_ << std::endl;
        std::cout << "Height: " << height_ << std::endl;
        

        for (int j = 0; j < height_; j++)
        {
            for (int i = 0; i < width_; i++)
            {
                if (map[j][i] == 0) std::cout << "#";
                else if (map[j][i] == 1) std::cout << " ";
                else if (map[j][i] == 2) std::cout << "*";
                else if (map[j][i] == 3) std::cout << "@";
                else if (map[j][i] == 5) std::cout << "I";
                else if (map[j][i] == 9) std::cout << "O";
            }
            std::cout << std::endl;
        }
    }

    void search_exit_queue()
    {
        std::queue<Location2D> loc;
        int count = 0;

        loc.push(entry_);

        while (!loc.empty())
        {
            Location2D here = loc.front();
            loc.pop();

            if (map[here.row][here.col] == 9)
            {
                std::cout << "End of searching!" << std::endl;
                std::cout << "Total count: " << count << std::endl;
                return;
            }
            else 
            {
                map[here.row][here.col] = 2; // 2 is marking for now.

                if (is_valid_loc({here.row - 1, here.col})) loc.push({here.row - 1, here.col});
                if (is_valid_loc({here.row + 1, here.col})) loc.push({here.row + 1, here.col});
                if (is_valid_loc({here.row, here.col - 1})) loc.push({here.row, here.col - 1});
                if (is_valid_loc({here.row, here.col + 1})) loc.push({here.row, here.col + 1});
            }
            count++;
        }

        std::cout << "Can't find goal...." << std::endl;
    }

    void search_exit_stack()
    {
        std::stack<Location2D> loc;

        loc.push(entry_);
        
        int count = 0;

        while (!loc.empty())
        {
            Location2D here = loc.top();
            loc.pop();

            if (map[here.row][here.col] == 9)
            {
                std::cout << "End of searching!" << std::endl;
                std::cout << "Total count: " << count << std::endl;
                return;
            }
            else 
            {
                map[here.row][here.col] = 2;

                if (is_valid_loc({here.row - 1, here.col})) loc.push({here.row - 1, here.col});
                if (is_valid_loc({here.row + 1, here.col})) loc.push({here.row + 1, here.col});
                if (is_valid_loc({here.row, here.col - 1})) loc.push({here.row, here.col - 1});
                if (is_valid_loc({here.row, here.col + 1})) loc.push({here.row, here.col + 1});
            }
            count++;
        }

        std::cout << "Can't find goal...." << std::endl;
    }

    bool is_valid_loc(const Location2D& p)
    {
        return (p.col > 0 && p.row > 0 && p.col < width_ && p.row < height_ && 
                map[p.row][p.col] == 1 || map[p.row][p.col] == 9) ;
    }

};






int main()
{
    Maze qmaze;
    Maze smaze;

    std::string f_path = "test.txt";

    // std::cout << "Compare Queue and Stack Result" << std::endl;

    // qmaze.load(f_path);
    // qmaze.print();

    // qmaze.search_exit_queue();
    // qmaze.print();

    std::cout << "##############################" << std::endl;

    smaze.load(f_path);
    smaze.print();

    smaze.search_exit_stack();
    smaze.print();

    return 0;
}