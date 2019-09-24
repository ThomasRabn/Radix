#include "useful.h"
#define NUM_mSEC std::chrono::duration<double, std::milli>(t_end - t_start).count()
#define RADIX 256
#define SORT_THRESHOLD 256


int main()
{
    /// Creation of both arrays
	std::vector<unsigned int> tabInts;
	std::vector<std::string*> tabText;

	/// We load the arrays
	openFile("files/bible-lines.txt", tabText);
	openFile("files/ints.txt", tabInts);

	///Choose which array you want to sort
	auto arr = tabInts;

    auto t_start = std::chrono::high_resolution_clock::now(); // Store the start time of the sorting algorithm

    /// Choose which sorting algorithm you want to use
    //LSDRadixSort(arr);
    MSDRadixSort(arr);
    //std::sort(arr.begin(), arr.end(), Compare());

    auto t_end = std::chrono::high_resolution_clock::now(); // Store the end time

    /// Print the time of the sort
	std::cout << std::endl << "       Sorting integers with MSD sort was : " << NUM_mSEC << " ms long" << std::endl;

	/// Print an error if the array isn't sorted
    int verif = verify(arr);

    /// If this is uncommented and verify() didn't return an error, the array is printed
    /*if (verif == 0) {
        print(arr);
    }*/

	return 0;
}

///**** LSD Radix Sort ****///
///**** Takes an array and uses the LSD Radix Sort to put it in order ****///
template<typename T> void LSDRadixSort(std::vector<T>& tab) {

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
}
///***************************************************************************************************///


///**** MSD Radix Sort ****//

template<typename T> void MSDRadixSort(std::vector<T>& tab) {
	std::vector<T> tabAux(tab.size());
	MSDRadixSort(tab, tabAux, 0, tab.size(), 0);
}

template<typename T> void MSDRadixSort(std::vector<T>& tab, std::vector<T>& tabAux, int low, int high, int digit) {

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
