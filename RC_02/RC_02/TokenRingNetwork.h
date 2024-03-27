#pragma once
#include "Computer.h"
#include "Token.h"
#include <vector>

using ComputerPtr = std::shared_ptr<Computer>;
using TokenPtr = std::shared_ptr<Token>;

class TokenRingNetwork
{
public:
	TokenRingNetwork();

	std::pair<ComputerPtr, ComputerPtr> GenerateSourceAndDestination();
	void SendPacket(const std::string& message);
	void Run();

	friend std::ostream& operator<<(std::ostream& os, const TokenRingNetwork& network);

private:
	void ReadComputers();
	bool ValidateIP(const std::string& ip);
	bool IPAddressExists(const std::string& ip);

private:
	std::vector<ComputerPtr> m_computers;
	TokenPtr m_token;
};

