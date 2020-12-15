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

class WinrarBrutForcer {
    public:
        WinrarBrutForcer(const std::string &filepath, const std::string &filename);
        ~WinrarBrutForcer();
        void setup() const;
        void clear() const;
        void start();

    protected:
    private:
        bool test(const std::string &command, const std::string &password) const;
        bool completed_all_chars(const std::string &mdpTest) const;
        void reset_all_chars(std::string &mdpTest);
        std::string _filepath;
        std::string _filename;
        std::string _tmpDirectory;
};

#endif /* !WINRARBRUTFORCER_HPP_ */
