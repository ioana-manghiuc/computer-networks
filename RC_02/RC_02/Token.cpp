#include "Token.h"

Token::Token()
	: m_destinationIP(""), m_message(""), m_sourceIP(""), 
		m_status(ETokenStatus::None), m_messageStatus(EMessageStatus::NotSet)
{
	// Empty
}

const std::string& Token::GetSourceIP() const
{
	return m_sourceIP;
}

const std::string& Token::GetDestinationIP() const
{
	return m_destinationIP;
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
	m_messageStatus = EMessageStatus::LeftSource;
}

void Token::Free()
{
	m_message = "";
	m_status = ETokenStatus::Free;
	m_messageStatus = EMessageStatus::ReachedDestination;
}

bool Token::IsFree()
{
	return m_status == ETokenStatus::Free || m_status == ETokenStatus::None;
}
