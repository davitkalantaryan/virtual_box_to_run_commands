
#include <iostream>

int main(int argc, char* argv[])
{
	::std::cout << "Hello world! (";
	if(argc > 1) { ::std::cout<<"1 will be returned)\n";}else{ ::std::cout<<"0 will be returned)\n";}
	return argc>1?1:0;
}
