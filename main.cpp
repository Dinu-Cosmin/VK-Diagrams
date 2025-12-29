#include "vk_table.h"

std::vector<int> create_output()
{
    std::vector<int> output;

    output = {100, 101, 110, 111, 1000};

    return output;
}

int main()
{
    output x;

    x.init({100, 101, 110, 111, 1000});
    x.print_truth();
    char numbers[] = "aa1a1aa01ab";
    std::cout << output::to_dec(numbers) << std::endl;

    return 0;
}