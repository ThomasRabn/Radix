#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

#include "useful.h"


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

    if ((high-low) < SORT_THRESHOLD) {
        std::sort(tab.begin()+low, tab.begin()+high, Compare());
    }
    else {
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
}

template<typename T> void MSDRadixSort(std::vector<T>& tab, std::vector<T>& tabAux, int low, int high, int digit) {

    if ((high-low) < SORT_THRESHOLD) {
        std::sort(tab.begin()+low, tab.begin()+high);
    }
    else {
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
}

#endif // SORTING_H_INCLUDED
