#include "useful.h"
#include "sorting.h"

int main()
{
	std::vector<unsigned int> tabInts;
	openFile("files/ints.txt", tabInts);

    std::vector<std::string*> tabText;
    openFile("files/bible-lines.txt", tabText);

    auto t_start = std::chrono::high_resolution_clock::now(); // Store the start time of the sorting algorithm

    //std::sort(tabInts.begin(), tabInts.end(), Compare());

    MSDRadixSort(tabInts);

    auto t_end = std::chrono::high_resolution_clock::now(); // Store the end time

    /// Print the time of the sort
	std::cout << "Sorting was : " << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << " seconds long" << std::endl;

	for(const auto& elem : tabInts) {
        std::cout << elem << std::endl;
	}

	return 0;
}
