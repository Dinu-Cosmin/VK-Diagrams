#pragma once
#include <iostream>

class output
{
    private:
        std::string values;
        size_t input_len;
        size_t output_len;
    public:
        output(std::string values_= "", const size_t input_len_=0, const size_t output_len_=0)
            : values(std::move(values_)), input_len(input_len_), output_len(output_len){};
        ~output(){values = "";};

        void print_truth();
        void read();
        std::string to_binary(size_t n);
        void init(void (*)());
        char& operator[](const size_t);
        const char& operator[](const size_t) const;
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