#include "Computer.h"

Computer::Computer()
	: m_IPAddress(""), m_buffer("")
{
	// Empty
}

Computer::Computer( const std::string& IP, const std::string& buffer)
	: m_IPAddress(IP), m_buffer(buffer)
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


void Computer::SetBufferContent(const std::string& buffer)
{
	m_buffer = buffer;
}

std::istream& operator>>(std::istream& is, Computer& computer)
{
	return is >> computer.m_IPAddress >> computer.m_buffer;
}

std::ostream& operator<<(std::ostream& os, const Computer& computer)
{
	return os << "(" << computer.m_IPAddress << ") -> " << computer.m_buffer;
}
