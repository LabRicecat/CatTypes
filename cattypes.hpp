#ifndef CAT_TYPES_HPP
#define CAT_TYPES_HPP

#include <vector>
#include <map>
#include <string>

namespace Cattype {
    bool is_number(std::string str) {
        return str.size() == 1 &&
            str[0] >= '0' && str[0] <= '9';
    }
    bool is_all_numbers(std::string str) {
        for(auto i : str)
            if(!is_number(std::string(1,i))) return false;
        return true;
    }
    bool is_string(std::string str) {
        if(str.size() < 2) return false;
        bool c = 0;
        for(size_t i = 0; i < str.size(); ++i) {
            if(c == 0 && i != 0) return false;
            if(str[i] == '"') c = !c;
        }
        return true;
    }
    bool is_bool(std::string str) {
        return str == "true" ||
            str == "True" ||
            str == "TRUE" ||
            str == "false" ||
            str == "False" ||
            str == "FALSE";
    }
    bool is_letter(std::string str) {
        return str.size() == 1 && 
            (str[0] >= 'a' && str[0] <= 'z') ||
            (str[0] >= 'A' && str[0] <= 'Z');
    }
    bool is_name_char(std::string str) {
        return str.size() == 1 && (
            is_letter(str) ||
            str[0] == '_' ||
            str[0] == '@' ||
            str[0] == '$'
        );
    }
    bool is_name(std::string str) {
        for(auto i : str)
            if(!is_name_char(std::string(1,i))) return false;
        return true;
    }
    bool is_math_sym(std::string str) {
        return str.size() == 1 && (
            str[0] == '+' ||
            str[0] == '-' ||
            str[0] == '*' ||
            str[0] == '/' ||
            str[0] == '<' ||
            str[0] == '>' ||
            str[0] == '&' ||
            str[0] == '>' ||
            str[0] == '~' ||
            str[0] == '%' ||
            str[0] == '!' ||
            str[0] == '='
        );
    }
    bool is_all_math_sym(std::string str) {
        for(auto i : str)
            if(!is_math_sym(std::string(1,i))) return false;
        return true;
    }
};

using cat_analyzer_function = bool(*)(std::string);
struct CatAnalyzer {
    struct TypePosibilities {
        std::map<std::string,int> pos;

        operator std::vector<std::string>() const {
            return to_vector();
        }
        inline operator std::map<std::string,int>() const {
            return pos;
        }

        inline bool matches(std::string type) const {
            return pos.count(type) != 0;
        }

        inline std::vector<std::string> to_vector() const {
            std::vector<std::string> ret;
            for(auto i : pos)
                ret.push_back(i.first);
            return ret;
        }

        inline int& operator[](std::string ty) {
            return pos[ty];
        }
    };

    std::map<std::string,cat_analyzer_function> types;

    inline CatAnalyzer& add_type(std::string name, cat_analyzer_function func) {
        types[name] = func;
        return *this;
    }

    TypePosibilities analyze(std::string context) {
        TypePosibilities ret;
        for(auto i : types)
            if(i.second(context)) ret[i.first] = true;
        return ret;
    }

};

#endif