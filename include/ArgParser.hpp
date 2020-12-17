#ifndef ARGPARSER_HPP_
#define ARGPARSER_HPP_

#include <string>
#include <unordered_map>

class ArgParser {
    public:
        ArgParser(int ac, char **av);
        ~ArgParser();
        const std::string &getFilepath() const;
        const std::string &getFilename() const;
        bool getHelping() const;
        bool getDebugMod() const;
        const std::unordered_map<std::string, bool> &getCharsEnabled() const;
        void fill_labels();
        void check_labels() const;
    protected:
    private:
        bool isOptionalFlag(const std::string &arg) const;
        void printFileInfos() const;
        void fill_from_args();
        void fill_from_stdin();
        void enable_characters();
        bool is_flag_inside(const std::string &flag);
        int _ac;
        char **_av;
        std::string _filename;
        std::string _filepath;
        bool _helping;
        bool _debugMod;
        std::unordered_map<std::string, bool> _charsEnabled;
};

#endif /* !ARGPARSER_HPP_ */
