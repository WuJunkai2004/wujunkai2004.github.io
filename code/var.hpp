#pragma once

#ifndef __VAR_HPP__
#define __VAR_HPP__

#include <string>
#include <ostream>

#include "token_type.hpp"
#include "lox.hpp"

class var{
private:
    token_type type;
    std::string value;
public:
    var() = default;
    var(token_type, std::string_view);

    // bool
    var(bool);

    // number
    var(int);
    var(double);
    var(long long);

    // string
    var(std::string_view);

    token_type  get_type();
    std::string get_value();

    var operator+(var);
    var operator-(var);
    var operator*(var);
    var operator/(var);
    var operator%(var);

    var operator==(var);
    var operator!=(var);
    var operator<(var);
    var operator>(var);
    var operator<=(var);
    var operator>=(var);

    operator bool();

    friend bool is_same_type(const var*, const var*);
    friend bool is_bool_type(const var*);

    //friend std::ostream& operator<<(std::ostream&, const var);
    friend std::ostream& operator<<(std::ostream&, const var&);
};

bool is_same_type(const var*, const var*);
bool is_bool_type(const var*);


//std::ostream& operator<<(std::ostream&, const var);
std::ostream& operator<<(std::ostream&, const var&);

#endif // __VAR_HPP__