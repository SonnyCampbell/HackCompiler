#include "JackTokenizer.h"



JackTokenizer::JackTokenizer(std::string fileName)
{
	tokenFile.open(fileName);
}


JackTokenizer::~JackTokenizer()
{
}

void JackTokenizer::Advance()
{
	if (HasMoreTokens())
	{
		GetNextToken();
	}
	else
	{
		std::cout << "Reached end of file. Compilation complete.";
		tokenFile.close();
		return;
	}
}

bool JackTokenizer::HasMoreTokens()
{
	return !tokenFile.eof();
}

void JackTokenizer::GetNextToken()
{

}
