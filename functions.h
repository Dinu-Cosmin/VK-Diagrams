#pragma once

//Modify these values for other input/output lengths
#define ROWS(inputLength) ((inputLength % 2 == 0) ? (inputLength / 2) : (inputLength / 2 + 1))
#define COLUMNS inputLength/2

#define IMPLIES(p, q) (!(p) || (q))
#define EQUIV(p, q) (((p) && (q)) || (!(p) && !(q)))

#define inputLength 5
#define outputLength 2


#include <stdbool.h>

size_t readBits(const char* );
void *allocateMemory(size_t, size_t);
void removePtr(void **, const size_t, const size_t);
void decToBin(unsigned int, const size_t, char *, char ***, const unsigned int, const unsigned int);
unsigned int binToDec(const size_t, bool *);
void createTruthTable(bool *, char *, const unsigned int, char ***, const bool);
void printVKTable (char **);
void createOutput(bool *, char *, char ***, const unsigned int, const unsigned int);
char ***createTables();
void zeros(void *, size_t,const bool);
void printPointer(const void *, const size_t);
void greyCode(bool *, const unsigned int, const size_t, const char*);
unsigned int power_of_two(const unsigned int);
unsigned int binaryToGray(unsigned int);
char *decToBinary(unsigned int, size_t, const bool);
void freeTables(char ***);
char isPrime(const unsigned int);
