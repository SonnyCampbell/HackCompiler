#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

typedef enum
{
	KEYWORD,
	SYMBOL,
	IDENTIFIER,
	INT_CONST,
	STRING_CONST
} Token;

class JackTokenizer
{
public:
	JackTokenizer(std::string);
	~JackTokenizer();

	void WriteToFile(std::ofstream &outputFile);

	void Advance();
	bool HasMoreTokens();

	std::string token;
	
private:
	std::ifstream jackFile;

	std::string currentLine;
	bool isComment;
	

	std::string& ltrim(std::string&, const char* t);
	std::string& rtrim(std::string&, const char* t);
	std::string& trim(std::string&, const char* t);


	void GetNextToken();
};

