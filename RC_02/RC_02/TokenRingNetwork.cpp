#include "TokenRingNetwork.h"
#include <random>

TokenRingNetwork::TokenRingNetwork():
	m_token(std::make_shared<Token>())
{
	ReadComputers();
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

std::pair<ComputerPtr, ComputerPtr> TokenRingNetwork::GenerateSourceAndDestination()
{
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

void TokenRingNetwork::SendPacket(const std::string& message)
{
	auto [source, destination] = GenerateSourceAndDestination();

	std::cout << "Source: C" << source->GetID() << " - " << source->GetIPAddress()
		<< "\nDestination: C" << destination->GetID() << " - " << destination->GetIPAddress() << std::endl;

	m_token->SetMessage(message);
	m_token->SetSourceIP(source->GetIPAddress());
	m_token->SetDestinationIP(destination->GetIPAddress());

	auto it_source = std::find_if(m_computers.begin(), m_computers.end(),
		[&source](const ComputerPtr& comp) { return comp->GetIPAddress() == source->GetIPAddress(); });

	auto it_destination = std::find_if(m_computers.begin(), m_computers.end(),
		[&destination](const ComputerPtr& comp) { return comp->GetIPAddress() == destination->GetIPAddress(); });

	if (it_source == m_computers.end() || it_destination == m_computers.end()) {
		std::cerr << "Error: Source or destination computer not found in the network." << std::endl;
		return;
	}

	std::vector<ComputerPtr> tokenRing;
	tokenRing.reserve(m_computers.size() * 2);

	// from source to destination
	if (it_source <= it_destination)
		std::copy(it_source, it_destination + 1, std::back_inserter(tokenRing));
	else {
		std::copy(it_source, m_computers.end(), std::back_inserter(tokenRing));

		std::copy(m_computers.begin(), it_destination + 1, std::back_inserter(tokenRing));
	}

	// continue from destination forward to the source
	tokenRing.push_back(*it_destination);

	// if source reached after destination, stop inserting
	bool source_reached = false;
	for (auto it = std::next(it_destination); it != m_computers.end(); ++it) {
		if (*it == *it_source) {
			source_reached = true;
			break;
		}
		tokenRing.push_back(*it);
	}

	if (!source_reached) {
		for (auto it = m_computers.begin(); it != it_source + 1; ++it) {
			tokenRing.push_back(*it);
		}
	}

	if (tokenRing.back()->GetIPAddress() != source->GetIPAddress()) {
		tokenRing.push_back(source);
	}

	for (auto c : tokenRing)
	{
		std::cout << *c << std::endl;
	}
}

void TokenRingNetwork::Run()
{
	std::string input;
	while (true)
	{
		std::cout<< "Do you want to send a message? (y/n)";
		std::cin >> input;		
		if (input == "y" || input == "Y")
		{
			std::string message;
			std::cout << "Enter message: "; std::cin >> message;
			SendPacket(message);
		}
		else
		{
			break;
		}
		
	}
}

std::ostream& operator<<(std::ostream& os, const TokenRingNetwork& network)
{
	for (int i = 0; i < network.m_computers.size(); i++)
	{
		os << *network.m_computers[i] << std::endl;
	}
	return os;
}
