#include "JackTokenizer.h"



JackTokenizer::JackTokenizer(std::string fileName)
{
	jackFile.open(fileName);
	currentLine = "";
	isComment = false;
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
		jackFile.close();
		return;
	}
}

bool JackTokenizer::HasMoreTokens()
{
	return !jackFile.eof();
}

void JackTokenizer::GetNextToken()
{
	if (!jackFile.eof())
	{
		while (currentLine == "" || (currentLine[0] == '/' && currentLine[1] == '/'))
		{
			if (!HasMoreTokens())
				return;

			std::getline(jackFile, currentLine);
			currentLine = trim(currentLine, " \t\n\r\f\v");


			if (currentLine[0] == '/' && currentLine[1] == '*')
			{
				isComment = true;
			}
			

			while (isComment || (currentLine[0] == '/' && currentLine[1] == '*'))
			{
				// For some reason the below doesn't work, so I hacked this crap together
				// currentLine.find_first_of("*/") != std::string::npos                  
				// I should probably be using some form of REGEX
				while (currentLine.find_first_of("*") != std::string::npos)
				{
					std::string endComment = currentLine.substr(currentLine.find_first_of("*"), 2);
					currentLine = currentLine.substr(currentLine.find_first_of(endComment), currentLine.size());
					if (endComment == "*/")
						isComment = false;

					currentLine.erase(currentLine.find_first_of(endComment), 2);
				}
					

				if (!HasMoreTokens())
					return;

				std::getline(jackFile, currentLine);
				currentLine = trim(currentLine, " \t\n\r\f\v");
			}

		}


		if (currentLine == ";")
		{
			token = currentLine;
			currentLine = "";
		}
		else if (currentLine.find_first_of(" ") != currentLine.npos)
		{
			token = currentLine.substr(0, currentLine.find_first_of(" "));

			if (token.find_first_of(";") != token.npos && token != ";")
			{
				token = currentLine.substr(0, currentLine.find_first_of(";"));
				currentLine = trim(currentLine.substr(currentLine.find_first_of(";"), currentLine.size()), " \t\n\r\f\v");
			}
			else
			{
				currentLine = trim(currentLine.substr(currentLine.find_first_of(" "), currentLine.size()), " \t\n\r\f\v");
			}
		}
		else if (currentLine.find_first_of(";") != currentLine.npos)
		{
			token = currentLine.substr(0, currentLine.find_first_of(";"));
			currentLine = trim(currentLine.substr(currentLine.find_first_of(";"), currentLine.size()), " \t\n\r\f\v");
		}
		else
		{
			token = currentLine;
			currentLine = "";
		}
	}
}


void JackTokenizer::WriteToFile(std::ofstream &outputFile)
{

}

// trim from left
std::string& JackTokenizer::ltrim(std::string& s, const char* t)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from right
std::string& JackTokenizer::rtrim(std::string& s, const char* t)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from left & right
std::string& JackTokenizer::trim(std::string& s, const char* t)
{
	return ltrim(rtrim(s, t), t);
}


template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}
