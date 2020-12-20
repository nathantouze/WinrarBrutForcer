#include "BrutForcerPool.hpp"
#include "WinrarBrutForcer.hpp"
#include <filesystem>
#include <boost/asio/io_service.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>
#include <thread>
#include <iostream>


BrutForcerPool::BrutForcerPool(const std::string &filepath, const std::unordered_map<std::string, bool> &charsEnabled) : _filepath(filepath), _charsEnabled(charsEnabled), \
_tmpDirectory(std::filesystem::temp_directory_path().string() + "winrarbrutforce-" + std::to_string(std::time(nullptr))), _maxLength(10)
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
    if (!std::filesystem::exists(UNRAR_BIN))
        std::filesystem::remove(UNRAR_BIN);
    std::filesystem::remove_all(_tmpDirectory);
}


bool BrutForcerPool::brutforce(unsigned int characters, const std::string &filepath, const std::unordered_map<std::string, bool> &charsEnabled, const std::string &tmpDirectory)
{
    WinrarBrutForcer brutforcer(charsEnabled);
    long long loop_time = std::time(nullptr);

    const std::string password = brutforcer.find_every_combination(filepath, characters, tmpDirectory);
    if (password.size() != 0) {
        std::cout << "---------------------- PASSWORD FOUND ----------------------" << std::endl << std::endl;
        std::cout << "Password: \"" << password << "\"" << std::endl;
        std::cout << std::time(nullptr) - loop_time << " seconds for this loop." << std::endl;
        std::cout << "Press enter to exit...";
        std::cin.ignore();
        return true;
    } else {
        std::cout << std::time(nullptr) - loop_time << " secondes for this loop with " << characters << " characters.\n";
        return false;
    }
}


void BrutForcerPool::start()
{
    for (unsigned int i = 1; i < _maxLength; i++) {
        if (brutforce(i, _filepath, _charsEnabled, _tmpDirectory))
            break;
    }
}