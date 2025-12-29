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

int output::max_input_len()
{
    if(this->values.empty())
    {
        std::cout << "called max_input_len() on empty vector" << std::endl;
        return -1;
    }

    size_t size_in_bits = output::to_binary(this->values.size() - 1).size();
    this->input_len = size_in_bits;
    return 0;
}

int output::max_output_len()
{
    if(this->values.empty())
    {
        std::cout << "called max_output_len() on empty vector." << std::endl;
        return -1;
    }

    size_t maximum_element = this->values.front();

    for(size_t i = 1; i < this->values.size(); i ++)
    {
        if(this->values.at(i) > maximum_element)
        {
            maximum_element = this->values.at(i);
        }
    }
    this->output_len = output::to_binary(maximum_element).size();
    return 0;
}

void output::print_truth()
{
    if(this->values.empty())
    {
        return ;
    }

    if(this->input_len == 0)
    {
        int x = this->max_input_len();
        if(x == -1)
        {
            return;
        }
    }
    if(this->output_len == 0)
    {
        int x = this->max_output_len();
        if(x == -1)
        {
            return;
        }
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
        binary.clear();
        binary.insert(binary.begin(), this->output_len, '0');

        binary.replace(this->output_len - temp.size(), temp.size(), temp);
        std::cout << binary << std::endl;
    }
}

void output::read()
{
    if(!this->values.empty())
    {
        this->values.clear();
        this->input_len = 0;
        this->output_len = 0;
    }
    
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

void output::init(std::vector<int> (*foo)())
{
    std::vector<int> temp = foo();

    if(temp.empty())
    {
        std::cout << "[warning]: the vector provided is empty. Do you wish to proceed with the assignment? [y/n]: ";
        char option;
        std::cin >> option;

        if(option == 'n' || option == 'N')
        {
            std::cout << "Assignment will not procceed: User entered 'n'." << std::endl;
            return ;
        }
        else if(option != 'y' && option != 'Y')
        {
            std::cout << "Assignment will not proceed: User entered invalid character: '" << option << "'." << std::endl;
            return ;
        }
    }
    
    bool is_binary = true;
    
    for(size_t i = 0; i < temp.size(); i ++)
    {
        if(temp.at(i) < 0)
        {
            std::cout << "[fatal]: negative number [" << temp.at(i) << "] found at position " << i << ".";
            std::cout << std::endl;
            std::cout << "         assignment failed: only introduce positive values." << std::endl;
            return;
        }
        std::string number = std::to_string(temp.at(i));
        for(size_t j = 2; j < 10; j ++)
        {
            if(number.find(char(j + '0')) != std::string::npos)
            {
                is_binary = false;
            }
        }
    }

    if(is_binary)
    {
        std::cout << "[warning]: values appear to be binary. Would you like to store them as binary numbers? [y/n]: ";
        char option;
        std::cin >> option;

        switch(option)
        {
            case 'n':
            case 'N':
                std::cout << "Values will be stored as ints." << std::endl;
                this->values = temp;
                return;
            case 'y':
            case 'Y':
                std::cout << "Values will be treated as binary numbers." << std::endl;
                for(size_t i = 0; i < temp.size(); i ++)
                {
                    temp.at(i) = output::to_dec(std::to_string(temp.at(i)));
                }
                this->values = temp;
                return;
            default:
                std::cout << "Invalid option entered: [" << option << "]." << std::endl;
                return;
        }
    }

    this->values = temp;
} 