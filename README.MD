# 📈 C++ Text Analyser 📈
## Description
<b>A simple tool to analyse a given text. Counts all of the words and their reoccurances, removing any possible gibberish.</b>

<b>A <i>cross-refererence</i> is also provided with every word.</b>

<b>This tool detects URL's in a text and prints them seperately.</b>

## Functionality
Data is stored in [std::map](https://en.cppreference.com/w/cpp/container/map) associative container, it contains key-value pairs with unique keys.
``` shell
std::map<std::string, std::pair<unsigned int, std::set<unsigned int>>> 
```
Occurances and lines are being stored in [std::pair](https://en.cppreference.com/w/cpp/utility/pair)

For example:

| Key (unique word)| Value (occurance) | Value (line)  |
| ------------- |:-------------:| -----:|
| ANN      | 4| 1 3 6 9  |
| this      | 3    |   1 5 8|
| zebra| 2      |    6 7 |

Links are stored in *std::set*

## Instructions
1. Compile the program with your preferred compiler. 
2. Make sure you have your input file and it's name matches the source code's input file name. By default <b><i>input.txt</i></b>
3. Run the program.
4. Choose whether you want to output to file or not.

## 📉Output📉
Depending on your choice the output will be one of the following:
* A file named <i>output.txt</i>
* The program will output to the terminal <i>std::cout</i>

Keys are sorted by using the comparison function, so the output is alphabeticaly ordered.

Example:
```shell
Word                                                   Occurances    Lines

ANN                                                    4             1 3 5 7 
An                                                     2             3 
Neurons                                                2             5 
The                                                    3             5 7 
```

