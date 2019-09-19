#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

short int getByte(unsigned int elem, unsigned int i);
char getByte(std::string elem, unsigned int i);
void LSDRadixSort(std::vector<std::string*>& tab);
template<typename T>
void openFile(std::string nom, std::vector<T*>& tab);

int main()
{
	std::vector<std::string*> text;
	openFile("files/bible-lines.txt", text);

	auto t_start = std::chrono::high_resolution_clock::now(); // Store the start time of the sorting algorithm

	LSDRadixSort(text); // Launch the sort

	auto t_end = std::chrono::high_resolution_clock::now(); // Store the end time

	/// Print the time of the sort
	std::cout << "Le tri a pris : " << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << " selon chrono" << std::endl;

	return 0;
}

/// Returns the byte i of elem (elem being a unsigned int) ; returns -1 if i is larger than the number of bytes of elem
short int getByte(unsigned int elem, unsigned int i) {
	if (sizeof(elem) > i) { return (elem >> ((3 - i) * 8) & 255); }
	else return -1;
}

/// Returns the byte i of elem (elem being a string) ; returns '\0' (NULL) if i is larger than the number of bytes of elem
char getByte(std::string elem, unsigned int i) {
	if (elem.size() > i) { return elem[i]; }
	else return '\0';
}

/// Takes an array and uses the LSD Radix Sort to put it in order
void LSDRadixSort(std::vector<std::string*>& tab) {
	std::size_t tabSize = tab.size();
	unsigned int radix = 256;
	std::size_t maxLength = 0;

	/// Store the biggest length of all the array
	for (const auto& elem : tab) { if ((*elem).size() > maxLength)     maxLength = (*elem).size(); }

	std::cout << "Max length : " << maxLength << std::endl << std::endl;

	/// Counting sort
	for (int digit = maxLength - 1; digit >= 0; digit--) {
		std::vector<std::string*> tabAux(tabSize);
		std::vector<int> counter(radix + 1);

		for (unsigned int i = 0; i < tabSize; ++i) {
			counter[getByte(*tab[i], digit) + 1]++;
		}

		for (unsigned int r = 0; r < radix; ++r) {
			counter[r + 1] += counter[r];
		}

		for (unsigned int i = 0; i < tabSize; ++i) {
			tabAux[counter[getByte(*tab[i], digit)]++] = tab[i];
		}

		for (unsigned int i = 0; i < tabSize; ++i) {
			tab[i] = tabAux[i];
		}
	}
}

/// Takes the name (nom) of a file and store each new line in a case of an array given as parameter
template<typename T>
void openFile(std::string nom, std::vector<T*>& tab) {
	std::fstream file{ nom };
	T temp;
	T* value;
	if (!file) { std::cout << "Error : file can't be opened"; }

	else {
		while (getline(file, temp)) {
			value = new T;
			*value = temp;
			tab.push_back(value);
		}
	}
}
