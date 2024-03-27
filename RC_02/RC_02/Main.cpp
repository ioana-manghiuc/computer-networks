#include "TokenRingNetwork.h"
using NetworkPtr = std::unique_ptr<TokenRingNetwork>;


int main()
{
	NetworkPtr network = std::make_unique<TokenRingNetwork>();
	std::cout << *network;
	auto pair = network->GenerateSourceAndDestination();
	std::cout << "Source: C" << pair.first->GetID() << " - " << pair.first->GetIPAddress()
		<< "\nDestination: C" << pair.second->GetID() << " - " << pair.second->GetIPAddress() << std::endl;
	return 0;
}