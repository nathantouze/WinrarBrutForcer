#ifndef WINRARBRUTFORCER_HPP_
#define WINRARBRUTFORCER_HPP_

#ifdef _WIN32
    #define UNRAR_BIN "Unrar.exe"
    #define UNRAR_EXEC "UNRAR"
    #define UNRAR_LOCATION "C:\\Program Files\\WinRAR\\Unrar.exe"
#else
    #define UNRAR_BIN "unrar"
    #define UNRAR_EXEC "./unrar"
    #define UNRAR_LOCATION "/usr/local/bin/unrar"
#endif


#include <string>
#include <unordered_map>
#include <thread>
#include <vector>

class WinrarBrutForcer {
    public:
        WinrarBrutForcer(const std::unordered_map<char, bool> &charsEnabled);
        ~WinrarBrutForcer();
        bool find_every_combination(const std::string &filepath, unsigned int &length, const std::string &tmpDirectory);
        const std::string &getPassword() const;

    protected:
    private:
        bool test(const std::string &command) const;
        void reset_all_chars(std::string &passTest);
        char first_char(int step) const;
        char first_char() const;
        char last_char() const;
        char next_char(const char &current) const;
        char following_symbol(const char &current) const;
        char following_number(const char &current) const;
        char following_uppercase(const char &current) const;
        char following_lowercase(const char &current) const;
        void tester(std::string passTest, const std::string filepath, const std::string tmpDirectory);
        std::thread testerer(std::string passTest, const std::string filepath, const std::string tmpDirectory);

        std::unordered_map<char, bool> _charsEnabled;
        std::vector<std::thread> _threads;
        std::string _password;
};

#endif /* !WINRARBRUTFORCER_HPP_ */
