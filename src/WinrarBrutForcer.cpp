#include "WinrarBrutForcer.hpp"
#include <filesystem>
#include <ctime>
#include <iostream>

WinrarBrutForcer::WinrarBrutForcer(const std::string &filepath, const std::string &filename) : 
_filepath(filepath), _filename(filename), _tmpDirectory(std::filesystem::temp_directory_path().string() + "winrarbrutforce-" + std::to_string(std::time(nullptr)))
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


bool WinrarBrutForcer::completed_all_chars(const std::string &mdpTest) const
{
    for (int i = 0; mdpTest[i]; i++) {
        if (mdpTest[i] < 'z')
            return false;
    }
    return true;
}

void WinrarBrutForcer::reset_all_chars(std::string &mdpTest)
{
    for (int i = 0; mdpTest[i]; i++)
        mdpTest[i] = '0';
    mdpTest.append("0");
}

bool WinrarBrutForcer::test(const std::string &command, const std::string &password) const
{
    int ret = std::system(command.c_str());
    if (ret == 0) {
        std::cout << "---------------------- PASSWORD FOUND ----------------------" << std::endl << std::endl;
        std::cout << "Password: \"" << password << "\"" << std::endl;
        std::cout << "Press enter to exit...";
        std::cin.ignore();
        return true;
    }
    return false;
}

void WinrarBrutForcer::start()
{
    std::string mdpTest("0");
    std::string getter;
    long long loop_time = std::time(nullptr);
    long long start_time = std::time(nullptr);

    /* Check if the rar actually has a password, doesn't work for now
    if (std::system(std::string(UNRAR_EXEC + std::string(" E -INUL ") + _filepath + "/" + _filename + " " + _tmpDirectory).c_str()) == 0) {
        std::cout << "This file doesn't have any password." << std::endl;
        std::cout << "Press enter to exit...";
        std::cin.ignore();
        return;
    }*/
    while (1) {
        if (test(std::string(UNRAR_EXEC + std::string(" E -INUL -P\"") + mdpTest + "\" " + _filepath + "/" + _filename + " " + _tmpDirectory), mdpTest) == true) {
            std::cout << std::time(nullptr) - start_time << " secondes au total !" << std::endl;
            break;
        }

    // algo brutforce

        for (int i = 0; i < (int)mdpTest.length(); i++) {
            if (mdpTest[i] == 'z' && i < (int)mdpTest.length() - 1) {
                mdpTest[i] = '0';
            } else if (mdpTest[i] == 'z' && i == (int)mdpTest.length() - 1) {
                break;
            } else {
                if (mdpTest[i] == '9')
                    mdpTest[i] = 'A';
                else if (mdpTest[i] == 'Z')
                    mdpTest[i] = 'a';
                else {
                    mdpTest[i]++;
                }
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