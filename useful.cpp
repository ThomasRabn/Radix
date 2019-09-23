#include "useful.h"

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

///**************************************************************************************************///



///**** Returns the byte i of elem ; return a special velue if i is larger than the number of bytes of elem ****///
short int getByte(unsigned int elem, unsigned int i) {
	if (sizeof(elem) > i)   { return (elem >> ((3-i)*8)&(255)); }
	else return -1;
}

short int getByte(std::string* elem, unsigned int i) {
	if ((*elem).size() > i)    { return (*elem)[i]; }
	else return -1;
}
///************************************************************************************************************///



///**** Return the maximum number of bytes needed ****///
std::size_t getMaxLength(std::vector<unsigned int>& tab) {
    return 4;
}

std::size_t getMaxLength(std::vector<std::string*>& tab) {
    std::size_t maxLength = 0;
    for (const auto& elem : tab) { if ((*elem).size() > maxLength)     maxLength = (*elem).size(); }
    return maxLength;
}
///***************************************************///
