#pragma once
#include <iostream>
#include <vector>

class output
{
    private:
        std::vector<int> values;
        size_t input_len;
        size_t output_len;
        int max_input_len();
        int max_output_len();
    public:
        output(std::vector<int> values_= {}, const size_t input_len_=0, const size_t output_len_=0)
            : values(std::move(values_)), input_len(input_len_), output_len(output_len_){};
        ~output(){values = {};};

        void print_truth();
        void read();
        static std::string to_binary(int);
        static size_t to_dec(std::string);
        void init(std::vector<int> (*)());
        int& operator[](const size_t);
        const int& operator[](const size_t) const;
};

class vk_table
{
    private:
        std::string *table;
    public:
        vk_table(char **table=nullptr);
        ~vk_table();

        void print();
};