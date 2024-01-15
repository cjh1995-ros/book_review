#include <iostream>
#include <vector>

std::vector<std::vector<int>> image = {
    {0,0,0,0,0,0,9,0,0,0,0,9,9,9,9,9,0,0,9,9},
    {9,9,9,9,9,0,9,0,0,0,0,0,0,0,0,9,0,0,9,9},
    {0,0,9,0,0,0,9,0,0,0,0,9,9,9,9,9,0,0,9,9},
    {0,9,9,9,0,0,9,9,9,0,0,9,0,0,0,0,0,0,9,9},
    {0,9,0,9,0,0,9,0,0,0,0,9,9,9,9,9,0,0,9,9},
    {9,9,0,9,9,0,9,0,0,0,0,0,0,0,0,0,0,0,9,9},
    {9,0,0,0,9,0,9,0,0,0,0,0,9,0,9,0,0,0,0,0},
    {9,0,0,0,9,0,9,0,0,0,0,0,9,0,9,0,0,0,9,9},
    {0,0,0,0,0,0,9,0,0,0,0,9,9,9,9,9,0,0,9,9}
};

void label_component(std::vector<std::vector<int>>& img, int x, int y, int label)
{
    if ( x < 0 || y < 0 || x >= 20 || y >= 9) return;

    if (img[y][x] == 9)
    {
        img[y][x] = label;
        label_component(img, x - 1, y, label);
        label_component(img, x + 1, y, label);
        label_component(img, x, y - 1, label);
        label_component(img, x, y + 1, label);
    }
}

void blob_coloring(std::vector<std::vector<int>>& img)
{
    int label = 1;

    for (int y = 0; y < 9; y++)
    for (int x = 0; x < 20; x++)
        if (img[y][x] == 9) label_component(img, x, y, label++);
}

void print_image(std::vector<std::vector<int>>& img)
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            if (img[y][x] == 0) std::cout << ".";
            else std::cout << img[y][x];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    print_image(image);

    blob_coloring(image);

    print_image(image);

    return 0;
}