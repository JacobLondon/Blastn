#define TEST true

#if TEST == false
#include "blastn.hpp"
int main(int argc, char** argv)
{
	return 0;
}

#else
#include "test.hpp"
int main(int argc, char** argv)
{
	//tsplit_to_words();
	//tsmith_waterman();
	//tsequence();
	//tmatch();
	//tdust();
	textend();

	std::cin.get();
	return 0;
}
#endif
