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
        WinrarBrutForcer(const std::string &filepath, const std::string &filename, const std::unordered_map<std::string, bool> &charsEnabled);
        ~WinrarBrutForcer();
        void setup() const;
        void clear() const;
        void start();

    protected:
    private:
        bool test(const std::string &command, const std::string &password) const;
        bool completed_all_chars(const std::string &mdpTest) const;
        void reset_all_chars(std::string &mdpTest);
        char first_char(int step) const;
        char first_char() const;
        char last_char() const;
        char next_char(char current) const;
        char following_symbol(char current) const;
        char following_number(char current) const;
        char following_uppercase(char current) const;
        char following_lowercase(char current) const;
        std::string _filepath;
        std::string _filename;
        std::unordered_map<std::string, bool> _charsEnabled;
        std::string _tmpDirectory;
};

#endif /* !WINRARBRUTFORCER_HPP_ */
