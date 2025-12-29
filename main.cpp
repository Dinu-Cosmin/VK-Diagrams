#include "vk_table.h"

int main()
{
    output x({0, 1, 1, 0, 0});

    x.print_truth();

    x.read();
    x.print_truth();
    return 0;
}