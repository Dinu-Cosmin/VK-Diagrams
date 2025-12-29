#include <iostream>
#include <bitset>
#include <sstream>
#include <iterator>
#include "vk_table.h"

std::string output::to_binary(int n)

{
    if(n < 0)
    {
        return "X";
    }

    if(n == 0 | n == 1)
    {
        return std::to_string(n);
    }

    std::string binary;

    while(n > 0)
    {
        binary = char('0' + (n & 1)) + binary;
        n >>= 1;
    }

    return binary;
}

size_t output::to_dec(std::string binary)
{
    size_t dec = 0;
    size_t pos = 0;

    for(auto it = binary.rbegin(); it != binary.rend(); ++it, pos++)
    {
        if(*it == '1')
        {
            dec += 1 << pos;
        }
    }

    return dec;
}



int& output::operator[](const size_t i)
{
    return this->values.at(i);
}

const int& output::operator[](const size_t i) const
{
    return this->values.at(i);
}

void output::print_truth()
{
    if(this->values.empty())
    {
        return ;
    }

    if(this->input_len == 0)
    {
        size_t x = this->values.size();
        this->input_len = this->to_binary(this->values.size() - 1).size();
    }
    //The "input" is going to be i, while the "output" is going to be values(i).
    for(size_t i = 0; i < this->values.size(); i ++)
    {
        std::string binary(this->input_len, '0');
        std::string temp = this->to_binary(i);
        binary.replace(this->input_len - temp.size(), temp.size(), temp);
        std::cout << binary << " | ";

        temp = this->to_binary(this->values.at(i));

        //Reset binary before placing temp
        binary.replace(0, this->input_len, "0");
        
        binary.replace(this->input_len - temp.size(), temp.size(), temp);
        std::cout << binary << std::endl;
    }
}

void output::read()
{
    std::string line;
    bool is_binary = 1;

    std::cout << "Enter values for output functions: ";
    std::getline(std::cin, line);
    for(size_t i = 2; i < 10; i ++)
    {
        if(line.find(char(i + '0')) != std::string::npos)
        {
            is_binary = 0;
            break;
        }
    }

    if(is_binary)
    {
        if(line.back() != ' ')
        {
            line.push_back(' ');
        }

        while(!line.empty())
        {
            int space_pos = line.find(' ');
            std::string binary_num = line.substr(0, space_pos);
            line.replace(0, space_pos + 1, "");

            this->values.push_back(output::to_dec(binary_num));
        }

        return ;
    }


    std::istringstream ss(line);
    int x;
    while(ss >> x)
    {
        this->values.push_back(x);
    }
}
