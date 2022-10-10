#include "BrutForcerPool.hpp"
#include "WinrarBrutForcer.hpp"
#include <filesystem>
#include <thread>
#include <iostream>


BrutForcerPool::BrutForcerPool(const std::string &filepath, const std::unordered_map<char, bool> &charsEnabled, bool debug) : _filepath(filepath), _charsEnabled(charsEnabled), \
_tmpDirectory(std::filesystem::temp_directory_path().string() + "/winrarbrutforce-" + std::to_string(std::time(nullptr))), _maxLength(10), _debug(debug)
{
}

BrutForcerPool::~BrutForcerPool()
{
}

void BrutForcerPool::setup() const
{
    if (!std::filesystem::exists(UNRAR_BIN))
        std::filesystem::copy(UNRAR_LOCATION, ".");
    std::filesystem::create_directory(_tmpDirectory);
}

void BrutForcerPool::clear() const
{
    if (std::filesystem::exists(UNRAR_BIN))
        std::filesystem::remove(UNRAR_BIN);
    std::filesystem::remove_all(_tmpDirectory);
}

void BrutForcerPool::print_char_infos() const
{
    std::cout << "\nCharacters enabled: " << std::endl;
    if (_charsEnabled.at('l'))
        std::cout << "- Lowercase letters" << std::endl;
    if (_charsEnabled.at('u'))
        std::cout << "- Uppercase letters" << std::endl;
    if (_charsEnabled.at('n'))
        std::cout << "- Numbers" << std::endl;
    if (_charsEnabled.at('s'))
        std::cout << "- Symbols" << std::endl;
    std::cout << std::endl;
}

bool BrutForcerPool::brutforce(unsigned int &characters, const std::string &filepath, const std::unordered_map<char, bool> &charsEnabled, const std::string &tmpDirectory)
{
    WinrarBrutForcer brutforcer(charsEnabled);
    long long loop_time = std::time(nullptr);

    if (brutforcer.find_every_combination(filepath, characters, tmpDirectory)) {
        std::cout << std::endl << "---------------------- PASSWORD FOUND ----------------------" << std::endl << std::endl;
        std::cout << "Password: \"" << brutforcer.getPassword() << "\"" << std::endl;
        if (_debug)
            std::cout << std::time(nullptr) - loop_time << " seconds with " << characters << " characters.\n";
        return true;
    } else {
        if (_debug)
            std::cout << std::time(nullptr) - loop_time << " seconds with " << characters << " characters.\n";
        return false;
    }
}


void BrutForcerPool::start()
{
    long long start_time = std::time(nullptr);

    if (_debug)
        print_char_infos();
    std::cout << "---------------------- PASSWORD SEARCH ---------------------" << std::endl << std::endl;
    for (unsigned int i = 1; i < _maxLength; i++) {
        if (brutforce(i, _filepath, _charsEnabled, _tmpDirectory)) {
            if (_debug)
                std::cout << "Total time: " << std::time(nullptr) - start_time << " seconds." << std::endl;
            std::cout << "Press enter to exit...";
            std::cin.ignore();
            break;
        }
    }
}