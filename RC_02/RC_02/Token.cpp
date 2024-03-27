#include "Token.h"

Token::Token()
	: m_destinationIP(""), m_message(""), m_sourceIP(""), 
		m_status(ETokenStatus::None), m_messageStatus(EMessageStatus::NotSet)
{
	// Empty
}

void Token::SetSourceIP(const std::string& sourceIP)
{
	m_sourceIP = sourceIP;
}

void Token::SetDestinationIP(const std::string& destinationIP)
{
	m_destinationIP = destinationIP;
}

void Token::SetMessage(const std::string& message)
{
	m_message = message;
	m_status = ETokenStatus::Occupied;
	m_messageStatus = EMessageStatus::LeftDestination;
}
