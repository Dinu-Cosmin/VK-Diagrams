#include "vk_table.h"

std::vector<int> create_output()
{
    std::vector<int> output;

    output = {100, -101, 110, 111, 1000};

    return output;
}

int main()
{
    output x;

    x.init(create_output);
    x.print_truth();

    return 0;
}