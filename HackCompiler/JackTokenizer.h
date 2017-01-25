#pragma once
#include <string>
#include <fstream>
#include <iostream>

typedef enum
{
	KEYWORD,
	SYMBOL,
	IDENTIFIER,
	INT_CONST,
	STRING_CONST
} TokenType;

class JackTokenizer
{
public:
	JackTokenizer(std::string);
	~JackTokenizer();

	void WriteToFile(std::ofstream &outputFile);


private:
	std::ifstream tokenFile;
	void Advance();
	bool HasMoreTokens();
	void GetNextToken();
};

