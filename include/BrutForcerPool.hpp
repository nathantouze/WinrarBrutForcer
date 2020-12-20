#ifndef BRUTFORCERPOOL_HPP_
#define BRUTFORCERPOOL_HPP_

#include <string>
#include <unordered_map>

#ifdef _WIN32
    #define UNRAR_BIN "Unrar.exe"
    #define UNRAR_EXEC "UNRAR"
    #define UNRAR_LOCATION "C:\\Program Files\\WinRAR\\Unrar.exe"
#else
    #define UNRAR_BIN "unrar"
    #define UNRAR_EXEC "./unrar"
    #define UNRAR_LOCATION "/usr/local/bin/unrar"
#endif

class BrutForcerPool {
    public:
        BrutForcerPool(const std::string &filepath, const std::unordered_map<char, bool> &charsEnabled);
        ~BrutForcerPool();
        void setup() const;
        void clear() const;
        void start();
    protected:
    private:
        bool brutforce(unsigned int &characters, const std::string &filepath, const std::unordered_map<char, bool> &charsEnabled, const std::string &tmpDirectory);
        std::string _filepath;
        std::unordered_map<char, bool> _charsEnabled;
        std::string _tmpDirectory;
        unsigned int _maxLength;

};

#endif /* !BRUTFORCERPOOL_HPP_ */
