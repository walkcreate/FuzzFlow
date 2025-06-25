#ifndef FUZZFLOW_LOGGER_H
#define FUZZFLOW_LOGGER_H

#include <string>

using std::string;

enum class LogLevel {
    verbose,
    info,
    warning,
    error,
    fatal
};

bool is_at_least() {

}

class Logger {

public:

    string label;

    Logger(string label) {
        this->label = label;
    }

    void log(string message, LogLevel level) {
    }

    void verbose(string msg) {
        log(msg, LogLevel::verbose);
    }

    void info(string msg) {
        log(msg, LogLevel::info);
    }

    void warning(string msg) {
        log(msg, LogLevel::warning);
    }

    void error(string msg) {
        log(msg, LogLevel::error);
    }

    void fatal(string msg) {
        log(msg, LogLevel::fatal);

        //Fuzzer fuzzer = Fuzzer::current();
        //fuzzer.shutdown(LogLevel::fatal);

        // If the process hasn't terminated yet, just abort now.
        abort();
    }

private:

};


#endif //FUZZFLOW_LOGGER_H
