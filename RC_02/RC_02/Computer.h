#pragma once
#include <string>
#include <iostream>
#include <fstream>

static const std::string_view MOVE = "Moving Token";
static const std::string_view RECEIVE = "Token received by destination";
static const std::string_view RETURNED = "Token returned to source";
static const std::string_view ACQUIRED = "Token acquired by source - sending to destination";

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
	void SetAction(const std::string_view& action);
	void PrintAction() const;

	bool operator==(const Computer& computer) const;
	friend std::istream & operator>>(std::istream & is, Computer& computer);
	friend std::ostream & operator<<(std::ostream & os, const Computer& computer);

private:
	int m_ID;
	std::string m_IPAddress;
	std::string m_buffer;
	std::string m_action;
};

