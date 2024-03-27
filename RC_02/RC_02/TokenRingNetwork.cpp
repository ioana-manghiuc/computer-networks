#include "TokenRingNetwork.h"
#include <random>

TokenRingNetwork::TokenRingNetwork():
	m_token(Token())
{
	ReadComputers();
}

std::pair<ComputerPtr, ComputerPtr> TokenRingNetwork::GenerateSourceAndDestination()
{
	// source first, destination second
	std::random_device RD;
	std::mt19937 engine(RD());
	std::uniform_int_distribution<> distr(0, m_computers.size() - 1);

	ComputerPtr source, destination;
	source = m_computers[distr(engine)];
	do
	{
		destination = m_computers[distr(engine)];
	} while (source == destination);

	return {source, destination};
}

bool TokenRingNetwork::ValidateIP(const std::string& ip)
{
	int part = 0;
	int count = 1;
	for (auto c : ip)
	{
		if (c != '.')
		{
			part = part * 10 + (c - '0');
		}
		else
		{			
			if (part < 0 || part > 255)
			{
				return false;
			}
			count++;
			part = 0;
		}
	}
	if (count != 4)
	{
		return false;
	}
	return true;
}

bool TokenRingNetwork::IPAddressExists(const std::string& ip)
{
	return std::find_if(m_computers.begin(), m_computers.end(),
		[&ip](auto computer) {
			return computer->GetIPAddress() == ip;
		}) != m_computers.end();
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
		if (ValidateIP(ip) && !IPAddressExists(ip))
		{
			m_computers.push_back(std::make_shared<Computer>(m_computers.size(), ip, buffer));
		}
		else
		{	
			while (true)
			{
				std::cerr << "Invalid IP address / IP address already exists\nEnter new IP Address:" << std::endl;
				std::cin >> ip;
				if (ValidateIP(ip) && !IPAddressExists(ip))
				{
					m_computers.push_back(std::make_shared<Computer>(ip, buffer));
					break;
				}
			}
			
		}
	}

	input.close();
}


//ComputerPtr TokenRingNetwork::GenerateSource()
//{
//
//}
//
//ComputerPtr TokenRingNetwork::GenerateDestination()
//{
//
//}


std::ostream& operator<<(std::ostream& os, const TokenRingNetwork& network)
{
	for (int i = 0; i < network.m_computers.size(); i++)
	{
		os << "C" << *network.m_computers[i] << std::endl;
	}
	return os;
}
