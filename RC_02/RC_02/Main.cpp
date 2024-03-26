#include "TokenRingNetwork.h"
using NetworkPtr = std::unique_ptr<TokenRingNetwork>;


int main()
{
	NetworkPtr network = std::make_unique<TokenRingNetwork>();
	std::cout << *network;
	return 0;
}