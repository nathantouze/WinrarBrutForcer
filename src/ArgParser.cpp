#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include "ArgParser.hpp"
#include "ArgParserException.hpp"
#include "Macros.hpp"

ArgParser::ArgParser(int ac, char **av) : _ac(ac), _av(av), _filename(""), _filepath(""), _helping(false), _debugMod(false)
{
    if (ac == 2 && std::string(av[1]) == HELPER_ARG) {
        std::cout << "USAGE: ./RarBrutForcer [filepath] [filename]" << std::endl;
        std::cout << "\tfilepath\tAbsolute path to the folder containing the file." << std::endl;
        std::cout << "\tfilename\tName of the file (extension required: .rar, .zip)." << std::endl << std::endl;
        std::cout << "Optional flags:" << std::endl;
        std::cout << "\t-h\t\tDisplay helper." << std::endl;
        std::cout << "\t-d, --debug\tDisplay all debug informations." << std::endl;
        std::cout << "\t-a, --all\tEnable all characters to the research." << std::endl;
        std::cout << "\t-l, --lowercase\tEnable lowercase characters to the research (enabled by default)." << std::endl;
        std::cout << "\t-u, --uppercase\tEnable uppercase characters to the research." << std::endl;
        std::cout << "\t-n, --numbers\tEnable numbers to the research." << std::endl;
        std::cout << "\t-s, --symbols\tEnable symbols to the research." << std::endl;
        _helping = true;
    }
    if (ac > 1) {
        for (int i = 1; av[i]; i++) {
            if (std::string(av[i]) == DEBUG_ARG || std::string(av[i]) == DEBUG_ARG_ALT)
                _debugMod = true;
        }
    }
    _charsEnabled.insert({"lowercase", true});
    _charsEnabled.insert({"uppercase", false});
    _charsEnabled.insert({"numbers", false});
    _charsEnabled.insert({"symbols", false});
}

ArgParser::~ArgParser()
{
}

const std::string &ArgParser::getFilename() const
{
    return _filename;
}

const std::string &ArgParser::getFilepath() const
{
    return _filepath;
}

bool ArgParser::getHelping() const
{
    return _helping;
}

bool ArgParser::getDebugMod() const
{
    return _debugMod;
}

const std::unordered_map<std::string, bool> &ArgParser::getCharsEnabled() const
{
    return _charsEnabled;
}

bool ArgParser::isOptionalFlag(const std::string &arg) const
{
    if (arg == HELPER_ARG || arg == DEBUG_ARG || arg == DEBUG_ARG_ALT || \
        arg == ALL_ARG || arg == ALL_ARG_ALT || arg == LOWER_ARG || \
        arg == LOWER_ARG_ALT || arg == UPPER_ARG || arg == UPPER_ARG_ALT || \
        arg == SYMBOLS_ARG || arg == SYMBOLS_ARG_ALT || arg == NUMBER_ARG || \
        arg == NUMBER_ARG_ALT)
        return true;
    return false;
}

void ArgParser::printFileInfos() const
{
    if (_filepath != "")
        std::cout << "Filepath: " << _filepath << std::endl;
    if (_filename != "")
        std::cout << "Filename: " << _filename << std::endl;
}

void ArgParser::fill_from_args()
{
    int nthArg = 0;

    for (int i = 1; _av[i]; i++) {
        std::string arg(_av[i]);
        if (!isOptionalFlag(arg) && nthArg == 0) {
            _filepath = arg;
            nthArg++;
            continue;
        }
        if (!isOptionalFlag(arg) && nthArg == 1) {
            _filename = arg;
            nthArg++;
            continue;
        }
        if (!isOptionalFlag(arg) && nthArg > 1)
            throw ArgParserException("Too many arguments");
    }
}

void ArgParser::fill_from_stdin()
{
    while (_filepath == "") {
        std::cout << "Filepath: ";
        std::getline(std::cin, _filepath);
    }
    while (_filename == "") {
        std::cout << "Filename: ";
        std::getline(std::cin, _filename);
    }
}

bool ArgParser::is_flag_inside(const std::string &flag)
{
    for (int i = 0; _av[i]; i++) {
        if (std::string(_av[i]) == flag)
            return true;
    }
    return false;
}

void ArgParser::enable_characters()
{
    if (is_flag_inside(ALL_ARG_ALT) || is_flag_inside(ALL_ARG)) {
        _charsEnabled["uppercase"] = true;
        _charsEnabled["numbers"] = true;
        _charsEnabled["symbols"] = true;
        return;
    }
    if (is_flag_inside(UPPER_ARG) || is_flag_inside(UPPER_ARG_ALT))
        _charsEnabled["uppercase"] = true;
    if (is_flag_inside(NUMBER_ARG) || is_flag_inside(NUMBER_ARG_ALT))
        _charsEnabled["numbers"] = true;
    if (is_flag_inside(SYMBOLS_ARG) || is_flag_inside(SYMBOLS_ARG_ALT))
        _charsEnabled["symbols"] = true;
}

void ArgParser::fill_labels()
{
    enable_characters();
    if (_ac > 1) {
        fill_from_args();
    }
    fill_from_stdin();
    if (_debugMod)
        printFileInfos();
}

void ArgParser::check_labels() const
{
    std::fstream file;
    std::string extension;

    if (!std::filesystem::exists(_filepath))
        throw ArgParserException("Cannot open filepath. Maybe the directory doesn't exist.");
    if (_filename.find_last_of('.') == std::string::npos)
        throw ArgParserException("The file submitted is not a RAR or ZIP file.");
    extension = _filename.substr(_filename.find_last_of('.'));
    if (extension != EXT_RAR && extension != EXT_ZIP)
        throw ArgParserException("The file submitted is not a RAR or ZIP file.");
    if (!std::filesystem::exists(_filepath + '/' + _filename))
        throw ArgParserException("Cannot open file. Maybe the file doesn't exist.");
}