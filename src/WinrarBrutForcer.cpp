#include "WinrarBrutForcer.hpp"
#include <filesystem>
#include <ctime>
#include <iostream>

WinrarBrutForcer::WinrarBrutForcer(const std::unordered_map<char, bool> &charsEnabled) : _charsEnabled(charsEnabled)
{
}

WinrarBrutForcer::~WinrarBrutForcer()
{
}

char WinrarBrutForcer::first_char(int symbol_step) const
{
    if (_charsEnabled.at('s')) {
        switch (symbol_step) {
        case 0:
            return ' ';
        case 1:
            return ':';
        case 2:
            return '[';
        case 3:
            return '{';
        default:
            return 0;
        }
    }
    if (_charsEnabled.at('n'))
        return '0';
    if (_charsEnabled.at('u'))
        return 'A';
    if (_charsEnabled.at('l'))
        return 'a';
    return 0;
}

char WinrarBrutForcer::first_char() const
{
    if (_charsEnabled.at('s'))
        return ' ';
    if (_charsEnabled.at('n'))
        return '0';
    if (_charsEnabled.at('u'))
        return 'A';
    if (_charsEnabled.at('l'))
        return 'a';
    return 0;
}


char WinrarBrutForcer::last_char() const
{
    if (_charsEnabled.at('s'))
        return '~';
    if (_charsEnabled.at('l'))
        return 'z';
    if (_charsEnabled.at('u'))
        return 'Z';
    if (_charsEnabled.at('n'))
        return '9';
    return 0;
}

char WinrarBrutForcer::following_symbol(const char &current) const
{
    if (current == '/' && _charsEnabled.at('n'))
        return '0';
    else if (current == '/')
        return first_char(1);
    if (current == '@' && _charsEnabled.at('u'))
        return 'A';
    else if (current == '@')
        return first_char(2);
    if (current == '`' && _charsEnabled.at('l'))
        return 'a';
    else if (current == '`')
        return first_char(3);
    return 0;
}

char WinrarBrutForcer::following_number(const char &current) const
{
    if (current == '9' && last_char() == '~')
        return current + 1;
    else if (current == '9' && last_char() == 'Z')
        return 'A';
    else if (current == '9' && last_char() == 'z')
        return 'a';
    return 0;
}

char WinrarBrutForcer::following_uppercase(const char &current) const
{
    if (current == 'Z' && last_char() == '~')
        return current + 1;
    else if (current == 'Z' && last_char() == 'z')
        return 'a';
    return 0;
}

char WinrarBrutForcer::following_lowercase(const char &current) const
{
    if (current == 'z' && last_char() == '~')
        return current + 1;
    return 0;
}

char WinrarBrutForcer::next_char(const char &current) const
{
    char ret;

    if (current != last_char() && current != '/' && current != '@' && \
    current != '`' && current != '9' && current != 'Z' && current != 'z')
        return current + 1;
    if ((ret = following_symbol(current)) != 0)
        return ret;
    if ((ret = following_number(current)) != 0)
        return ret;
    if ((ret = following_uppercase(current)) != 0)
        return ret;
    return following_lowercase(current);
}

void WinrarBrutForcer::reset_all_chars(std::string &passTest)
{
    for (unsigned int i = 0; passTest[i]; ++i)
        passTest[i] = first_char();
    passTest += first_char();
}

bool WinrarBrutForcer::test(const std::string &command) const
{
    if (std::system(command.c_str()) == 0)
        return true;
    return false;
}

const std::string WinrarBrutForcer::find_every_combination(const std::string &filepath, unsigned int &length, const std::string &tmpDirectory)
{
    std::string passTest(length, first_char());

    while (1) {
        if (test(UNRAR_EXEC + std::string(" E -INUL -P\"") + passTest + "\" " + filepath + " " + tmpDirectory))
            return passTest;

        for (unsigned int i = 0; i < length; ++i) {
            if (passTest[i] == last_char() && i < length - 1) {
                passTest[i] = first_char();
            } else if (passTest[i] == last_char()) {
                return "";
            } else {
                passTest[i] = next_char(passTest[i]);
                break;
            }
        }
    }
}

// 22 secondes (numbers / Windows)
// 12 secondes (numbers / Ubuntu)