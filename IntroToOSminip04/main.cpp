//Mini project 04 made by Zachary Kingcade & Dominque Shepherd

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

/*since we are running in a space of 8kb (8192 bytes) and each page is 256 bytes
we have 32 slots to work with in our paging system, I think*/
/* Confirmed by passos since our page is 256  bytes the offset for it is 8 bits and
we are told our address is a size of 16 bits meaning the page address is also 8 bits */

//prototypes
int generateAddress();
int maskOffset(int address);

int main() {
  //to store our "pages" I'm going to use a vector
	std::vector <int> pageTableFIFO;
	std::vector <int> pageTableLRU;
	int FIFOPageFaults = 0;
	int LRUPageFaults = 0;

	srand(time(0));

	//FIFO Section
	//FIFO is real easy, we just insert from the back and take from the front once we reach max size
	for (int i = 0; i < 1000; i++){
		//get and mask a new address
		int newPage = maskOffset(generateAddress());
		if (std::count(pageTableFIFO.begin(), pageTableFIFO.end(), newPage)){
			//do nothing
		} else if(pageTableFIFO.size() < 32){
			pageTableFIFO.push_back(newPage);
		} else {
			pageTableFIFO.erase(pageTableFIFO.begin());
			pageTableFIFO.push_back(newPage);
			FIFOPageFaults++;
		}
	}
	std::cout << "Numer of page faults using FIFO: " << FIFOPageFaults << std::endl;

	//LRU Section
	//here we do almost the same but we move item to the front when they are accessed
	for (int i = 0; i < 1000; i++){
		//get and mask a new address
		int newPage = maskOffset(generateAddress());
		if (std::count(pageTableLRU.begin(), pageTableLRU.end(), newPage)){
			std::vector<int>::iterator index = std::find(pageTableLRU.begin(), pageTableLRU.end(), newPage);
			int temp = *index;
			pageTableLRU.erase(index);
			pageTableLRU.insert(pageTableLRU.begin(), temp);
		} else if(pageTableLRU.size() < 32){
			pageTableLRU.push_back(newPage);
		} else {
			pageTableLRU.erase(pageTableLRU.begin());
			pageTableLRU.push_back(newPage);
			LRUPageFaults++;
		}
	}
	std::cout << "Numer of page faults using LRU: " << LRUPageFaults << std::endl;

	return 0;
}

int generateAddress(){
	int result = rand() & 0xFFFF;
	return result;
}

int maskOffset(int address){
	int result =  address & 0xFF;
	return result;
}