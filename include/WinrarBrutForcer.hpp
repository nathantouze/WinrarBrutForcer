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

class WinrarBrutForcer {
    public:
        WinrarBrutForcer(const std::unordered_map<std::string, bool> &charsEnabled);
        ~WinrarBrutForcer();
        const std::string find_every_combination(const std::string &filepath, unsigned int length, const std::string &tmpDirectory);

    protected:
    private:
        bool test(const std::string &command) const;
        void reset_all_chars(std::string &passTest);
        char first_char(int step) const;
        char first_char() const;
        char last_char() const;
        char next_char(char current) const;
        char following_symbol(char current) const;
        char following_number(char current) const;
        char following_uppercase(char current) const;
        char following_lowercase(char current) const;
        std::unordered_map<std::string, bool> _charsEnabled;
};

#endif /* !WINRARBRUTFORCER_HPP_ */
