// Knapecz, Adam - 1DAE11
#include <iostream>
#include <fstream>
#include <string>

void ReadFromConsole();
void ReadFromFile();
void WriteToFile(const std::string& text);
void ReadSentence(std::istream& istream, std::string& sentence);

int main()
{
    //ReadFromConsole();
    //ReadFromFile();
    std::string sentence;
    const std::string fileName{"../Resources/SoftwareQuotesInput.txt"};
    std::ifstream file{fileName};
    ReadSentence(file, sentence);
    std::cout << sentence;
}

void ReadFromConsole()
{
    std::string line, sentence;
    while (std::getline(std::cin, line, '\n'))
    {
        if (not line.empty())
        {
            if (line == "exit")
                break;
            sentence += line;
            if (line[line.size() - 1] == '.')
            {
                sentence += '\n';
            }
            else
            {
                sentence += ' ';
            }
        }
    }
    std::cout << sentence;
}


void ReadFromFile()
{
    const std::string fileName{"../Resources/SoftwareQuotesInput.txt"};
    std::ifstream file{fileName};
    if (not file)
    {
        std::cerr << "Could not open file " << fileName << std::endl;
        return;
    }
    std::string line, text;
    while (std::getline(file, line, '\n'))
    {
        if (not line.empty())
        {
            text += line;
            if (line[line.size() - 1] == '.')
            {
                text += '\n';
            }
            else
            {
                text += ' ';
            }
        }
    }
    std::cout << text;
}

void ReadSentence(std::istream& istream, std::string& sentence)
{
    std::string line;
    while (std::getline(istream, line, '\n'))
    {
        if (not line.empty())
        {
            sentence += line;
            if (line[line.size() - 1] == '.')
            {
                sentence += '\n';
            }
            else
            {
                sentence += ' ';
            }
        }
    }
}

void WriteToFile(const std::string& text)
{
    const std::string fileName{"../Resources/SoftwareQuotesOutput.txt"};
    std::ofstream file{fileName};
    if (not file)
    {
        std::cerr << "Could not open file " << fileName << std::endl;
        return;
    }
    file << text;
}
