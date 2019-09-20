#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <type_traits>
#include <algorithm>

#define RADIX 255


///**** Input ****///
void openFile(std::string nom, std::vector<std::string*>& tab);
void openFile(std::string nom, std::vector<std::string>& tab);
void openFile(std::string nom, std::vector<unsigned int>& tab);
void openFile(std::string nom, std::vector<unsigned int*>& tab);

///**** getByte ****///
short int getByte(unsigned int elem, unsigned int i);
short int getByte(std::string elem, unsigned int i);
/*int get4bits(unsigned int elem, unsigned int i);
int get2bytes(unsigned int elem, unsigned int i);*/

///**** getMaxLength ****///
std::size_t getMaxLength(std::vector<unsigned int>& tab);
std::size_t getMaxLength(std::vector<unsigned int*>& tab);
std::size_t getMaxLength(std::vector<std::string*>& tab);
std::size_t getMaxLength(std::vector<std::string>& tab);

///**** Sorting ****///
/** LSD **/
template<typename T> void LSDRadixSort(std::vector<T*>& tab);
template<typename T> void LSDRadixSort(std::vector<T>& tab);
/** MSD **/
template<typename T> void MSDRadixSort(std::vector<T*>& tab);
template<typename T> void MSDRadixSort(std::vector<T>& tab);
template<typename T> void MSDRadixSort(std::vector<T*>& tab, std::vector<T*>& tabAux, int low, int high, int digit);
template<typename T> void MSDRadixSort(std::vector<T>& tab, std::vector<T>& tabAux, int low, int high, int digit);

int main()
{
	std::vector<unsigned int> tabInts;
	openFile("files/ints.txt", tabInts);

    std::vector<std::string> tabText;
    openFile("files/bible-lines.txt", tabText);

    auto t_start = std::chrono::high_resolution_clock::now(); // Store the start time of the sorting algorithm

    //std::sort(tabInts.begin(), tabInts.end());

    LSDRadixSort(tabText);

    auto t_end = std::chrono::high_resolution_clock::now(); // Store the end time

    /// Print the time of the sort
	std::cout << "Sorting was : " << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << " seconds long" << std::endl;

	/*for(const auto& elem : tabInts) {
        std::cout << elem << std::endl;
	}*/

	return 0;
}


/*** Takes the name (nom) of a file and store each new line in a case of an array given as parameter ***/
void openFile(std::string nom, std::vector<std::string*>& tab) {
	std::fstream file{ nom };
	std::string temp;
	std::string* value;
	if (!file) { std::cout << "Error : file can't be opened"; }

	else {
		while (getline(file, temp)) {
            value = new std::string;
			*value = temp;
			tab.push_back(value);
		}
	}
}

void openFile(std::string nom, std::vector<std::string>& tab) {
	std::fstream file{ nom };
	std::string value;
	if (!file) { std::cout << "Error : file can't be opened"; }

	else {
		while (getline(file, value)) {
			tab.push_back(value);
		}
	}
}

void openFile(std::string nom, std::vector<unsigned int>& tab) {
	std::fstream file{ nom };
	std::string temp;
	unsigned int value;
	if (!file) { std::cout << "Error : file can't be opened"; }

	else {
        while (getline(file, temp)) {
			value = std::stoul(temp);
			tab.push_back(value);
		}
	}
}

void openFile(std::string nom, std::vector<unsigned int*>& tab) {
	std::fstream file{ nom };
	std::string temp;
	unsigned int* value;
	if (!file) { std::cout << "Error : file can't be opened"; }

	else {
        while (getline(file, temp)) {
            value = new unsigned int;
			*value = std::stoul(temp);
			tab.push_back(value);
		}
	}
}
///**************************************************************************************************///



///**** Returns the byte i of elem ; return a special velue if i is larger than the number of bytes of elem ****///
short int getByte(unsigned int elem, unsigned int i) {
	if (sizeof(elem) > i)   { return (elem >> ((3-i)*8)&(255)); }
	else return -1;
}

short int getByte(std::string elem, unsigned int i) {
	if (elem.size() > i)    { return elem[i]; }
	else return -1;
}

/*int get4bits(unsigned int elem, unsigned int i) {
    if(sizeof(elem)*2 > i)  { return (elem >> ((7-i)*4)&(15)); }
    else return -1;
}

int get2bytes(unsigned int elem, unsigned int i) {
    if(sizeof(elem)/2 > i)  { return (elem >> ((1-i)*16)&(65535)); }
    else return -1;
}*/
///************************************************************************************************************///



///**** Return the maximum number of bytes needed ****///
std::size_t getMaxLength(std::vector<unsigned int>& tab) {
    return 4;
}

std::size_t getMaxLength(std::vector<unsigned int*>& tab) {
    return 4;
}

std::size_t getMaxLength(std::vector<std::string*>& tab) {
    std::size_t maxLength = 0;
    for (const auto& elem : tab) { if ((*elem).size() > maxLength)     maxLength = (*elem).size(); }
    return maxLength;
}

std::size_t getMaxLength(std::vector<std::string>& tab) {
    std::size_t maxLength = 0;
    for (const auto& elem : tab) { if (elem.size() > maxLength)     maxLength = elem.size(); }
    return maxLength;
}
///***************************************************///



///**** Takes an array and uses the LSD Radix Sort to put it in order ****///
/// Pointer version : faster for heavy object like strings
template<typename T> void LSDRadixSort(std::vector<T*>& tab) {
    auto t_start = std::chrono::high_resolution_clock::now(); // Store the start time of the sorting algorithm

	std::size_t tabSize = tab.size();
	std::size_t maxLength = getMaxLength(tab);

	/// Counting sort
	for (int digit = maxLength - 1; digit >= 0; digit--) {
		std::vector<T*> tabAux(tabSize);
		std::vector<unsigned int> counter(RADIX + 2);

		for (unsigned int i = 0; i < tabSize; ++i) {
			counter[getByte(*tab[i], digit) + 2]++;
		}

		for (unsigned int r = 0; r < RADIX+1; ++r) {
			counter[r + 1] += counter[r];
		}

		for (unsigned int i = 0; i < tabSize; ++i) {
			tabAux[counter[getByte(*tab[i], digit)+1]++] = tab[i];
		}

		for (unsigned int i = 0; i < tabSize; ++i) {
			tab[i] = tabAux[i];
		}
	}

	auto t_end = std::chrono::high_resolution_clock::now(); // Store the end time

	/// Print the time of the sort
	std::cout << "Sorting (with pointer) was : " << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << " seconds long" << std::endl;
}

/// Normal version : faster for small objects like integers
template<typename T> void LSDRadixSort(std::vector<T>& tab) {
    auto t_start = std::chrono::high_resolution_clock::now(); // Store the start time of the sorting algorithm

	std::size_t tabSize = tab.size();
	std::size_t maxLength = getMaxLength(tab);

	/// Counting sort
	for (int digit = maxLength - 1; digit >= 0; digit--) {
		std::vector<T> tabAux(tabSize);
		std::vector<unsigned int> counter(RADIX + 2);

		for (unsigned int i = 0; i < tabSize; ++i) {
			counter[getByte(tab[i], digit) + 2]++;
		}

		for (unsigned int r = 0; r < RADIX+1; ++r) {
			counter[r + 1] += counter[r];
		}

		for (unsigned int i = 0; i < tabSize; ++i) {
			tabAux[counter[getByte(tab[i], digit)+1]++] = tab[i];
		}

		for (unsigned int i = 0; i < tabSize; ++i) {
			tab[i] = tabAux[i];
		}
	}

	auto t_end = std::chrono::high_resolution_clock::now(); // Store the end time

    /// Print the time of the sort
	std::cout << "Sorting (without pointer) was : " << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << " seconds long" << std::endl;
}
///***************************************************************************************************///


///**** MSD Radix Sort ****///
template<typename T> void MSDRadixSort(std::vector<T*>& tab) {
	std::vector<T*> tabAux(tab.size());
	MSDRadixSort(tab, tabAux, 0, tab.size(), 0);
}

template<typename T> void MSDRadixSort(std::vector<T>& tab) {
	std::vector<T> tabAux(tab.size());
	MSDRadixSort(tab, tabAux, 0, tab.size(), 0);
}

template<typename T> void MSDRadixSort(std::vector<T*>& tab, std::vector<T*>& tabAux, int low, int high, int digit) {

	std::vector<int> counter(RADIX+2);

	for (int i = low; i < high; ++i) {
		counter[getByte(*tab[i], digit) + 2]++;
	}

	for (int r = 0; r < RADIX+1; ++r) {
		counter[r+1] += counter[r];
	}

	for (int i = low; i < high; ++i) {
		tabAux[counter[getByte(*tab[i], digit)+1]++] = tab[i];
	}

	for (int i = low; i < high; ++i) {
		tab[i] = tabAux[i-low];
	}

    for(int r = 0; r < RADIX; ++r) {
        if(low+counter[r] < low+counter[r+1])    MSDRadixSort(tab, tabAux, low+counter[r], low+counter[r+1], digit+1);
    }
}

template<typename T> void MSDRadixSort(std::vector<T>& tab, std::vector<T>& tabAux, int low, int high, int digit) {

	std::vector<int> counter(RADIX+2);

	for (int i = low; i < high; ++i) {
		counter[getByte(tab[i], digit) + 2]++;
	}

	for (int r = 0; r < RADIX+1; ++r) {
		counter[r+1] += counter[r];
	}

	for (int i = low; i < high; ++i) {
		tabAux[counter[getByte(tab[i], digit)+1]++] = tab[i];
	}

	for (int i = low; i < high; ++i) {
		tab[i] = tabAux[i-low];
	}

    for(int r = 0; r < RADIX; ++r) {
        if(low+counter[r] < low+counter[r+1])    MSDRadixSort(tab, tabAux, low+counter[r], low+counter[r+1], digit+1);
    }
}
