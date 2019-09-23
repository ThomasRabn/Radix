#ifndef USEFUL_H_INCLUDED
#define USEFUL_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>

#define RADIX 256
#define SORT_THRESHOLD 256

///**** COMPARE ****///
struct Compare {
    template<typename T>
        bool operator()(T* a, T* b) const { return *a < *b; }
    template<typename T>
    bool operator()(T a, T b) const { return a < b; }
};

///**** COMPARE ****///
template<typename T> bool comparePoitersValues(T* a, T* b)  { return *a < *b; }
template<typename T> bool compareValues(T a, T b)           { return a < b; }

///**** Input ****///
void openFile(std::string nom, std::vector<unsigned int>& tab);
void openFile(std::string nom, std::vector<std::string*>& tab);

///**** getByte ****///
short int getByte(unsigned int elem, unsigned int i);
short int getByte(std::string* elem, unsigned int i);

///**** getMaxLength ****///
std::size_t getMaxLength(std::vector<unsigned int>& tab);
std::size_t getMaxLength(std::vector<std::string*>& tab);


///**** Sorting ****///
/** LSD **/
template<typename T> void LSDRadixSort(std::vector<T>& tab);
/** MSD **/
template<typename T> void MSDRadixSort(std::vector<T>& tab);
template<typename T> void MSDRadixSort(std::vector<T>& tab, std::vector<T>& tabAux, int low, int high, int digit);

#endif // USEFUL_H_INCLUDED
