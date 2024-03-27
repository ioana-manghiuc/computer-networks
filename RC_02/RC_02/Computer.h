#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Computer
{
public:
	Computer();
	Computer(const std::string& IP, const std::string& buffer);
	Computer(int id, const std::string& IP, const std::string& buffer);

	const std::string& GetIPAddress() const;
	const std::string& GetBuffer() const;
	int GetID() const;

	void SetBufferContent(const std::string& buffer);

	bool operator==(const Computer& computer) const;
	friend std::istream & operator>>(std::istream & is, Computer& computer);
	friend std::ostream & operator<<(std::ostream & os, const Computer& computer);

private:
	int m_ID;
	std::string m_IPAddress;
	std::string m_buffer;
};

