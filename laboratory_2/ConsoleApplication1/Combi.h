#pragma once
#include <vector>
#include <iostream>
namespace combi {
	struct subset {
		short n;
		short sn;
		std::vector<short> sset;
		unsigned long long mask;
		subset(short n = 1);
		short getfirst();
		short getnext();
		short ntx(short i);
		void reset();
		unsigned long long count();
	};

	struct xcombination {
		long long n;
		long long m;
		std::vector<int> sset;
		long long nc;
		xcombination(long long n = 1, long long m = 1);
		long long getfirst();
		long long getnext();
		long long ntx(short i);
		void reset();
		//unsigned long long fact(unsigned long long x);
		unsigned long long count();
	};


	struct permutation {
		const static bool L = true;
		const static bool R = false;
		short n;
		long long np;
		std::vector<short> sset;
		std::vector<bool> dart;
		permutation(short n = 1);
		void reset();
		long long getfirst();
		long long getnext();
		short ntx(short i);
		long long count();
	};

	struct accomodation {
		short n;
		short m;
		std::vector<short> sset;
		xcombination* cgen;
		permutation* pgen;
		accomodation(short n = 1, short m = 1);
		void reset();
		short getfirst();
		short getnext();
		short ntx(short i);
		long long na;
		unsigned long long count();
	};
}