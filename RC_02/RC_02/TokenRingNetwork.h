#pragma once
#include "Computer.h"
#include "Token.h"
#include <vector>

using ComputerPtr = std::shared_ptr<Computer>;

class TokenRingNetwork
{
public:
	TokenRingNetwork();

	std::pair<ComputerPtr, ComputerPtr> GenerateSourceAndDestination();
	friend std::ostream& operator<<(std::ostream& os, const TokenRingNetwork& network);

private:
	void ReadComputers();
	bool ValidateIP(const std::string& ip);
	bool IPAddressExists(const std::string& ip);

private:
	std::vector<ComputerPtr> m_computers;
	Token m_token;
};

