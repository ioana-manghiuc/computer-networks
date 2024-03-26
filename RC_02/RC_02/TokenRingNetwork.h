#pragma once
#include "Computer.h"
#include <vector>

using ComputerPtr = std::shared_ptr<Computer>;

class TokenRingNetwork
{
public:
	TokenRingNetwork();

	void GenerateSource();
	void GenerateDestination();
	friend std::ostream& operator<<(std::ostream& os, const TokenRingNetwork& network);

private:
	void ReadComputers();

private:
	std::vector<ComputerPtr> m_computers;
	int m_token;
};

