#pragma once
#include "ETokenStatus.h"
#include "EMessageStatus.h"
#include <string>

class Token
{
public:
	Token();

	const std::string& GetSourceIP() const;
	const std::string& GetDestinationIP() const;

	void SetSourceIP(const std::string& sourceIP);
	void SetDestinationIP(const std::string& destinationIP);
	void SetMessage(const std::string& message); // sets statuses as well
	void ReachedDestination();
	void Free();

	bool IsFree();

private:
	std::string m_sourceIP;
	std::string m_destinationIP;
	std::string m_message;
	ETokenStatus m_status;
	EMessageStatus m_messageStatus;
};

