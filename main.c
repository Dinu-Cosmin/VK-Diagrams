#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

int main() {
    bool repeat;
    repeat = false;
    bool error = true;
    //The length of the input and output arrays can be changed manually from functions.h .



    bool *input = (bool *)allocateMemory(inputLength, sizeof(bool)); //Creating input bool pointer & allocating memory
    char *output = (char *)allocateMemory(outputLength, sizeof(char)); //Creating output pointer and allocationg memory.
    char ***vk = createTables();
    unsigned int choice = 0;

    while (error) {

        error = false;
        printf("Do you want to print:\n0.Truth Table\n1.V-K Table(s)\n");
        scanf("%u", &choice);
        if (choice != 0 && choice != 1) {
            printf("Invalid option.\n");
            error = true;
        }
        else if (choice) {
            createTruthTable(input, output, 0, vk, 0);
            error = true;
            while (error) {
                error = false;
                printf("Do you want:\n0.All V-K tables\n1.A specific table\n");
                scanf("%u", &choice);
                if (choice != 0 && choice != 1) {
                    printf("Invalid option.\n");
                    error = true;
                }
                else if (choice) {
                    error = true;
                    while (error) {
                        error = false;
                        printf("Which table do you want? (1-%d): ", outputLength);
                        unsigned int tableNo;
                        scanf("%u", &tableNo);
                        if (tableNo > outputLength) {
                            printf("Invalid option.\n");
                            error = true;    
                        }
                        else {
                            printf("\n %u  │ ", tableNo);
                            printVKTable(vk[tableNo - 1]);                                       
                        }
                    
                    }

                } else {
                    for (unsigned int i = 0; i < outputLength; i ++) {
                        printf("\n %u  │ ", i+1);
                        printVKTable(vk[i]);
                    }       
                    printf("\n");     
                }                        
            }

        }
        else {
            printf("The truth table is:\n");
            printf("\n  input  │ output\n");
            for (int i = 0; i < 19; i ++) {
                printf("─");
            }
            printf("\n");  
            createTruthTable(input, output, 0, vk, 1);
            printf("\n");             
        }            
    }


        

    

    //  greyCode(input, 0);
    removePtr((void**)&input, inputLength, sizeof(bool));
    removePtr((void**)&output, outputLength, sizeof(char));
    freeTables(vk);
    error = true;
    while (error) {
        error = false;
        printf("\nRepeat? (0/1): ");
        scanf("%d", &repeat);
        if (repeat != 0 && repeat != 1) {
            printf("Invalid value.");
            error = true;
        }                 
    }
    if (repeat) {
        main();
    }
    


    return 0;
}
