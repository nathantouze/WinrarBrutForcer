#include "WinrarBrutForcer.hpp"
#include <filesystem>
#include <ctime>
#include <iostream>

WinrarBrutForcer::WinrarBrutForcer(const std::string &filepath, const std::string &filename, const std::unordered_map<std::string, bool> &charsEnabled) : \
_filepath(filepath), _filename(filename), _charsEnabled(charsEnabled), \
_tmpDirectory(std::filesystem::temp_directory_path().string() + "winrarbrutforce-" + std::to_string(std::time(nullptr)))
{
}

WinrarBrutForcer::~WinrarBrutForcer()
{
}

void WinrarBrutForcer::setup() const
{
    if (!std::filesystem::exists(UNRAR_BIN))
        std::filesystem::copy(UNRAR_LOCATION, ".");
    std::filesystem::create_directory(_tmpDirectory);
}

void WinrarBrutForcer::clear() const
{
    if (!std::filesystem::exists(UNRAR_BIN))
        std::filesystem::remove(UNRAR_BIN);
    std::filesystem::remove_all(_tmpDirectory);
}

char WinrarBrutForcer::first_char(int symbol_step) const
{
    if (_charsEnabled.at("symbols")) {
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
    if (_charsEnabled.at("numbers"))
        return '0';
    if (_charsEnabled.at("uppercase"))
        return 'A';
    if (_charsEnabled.at("lowercase"))
        return 'a';
    return 0;
}

char WinrarBrutForcer::first_char() const
{
    if (_charsEnabled.at("symbols"))
        return ' ';
    if (_charsEnabled.at("numbers"))
        return '0';
    if (_charsEnabled.at("uppercase"))
        return 'A';
    if (_charsEnabled.at("lowercase"))
        return 'a';
    return 0;
}


char WinrarBrutForcer::last_char() const
{
    if (_charsEnabled.at("symbols"))
        return '~';
    if (_charsEnabled.at("lowercase"))
        return 'z';
    if (_charsEnabled.at("uppercase"))
        return 'Z';
    if (_charsEnabled.at("numbers"))
        return '9';
    return 0;
}

char WinrarBrutForcer::following_symbol(char current) const
{
    if (current == '/' && _charsEnabled.at("numbers"))
        return '0';
    else if (current == '/')
        return first_char(1);
    if (current == '@' && _charsEnabled.at("uppercase"))
        return 'A';
    else if (current == '@')
        return first_char(2);
    if (current == '`' && _charsEnabled.at("lowercase"))
        return 'a';
    else if (current == '`')
        return first_char(3);
    return 0;
}

char WinrarBrutForcer::following_number(char current) const
{
    if (current == '9' && last_char() == '~')
        return current + 1;
    else if (current == '9' && last_char() == 'Z')
        return 'A';
    else if (current == '9')
        return 'a';
    std::cout << "bah merde alors !" << std::endl;
    return 0;
}

char WinrarBrutForcer::following_uppercase(char current) const
{
    if (current == 'Z' && last_char() == '~')
        return current + 1;
    else if (current == 'Z')
        return 'a';
    return 0;
}

char WinrarBrutForcer::following_lowercase(char current) const
{
    if (current == 'z' && last_char() == '~')
        return current + 1;
    return 0;
}

char WinrarBrutForcer::next_char(char current) const
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


bool WinrarBrutForcer::completed_all_chars(const std::string &mdpTest) const
{
    for (int i = 0; mdpTest[i]; i++) {
        if (mdpTest[i] < last_char())
            return false;
    }
    return true;
}

void WinrarBrutForcer::reset_all_chars(std::string &mdpTest)
{
    for (int i = 0; mdpTest[i]; i++)
        mdpTest[i] = first_char();
    mdpTest += first_char();
}

bool WinrarBrutForcer::test(const std::string &command, const std::string &password) const
{
    if (std::system(command.c_str()) == 0)
        return true;
    return false;
}

void WinrarBrutForcer::start()
{
    std::string mdpTest(1, first_char());
    long long loop_time = std::time(nullptr);
    long long start_time = std::time(nullptr);

    while (1) {
        if (test(std::string(UNRAR_EXEC + std::string(" E -INUL -P\"") + mdpTest + "\" " + _filepath + "/" + _filename + " " + _tmpDirectory), mdpTest)) {
            std::cout << "---------------------- PASSWORD FOUND ----------------------" << std::endl << std::endl;
            std::cout << "Password: \"" << mdpTest << "\"" << std::endl;
            std::cout << std::time(nullptr) - loop_time << " secondes pour cette loop." << std::endl;
            std::cout << std::time(nullptr) - start_time << " secondes au total !" << std::endl;
            std::cout << "Press enter to exit...";
            std::cin.ignore();
            break;
        }

    // algo brutforce
        for (int i = 0; i < (int)mdpTest.length(); i++) {
            if (mdpTest[i] == last_char() && i < (int)mdpTest.length() - 1) {
                mdpTest[i] = first_char();
            } else if (mdpTest[i] == last_char() && i == (int)mdpTest.length() - 1) {
                break;
            } else {
                mdpTest[i] = next_char(mdpTest[i]);
                break;
            }
        }
        if (completed_all_chars(mdpTest)) {
            reset_all_chars(mdpTest);
            std::cout << std::time(nullptr) - loop_time << " secondes pour cette loop." << std::endl;
            loop_time = std::time(nullptr);
        }
    }
}