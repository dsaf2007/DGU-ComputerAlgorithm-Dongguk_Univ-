//2016112154 정동구
#include <iostream>
#include <vector>
#include <cstdlib>
#include "hamiltonian.h"
#include "BWT.h"
#include "ACTG.h"


int main()
{
	std::string seq_01[8] = { "AGT", "AAA", "ACT", "AAC", "CTT", "GTA", "TTT", "TAA" };
	std::string seq_02[8] = { "ATG", "AGG", "TGC", "TCC", "GTC", "GGT", "GCA", "CAG" };
	std::string seq_03[8] = { "ATG", "TGG", "TGC", "GTG","GGC", "GCA", "GCG", "CGT" };
	std::string seq_04[13] = { "ATGC", "TGCG", "GCGG", "CGGC", "GGCT", "GCTG",
							   "CTGT", "TGTA", "GTAT", "TATG", "ATGG", "TGGT", "GGTG" };

	// 임의로 만든 스트링
	std::string seq_05[9] = { "GAA", "ATC", "TCT", "AAG", "TCG", "CTT", "GTC", "AGT", "CGA" };

	int size = sizeof(seq_01) / sizeof(seq_01[0]);
	hamiltonian* hamilton_01 = new hamiltonian(seq_01, size);

	hamilton_01->make_adj_matrix();
	//hamilton_01->show_matrix();
	hamilton_01->hamilton_rec();

	////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(seq_02) / sizeof(seq_02[0]);
	hamiltonian* hamilton_02 = new hamiltonian(seq_02, size);

	hamilton_02->make_adj_matrix();
	//hamilton_02->show_matrix();
	hamilton_02->hamilton_rec();

	////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(seq_03) / sizeof(seq_03[0]);
	hamiltonian* hamilton_03 = new hamiltonian(seq_03, size);


	hamilton_03->make_adj_matrix();
	//hamilton_03->show_matrix();
	hamilton_03->hamilton_rec();

	////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(seq_04) / sizeof(seq_04[0]);
	hamiltonian* hamilton_04 = new hamiltonian(seq_04, size);

	hamilton_04->make_adj_matrix();
	//hamilton_04->show_matrix();
	hamilton_04->hamilton_rec();

	/////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(seq_05) / sizeof(seq_05[0]);
	hamiltonian* hamilton_05 = new hamiltonian(seq_05, size);

	hamilton_05->make_adj_matrix();
	//hamilton_05->show_matrix();
	hamilton_05->hamilton_rec();


	delete hamilton_01;
	delete hamilton_02;
	delete hamilton_03;
	delete hamilton_04;
	delete hamilton_05;
	std::cout << "======================\n";
	BWT bwt("mississippi");
	bwt.init();
	bwt.sortRest();
	bwt.decode();
	std::cout << "======================\n";
	BWT bwt2("chungdonggu");
	bwt2.init();
	bwt2.sortRest();
	bwt2.decode();


	ACTG test(30, 40000);
	test.init();
}