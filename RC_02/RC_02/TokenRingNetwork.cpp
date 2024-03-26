#include "TokenRingNetwork.h"
#include <sstream>

TokenRingNetwork::TokenRingNetwork()
{
	ReadComputers();
}

void TokenRingNetwork::GenerateSource()
{
}

void TokenRingNetwork::GenerateDestination()
{
}

void TokenRingNetwork::ReadComputers()
{
	std::ifstream input("computers.txt");
	if (!input.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}

	std::string ip, buffer;
	while (input >> ip >> buffer)
	{
		m_computers.push_back(std::make_shared<Computer>(ip, buffer));
	}

	input.close();
}

std::ostream& operator<<(std::ostream& os, const TokenRingNetwork& network)
{
	for (int i = 0; i < network.m_computers.size(); i++)
	{
		os << "C" << i << " " << *network.m_computers[i] << std::endl;
	}
	return os;
}
