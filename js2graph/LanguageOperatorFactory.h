#ifndef LANGUAGEOPERATORFACTORY_H
#define LANGUAGEOPERATORFACTORY_H

#include <memory>
#include <unordered_map>
#include <string>

#include "../utils/common_using.h"

#include "LanguageOperator.h"

namespace FuzzFlow {

class LanguageOperatorFactory {
private:
    unordered_map<string,
                  shared_ptr<LanguageOperator>> pool;

    LanguageOperatorFactory() = default;

public:
    /// copy denied
    LanguageOperatorFactory(const LanguageOperatorFactory &) = delete;
    LanguageOperatorFactory &operator=(const LanguageOperatorFactory &) = delete;

    static LanguageOperatorFactory &instance()
    {
        static LanguageOperatorFactory inst;
        return inst;
    }

    shared_ptr<LanguageOperator> get(const string &label, const string &code)
    {
        string key = label + "#" + code;
        auto it = pool.find(key);
        if (it != pool.end()) {
            return it->second;
        }

        auto op = make_shared<LanguageOperator>(label, code);
        pool[key] = op;
        return op;
    }
};

} // FuzzFlow

#endif //LANGUAGEOPERATORFACTORY_H
