//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016 
//

#ifndef HOMEWORK_DICTIONARY_H
#define HOMEWORK_DICTIONARY_H

template<class Container>
class Dictionary {
    Container words;
    const char *wordRegex = "([a-zA-Z][a-zA-Z'\\-]*)";

public:
    Dictionary(const std::string &input);

    Dictionary() { }

    uint64_t compareText(const std::string &input, const std::string &output);
};

#endif //HOMEWORK_DICTIONARY_H
