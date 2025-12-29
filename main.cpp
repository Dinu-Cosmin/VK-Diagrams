#include "vk_table.h"

int main()
{
    output x({0, 1, 1, 0});

    x.print_truth();

    output y;
    y.read();
    y.print_truth();
    return 0;
}