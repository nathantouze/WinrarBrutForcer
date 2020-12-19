#include "BrutForcerPool.hpp"
#include "WinrarBrutForcer.hpp"
#include <filesystem>
#include <boost/asio/io_service.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>
#include <thread>
#include <iostream>


BrutForcerPool::BrutForcerPool(const std::string &filepath, const std::unordered_map<std::string, bool> &charsEnabled) : _filepath(filepath), _charsEnabled(charsEnabled), \
_tmpDirectory(std::filesystem::temp_directory_path().string() + "winrarbrutforce-" + std::to_string(std::time(nullptr)))
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


void WinrarBrutForce(unsigned int characters, const std::string &filepath, const std::unordered_map<std::string, bool> &charsEnabled, const std::string &tmpDirectory)
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
    } else {
        std::cout << std::time(nullptr) - loop_time << " secondes for this loop with " << characters << " characters." << std::endl;
    }
}


void BrutForcerPool::start()
{
    boost::asio::io_service ioService;
    boost::thread_group threadpool;
    boost::asio::io_service::work work(ioService);
    std::vector<boost::thread *> threads;
    unsigned int cpu = std::thread::hardware_concurrency();
    
    for (unsigned int i = 0; i < cpu; i++)
        threads.push_back(threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &ioService)));
    for (unsigned int i = 1; i <= cpu; i++)
        ioService.post(boost::bind(WinrarBrutForce, i, _filepath, _charsEnabled, _tmpDirectory));
    while (1) {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        /*for (unsigned int i = 0; i < cpu; i++)
            if (threads.at(i)->interruption_requested())
                std::cout << "True" << std::endl;
            else
                std::cout << "False" << std::endl;*/
    }
    threadpool.join_all();
}