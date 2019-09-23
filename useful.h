#ifndef USEFUL_H_INCLUDED
#define USEFUL_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <thread>
#include <exception>


///**** COMPARE ****///
struct Compare {
    template<typename T>
        bool operator()(T* a, T* b) const { return *a < *b; }
    template<typename T>
        bool operator()(T a, T b) const { return a < b; }
};

///**** COMPARE ****///
template<typename T> inline bool compareValues(T* a, T* b)      { return *a < *b; }
template<typename T> inline bool compareValues(T a, T b)        { return a < b; }

    /// Verify if an array given as parameter is sorted, send an exception if not
template<typename T> inline int verify(T tab) {
    try{
        for (unsigned int i = 1; i < tab.size(); i++) {
            if (compareValues(tab[i], tab[i-1])) {
                throw std::exception();
            }
        }
    }
    catch(std::exception ex) {
        std::cerr << "ERROR : The array isn't well sorted" << std::endl;
        return 1;
    }
    return 0;
}

///**** Input ****///
void openFile(std::string nom, std::vector<unsigned int>& tab);
void openFile(std::string nom, std::vector<std::string*>& tab);

///**** getByte ****///
short int getByte(unsigned int elem, unsigned int i);
short int getByte(std::string* elem, unsigned int i);

///**** getMaxLength ****///
std::size_t getMaxLength(std::vector<unsigned int>& tab);
std::size_t getMaxLength(std::vector<std::string*>& tab);

///**** Printing ****///
void inline print(std::vector<unsigned int> arr) {
    for(const auto& elem : arr) {
            std::cout << elem << std::endl;
        }
}

void inline print(std::vector<std::string*> arr) {
    for(const auto& elem : arr) {
            std::cout << *elem << std::endl;
        }
}

///**** Sorting ****///
/** LSD **/
template<typename T> void LSDRadixSort(std::vector<T>& tab);
/** MSD **/
template<typename T> void MSDRadixSort(std::vector<T>& tab);
template<typename T> void MSDRadixSort(std::vector<T>& tab, std::vector<T>& tabAux, int low, int high, int digit);

#endif // USEFUL_H_INCLUDED
