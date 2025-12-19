#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

size_t readBits(const char* bitType) {
    bool error = true;
    size_t bits = 0;

    while (error) {//Reading number of bits
        error = false;
        printf("Introduce number of %s bits: ", &bitType);
        scanf("%zu", &bits);
        if (bits == 0) {
            printf("Number of bits must be greater than 0.\n");
            error = true;
        }
        if (bits > 100) {
            printf("Number of bits exceeds limit or is negative.\n");
            error = true;
        }
    }

    return bits;
}

void *allocateMemory(const size_t elementCount,const size_t elementSize) {
    void *ptr = malloc(elementCount * elementSize);

    if (ptr == 0) {
        fprintf(stderr, "\nINSUFFICIENT MEMORY\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void removePtr(void **ptr, const size_t elementCount, const size_t elementSize) {
    if (*ptr != NULL){
        memset(*ptr, 0, elementCount * elementSize);
        free(*ptr);
        *ptr = NULL;        
    }

}

unsigned int binToDec(const size_t length, bool *input) {
    unsigned int num = 0;
    for (size_t i = 0; i < length; i ++) {
        //Bitwise shifting and OR. It takes num, moves all bits to the left by one, making room for a new bit and it places it there by doin | with input[i]
        num = (num << 1) | input[i];
    }

    return num;
}

void decToBin(unsigned int num, const size_t length, char *output,  char ***VK, const unsigned int row, const unsigned int column) {
    for (size_t i = 0; i < length; i ++) {

        //Calculate 2^(length-1-i) as "term"          
        unsigned int term = 1 << (length-1-i);;
        //If the number is term, add 1 on the coressponding position and end loop
        if (num - term == 0) {
            output[i] = '1';
            VK[i][row][column] = output[i];
            break;
        }
        //If term can be subtracted, add 1 on the corresponding position and continue the loop
        else if ((int)(num - term) > 0) {
            output[i] = '1';
            num -= term;
        }
        //If term cannot be subtracted, add 0 on the corresponding position and continue the loop
        else {
            output[i] = '0';
        }
        VK[i][row][column] = output[i];
    }
}

void createTruthTable(bool *input, char *output, const unsigned int iteration, char ***VK, const bool print){
    if (iteration == inputLength - 1) {
        for (unsigned int i = 0; i < 2; i ++) {
            input[iteration] += i;
            createOutput(input, output, VK, binToDec(ROWS(inputLength), input+COLUMNS), binToDec((int)COLUMNS, input));

            if(print) {
                printPointer(input,inputLength);
                printf("│ ");
                printPointer(output, outputLength);
                printf("│\n");
                for (int i = 0; i < 19; i ++) {
                    printf("─");
                }
                printf("\n");                
            }


            //Reset array items before next iteration
            input[iteration] = 0;
            zeros(output, outputLength, true);
        }

    }
    else {
        for (unsigned int i = 0; i < 2; i ++) {
            input[iteration] += i;
            createTruthTable(input, output, iteration+1, VK, print);
            input[iteration] = 0;
        } 
    }
}

void createOutput(bool *input, char *output, char ***VK, const unsigned int row, const unsigned int column){
    //Some cases I met. If you want one, move the code outside of predefinedCases() and uncomment it. predefinedCases() IS NOT a real function.
    //It's there just so you can hide the cases if you want something unique.

    /*predefinedCases(){
        For the case where you want to multiply the first 2 input bits by the last 3 input bits, this is the createOutput function:

            unsigned int a = binToDec(2, input);
            unsigned int b = binToDec(3, input+2);
            a = a * b;
            decToBin(a, outputLength, output, VK, row, column);

        For the case where you have one output bit which is 1 if the input is prime:
            output[0] = isPrime(binToDec(inputLength, input));
            VK[0][row][column] = output[0];     

        For the case where the output is the input encoded in grey code:
            const unsigned int num = binaryToGray(binToDec(inputLength, input));
            char *binary = decToBinary(num, outputLength, 0);

            for (unsigned int i = 0; i < outputLength; i ++) {
                output[i] = binary[i];
                VK[i][row][column] = output[i];
            }
        Circuit that takes first 2 bits as a selection. For 00, it outputs '-', for 01 it does 3*(the other 3 bits), for 10 it outputs the last 3 bits and for 11 it does 2*(the last 3 bits):
            switch (binToDec(2, input)){
                    case 0:
                        for(size_t  i = 0; i < outputLength; i ++) {
                            output[i] = '-';
                            VK[i][row][column] = output[i];
                        }
                        break;
                    case 1:
                        decToBin(3*binToDec(3, input+2), outputLength, output, VK, row, column);
                        break;
                    case 2:
                        output[0] = '0';
                        VK[0][row][column] = '0';
                        for(size_t i = 1; i < outputLength; i ++) {
                            output[i] = input[1+i] + '0';
                            VK[i][row][column] = output[i];
                        }
                        break;
                    case 3:
                        decToBin(2*binToDec(3, input+2), outputLength, output, VK, row, column);
                        break;
   }

    }*/

    // bool a = input[0];
    // bool b = input[1];
    // bool c;
    // switch((int)a) {
    //     case 0:
    //         switch((int)b) {
    //             case 0:
    //                 c = (IMPLIES(input[2], input[3]) ^ a);
    //                 break;
    //             case 1:
    //                 c = (EQUIV(a, b) & (input[2] | input[3]));
    //                 break;
    //             default:
    //                 break;
    //         }
    //         break;
    //     case 1:
    //         switch ((int)b)
    //         {
    //         case 0:
    //             c = (IMPLIES(!(a & input[2]), input[3]));
    //             break;
    //         case 1:
    //             c = EQUIV((b ^ input[2]), (input[3] & a));
    //             break;
    //         default:
    //             break;
    //         }
    // }

    // output[0] = c + '0';

    unsigned int a = binToDec(2, input);
    unsigned int b = binToDec(3, input+2);
    a = a * b;
    decToBin(a, outputLength, output, VK, row, column);


}

void zeros(void *pointer, const size_t length,const bool isCharArray) {
    if (pointer == NULL) return;
    //If the flag isCharArray is 1, set all to '0'. Else, set to 0
    if (isCharArray) {
        memset(pointer, '0', length);
    }
    else {
        memset(pointer, 0, length);
    }
}

void printPointer(const void *pointer, const size_t length) {

    //If const void *pointer is a bool pointer, treat it as such.
    if (((const unsigned char *)pointer)[0] == false || ((const unsigned char *)pointer)[0] == true) {
        const bool *boolPointer = (const bool *)pointer;
        for (size_t i = 0; i < length - 1; i ++) {
            printf("%d ", boolPointer[i]);
        }
        printf("%d", boolPointer[length - 1]);
    }
    //Else, treat it as char pointer. 
    else {
        const char *charPointer = (const char *)pointer;
        for (size_t i = 0; i < length - 1; i ++) {
            printf("%c ", charPointer[i]);
        }
        printf("%c", charPointer[length - 1]);
    }
}

void greyCode(bool *input, const unsigned int iteration, const size_t length,const char *type) {
    if (type == "collumn") {
        if (iteration == length - 1) {
            printPointer(input, length);
            input[iteration] = !input[iteration];
            printPointer(input, length);
        }else {
            greyCode(input, iteration + 1, length, type);
            input[iteration] = !input[iteration];
            greyCode(input, iteration + 1, length, type);
        }        
    }

}

char ***createTables() {
    char ***tables =(char ***)malloc(outputLength * sizeof(char **));
    if (tables == 0) {
        fprintf(stderr, "INSUFFICIENT MEMORY");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < outputLength; i ++) {
        //For n bits, we will have 2^n possible combinations. Thus, 2^n rows and 2^n columns
        tables[i] =(char **)malloc(power_of_two(ROWS(inputLength)) * sizeof(char *));
        if (tables[i] == 0) {
            fprintf(stderr, "INSUFFICIENT MEMORY");
            exit(EXIT_FAILURE);
        }
        for (unsigned int j = 0; j < power_of_two(ROWS(inputLength)); j ++) {
            tables[i][j] =(char *)allocateMemory(power_of_two(COLUMNS), sizeof(char));
            zeros(tables[i][j], power_of_two(COLUMNS), true);

        }
    }

    return tables;
}

void freeTables(char ***tables) {
    for (unsigned int i = 0; i < outputLength; i ++) {
        for(unsigned int j = 0; j < ROWS(inputLength); j ++) {
            memset(tables[i][j], 0, COLUMNS * sizeof(char));
            free(tables[i][j]);
            tables[i][j] = NULL;
        }
        free(tables[i]);
        tables[i] = NULL;
    }
    free(tables);
    tables = NULL;
}

unsigned int power_of_two(const unsigned int n) {
    return 1 << n;
}

void printVKTable(char **table) {
    //As previously stated, we have 2^n columns and 2^n rows
    unsigned int columns = power_of_two(COLUMNS);
    unsigned int rows = power_of_two(ROWS(inputLength));
    for (unsigned i = 0; i < columns; i ++) {
        //Turn index i to its gray code counter part, then to binary and print
        decToBinary(binaryToGray(i), (int)COLUMNS, true);
        printf(" │ ");
    }
    printf("\n");
    for (int i = 0; i < 25 * power_of_two(COLUMNS - 2); i ++) {
        printf("─");
    }
    printf("\n");
    for (unsigned int i = 0; i < rows; i ++) {
        //Turn index i to its gray code counter part, then to binary and print
        decToBinary(binaryToGray(i), ROWS(inputLength), true);
        printf(" │  ");
        for (unsigned int j = 0; j < columns; j ++){
            //Print element coressponding to the gray code versions of i and j
            printf("%c", table[binaryToGray(i)][binaryToGray(j)]);
            for (int i = 0; i < COLUMNS - 1; i ++) {
                printf (" ");
            }
            printf("│  ");
            
        }
        printf("\n");
        for (int i = 0; i < 25 * power_of_two(COLUMNS - 2); i ++) {
            printf("─");
        }
        printf("\n");
    }
}

unsigned int binaryToGray(unsigned int num) {
    return num ^ (num >> 1);
}

char *decToBinary(unsigned int num, size_t length, const bool print) {
    char *binary = (char *)allocateMemory(length, sizeof(char));
    zeros(binary, length, true);
    //Creates pointer the size of the max number of bits to hold the binary number

    if (num == 0) {
        //In case we get 0, we simplify and end it here
        if(print) {
            for (unsigned int i = 0; i < length; i ++){
                printf("0");
            }
        }
        return binary;
    }
    unsigned int j = length - 1;
    while (num) {
        //Divide the number by 2 and keep remainders in binary[i]
        binary[j] = '0' + (num % 2);
        num /= 2;
        j --;
    }

    if (print){
        for (unsigned int i = 0; i < length; i ++) {
            //Print binary number in reverse order
            printf("%c", binary[i]);
        } 
    }

    return binary;

}

char isPrime(const unsigned int x) {
    if (x == 2) {
        return '1';
    }
    if(x % 2 == 0 || x == 0 || x == 1) {
        return '0';
    }
    for(unsigned int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            return '0';
        }
    }
    return '1';
}