//2016112154 정동구
#include <iostream>
#include <vector>
#include <cstdlib>
#include "ACTG.h"
#include <thread>

int main()
{
	std::string mydna;
	std::string refdna;
	std::string shortread;
	std::vector<std::string> short_read_;
	//read refdna

	std::string path = "./test_data_set/1000000/40_35000/";
	std::ifstream readRef(path+"ref.txt");
	std::getline(readRef, refdna);
	//read mydna
	std::ifstream readMy(path+"mydna.txt");
	std::getline(readMy, mydna);

	std::ifstream readShortRead(path+"shortread.txt");
	while (std::getline(readShortRead, shortread))
	{
		short_read_.push_back(shortread);
	}
	//std::cout << short_read_[0].length();
	time_t startx, endx;
	startx = time(NULL);
	ACTG test(mydna,refdna,short_read_,path);
	test.printSizeInfo();
	//test.exec_initMyDNA();
	//test.makeShortread();

	test.execute_triv();
	//test.BMRestore(0);
	//test.restore();
	std::cout << "걸린시간 :" << test.elapse_time << std::endl;
	test.compare(0);
	endx = time(NULL);
	std::cout << "총 걸린 시간 : " << (double)(endx - startx) << "\n";
	test.makeText();


	
}