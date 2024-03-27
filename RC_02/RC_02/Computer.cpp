#include "Computer.h"

Computer::Computer()
	: m_ID(0), m_IPAddress(""), m_buffer("")
{
	// Empty
}

Computer::Computer( const std::string& IP, const std::string& buffer)
	: m_ID(0), m_IPAddress(IP), m_buffer(buffer)
{
	// Empty
}

Computer::Computer(int id, const std::string& IP, const std::string& buffer)
	: m_ID(id), m_IPAddress(IP), m_buffer(buffer)
{
	// Empty
}

const std::string& Computer::GetIPAddress() const
{
	return m_IPAddress;
}

const std::string& Computer::GetBuffer() const
{
	return m_buffer;
}

int Computer::GetID() const
{
	return m_ID;
}


void Computer::SetBufferContent(const std::string& buffer)
{
	m_buffer = buffer;
}

void Computer::SetAction(const std::string_view& action)
{
	m_action = std::string(action);
}

void Computer::PrintAction() const
{
	std::cout << "C" << m_ID << ": " << m_action << std::endl;
}

bool Computer::operator==(const Computer& computer) const
{
	return this->m_IPAddress == computer.m_IPAddress;
}

std::istream& operator>>(std::istream& is, Computer& computer)
{
	return is >> computer.m_IPAddress >> computer.m_buffer;
}

std::ostream& operator<<(std::ostream& os, const Computer& computer)
{
	return os << "C" <<computer.m_ID << " (" << computer.m_IPAddress << ") -> " << computer.m_buffer;
}
