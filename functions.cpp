#include <iostream>
#include <bitset>
#include "vk_table.h"

std::string output::to_binary(size_t n)
{
    std::string binary;

    while(n > 0)
    {
        binary = char('0' + (n & 1)) + binary;
        n >>= 1;
    }

    return binary;
}

char& output::operator[](const size_t i)
{
    return this->values.at(i);
}

const char& output::operator[](const size_t i) const
{
    return this->values.at(i);
}

void output::print_truth()
{
    if(this->values == "")
    {
        return ;
    }

    if(this->input_len == 0)
    {
        size_t x = this->values.size();
        this->input_len = this->to_binary((*this)[this->values.size() - 1] - '0').size();
    }
    //The "input" is going to be i, while the "output" is going to be values(i).
    for(size_t i = 0; i < this->values.size(); i ++)
    {
        std::string binary(this->input_len, '0');
        std::string temp = this->to_binary(i);
        binary.replace(this->input_len - temp.size(), temp.size(), temp);
        std::cout << binary << " | ";

        temp = this->to_binary((*this)[i] - '0');
        binary.replace(this->input_len - temp.size(), temp.size(), temp);
        std::cout << binary << std::endl;
    }
}
