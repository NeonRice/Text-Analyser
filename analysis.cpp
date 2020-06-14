#include <iostream>
#include <map>     // A map will be used to count the words.
#include <fstream> // Will be used to read from a file.
#include <string>  // The map's key value.
#include <set>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <algorithm>

// Function to output our results from a map and a (possibly empty) links set.
template <class KTy, class Ty, class X>
void Output(std::ostream &s, std::map<KTy, Ty> map, std::set<X> links)
{
    if (s.bad()) // Failbit
        throw "Bad ostream given.";

    typedef typename std::map<KTy, Ty>::iterator iterator;
    s << std::left << std::setw(55) << "Word" << std::setw(14) << "Occurances" // Header of output
      << "Lines"
      << "\n\n";
    for (iterator p = map.begin(); p != map.end(); p++) // Printing "Lines" of occurance
    {
        s << std::left << std::setw(55) << p->first << std::setw(14) << p->second.first;
        for (auto linePos : p->second.second)
            s << linePos << " ";
        s << std::endl;
    }
    if (links.size()) // If there are links we print
    {
        s << "\n\nLinks extracted from text:" << std::endl;
        for (auto i : links)
            s << i << std::endl;
    }
}

// Function that returns a set of URL's from a given map.
template <class KTy, class Ty>
std::set<std::string> getLinksFromMap(std::map<KTy, Ty> &map)
{
    std::set<std::string> validLinks{"https://", "http://", "www."}, links;
    for (std::string linkPrefix : validLinks)
    {
        for (auto &[key, value] : map)
        {
            std::string prefix = key.substr(0, linkPrefix.size());
            if (linkPrefix == prefix)
            {
                std::string link = key;
                if (linkPrefix != "www.")
                    link.insert(link.begin() + linkPrefix.size() - 2, ':');
                links.insert(link);
            }
        }
    }
    return links;
}

bool isUrl(const std::string &URL)
{
    std::set<std::string> validLinks{
        "https://",
        "http://",
        "www.",
    },
        links;
    for (std::string linkPrefix : validLinks)
    {
        std::string prefix = URL.substr(0, linkPrefix.size());
        if (linkPrefix == prefix)
        {
            if (isalpha(URL.back()))
                return (std::count(std::begin(URL) + prefix.size(), std::end(URL), '.') >= 1);
        }
    }
    return false;
}

std::string removeNonUrl(const std::string &str)
{
    std::string modifiedStr = str;
    for (auto i = modifiedStr.begin(); i != modifiedStr.end(); ++i)
    {
        if(ispunct(*i) && *i != '.' && *i != '/' && *i != ':')
        {
            modifiedStr.erase(std::remove(std::begin(modifiedStr), std::end(modifiedStr), *i));
            --i;
        }
    }
    return modifiedStr;
}

std::string removeNotAlNum(const std::string &str)
{
    std::string modifiedStr = str;
    for (auto i = modifiedStr.begin(); i != modifiedStr.end(); ++i)
    {
        if(!isalnum
        (*i))
        {
            modifiedStr.erase(std::remove(std::begin(modifiedStr), std::end(modifiedStr), *i));
            --i;
        }
    }
    return modifiedStr;
}

// Function that returns a map from a given file (specified by fileName). If you give it a vector it fills it with links.
template <class BoolCallbackFunction>
auto readMapFromFile(BoolCallbackFunction boolFunction, std::set<std::string> &boolSorted,
                     const std::string &fileName = "input.txt", const bool removeSpecialFromMap = true)
{
    // Will store the word and count.
    std::map<std::string, std::pair<unsigned int, std::set<unsigned int>>> wordsCount;
    // Reading from file
    std::ifstream fileStream(fileName);
    if (fileStream.is_open()) // Checking if we opened the file successfully
    {
        // Store the next word in the file in a local variable.
        std::string word;
        unsigned int lineCnt = 1;

        for (std::string line; std::getline(fileStream, line); ++lineCnt) // Function to loop through lines...
        {
            std::stringstream ss(line); // For reading words.
            while (ss >> word)
            {
                const bool specialCase = boolFunction(word);
                if (specialCase)
                {
                    word = removeNonUrl(word);
                    boolSorted.insert(word);
                    if (removeSpecialFromMap)   // If we don't need the special case in our map
                        continue; // We're done processing the special case here... Move on
                }   

                word = removeNotAlNum(word);

                if (word.empty()) // If a word is empty, continue :))
                    continue;

                if (wordsCount.find(word) == wordsCount.end()) // New Key
                {
                    wordsCount[word].first = 1; // Initialize it to 1.
                    wordsCount[word].second.insert(lineCnt);
                }
                else // Not a new key
                {
                    ++wordsCount[word].first; // Increment it.
                    wordsCount[word].second.insert(lineCnt);
                }
            }
        }
        fileStream.close();
        return wordsCount;
    }
    else // Can't open the file. Throw an error.
        throw "Couldn't open the file.";
}

int main(void)
{
    try
    {
        std::set<std::string> links;
        auto map = readMapFromFile(isUrl, links);
        // Print the words map.
        //Output(std::cout, map, links);
        std::ofstream s("output.txt");
        Output(s, map, links);

        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
}