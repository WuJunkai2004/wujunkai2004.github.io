#include "var.hpp"
#include "token_type.hpp"
#include "lox.hpp"

#include <string>
#include <ostream>


var::var(token_type type_, std::string_view value_):
    type(type_),
    value(value_)
{}


var::var(bool value_):
    type(value_ ? token_type::TRUE : token_type::FALSE),
    value("")
{}


var::var(int value_):
    type(token_type::NUMBER),
    value(std::to_string(value_))
{}

var::var(double value_):
    type(token_type::NUMBER),
    value(std::to_string(value_))
{}


var::var(long long value_):
    type(token_type::NUMBER),
    value(std::to_string(value_))
{}


var::var(std::string_view value_):
    type(token_type::STRING),
    value(value_)
{}


token_type var::get_type(){
    return type;
}

std::string var::get_value(){
    return value;
}

bool is_same_type(const var* a, const var* b){
    return a->type == b->type;
}


bool is_bool_type(const var* a){
    return a->type == token_type::TRUE || a->type == token_type::FALSE;
}


var var::operator+(var other){
    if(not is_same_type(this, &other)){
        lox::error(-1, "Cannot add different types");
        return var(token_type::NIL, "");
    }
    if(type == token_type::STRING){
        return var(token_type::STRING, value + other.value);
    } else if(type == token_type::NUMBER){
        return var(token_type::NUMBER, std::to_string(std::stod(value) + std::stod(other.value)));
    }
    lox::error(-1, "Cannot add with wrong types");
    return var(token_type::NIL, "");
}


var var::operator-(var other){
    if(type != token_type::NUMBER || not is_same_type(this, &other)){
        lox::error(-1, "Cannot subtract with wrong types");
        return var(token_type::NIL, "");
    }
    return var(token_type::NUMBER, std::to_string(std::stod(value) - std::stod(other.value)));
}


var var::operator*(var other){
    if(type != token_type::NUMBER || not is_same_type(this, &other)){
        lox::error(-1, "Cannot multiply with wrong types");
        return var(token_type::NIL, "");
    }
    return var(token_type::NUMBER, std::to_string(std::stod(value) * std::stod(other.value)));
}


var var::operator/(var other){
    if(type != token_type::NUMBER || not is_same_type(this, &other)){
        lox::error(-1, "Cannot divide with wrong types");
        return var(token_type::NIL, "");
    }
    return var(token_type::NUMBER, std::to_string(std::stod(value) / std::stod(other.value)));
}


var var::operator%(var other){
    if(type != token_type::NUMBER || not is_same_type(this, &other)){
        lox::error(-1, "Cannot modulo with wrong types");
        return var(token_type::NIL, "");
    }
    lox::error(-1, "Modulo not implemented");
    return var(token_type::NIL, "");
    //return var(token_type::NUMBER, std::to_string(std::stoi(value) % std::stoi(other.value)));
}


var var::operator==(var other){
    if(is_bool_type(this) && is_bool_type(&other)){
        return var((type == other.type) ? token_type::TRUE : token_type::FALSE, "");
    }
    if(not is_same_type(this, &other)){
        lox::error(-1, "Cannot compare different types");
        return var(token_type::NIL, "");
    }
    if(type == token_type::STRING){
        return var((value == other.value) ? token_type::TRUE : token_type::FALSE, "");
    }
    if(type == token_type::NUMBER){
        return var((std::stod(value) == std::stod(other.value)) ? token_type::TRUE : token_type::FALSE, "");
    }
    
    lox::error(-1, "Cannot compare with wrong types");
    return var(token_type::NIL, "");
}


var var::operator!=(var other){
    return *this == other == var(token_type::FALSE, "");
}


var var::operator<(var other){
    if(not is_same_type(this, &other) || (type != token_type::NUMBER && type != token_type::STRING)){
        lox::error(-1, "Cannot compare different types");
        return var(token_type::NIL, "");
    }
    if(type == token_type::STRING){
        return var((value < other.value) ? token_type::TRUE : token_type::FALSE, "");
    }
    return var((std::stod(value) < std::stod(other.value)) ? token_type::TRUE : token_type::FALSE, "");
}


var var::operator>=(var other){
    return *this < other == var(token_type::FALSE, "");
}


var var::operator>(var other){
    if(not is_same_type(this, &other) || (type != token_type::NUMBER && type != token_type::STRING)){
        lox::error(-1, "Cannot compare different types");
        return var(token_type::NIL, "");
    }
    if(type == token_type::STRING){
        return var((value > other.value) ? token_type::TRUE : token_type::FALSE, "");
    }
    return var((std::stod(value) > std::stod(other.value)) ? token_type::TRUE : token_type::FALSE, "");
}


var var::operator<=(var other){
    return *this > other == var(token_type::FALSE, "");
}


var::operator bool(){
    if(type != token_type::NUMBER && type != token_type::STRING && not is_bool_type(this)){
        lox::error(-1, "Cannot convert to bool");
        return false;
    }
    if(type == token_type::STRING){
        return not value.empty();
    }
    if(type == token_type::NUMBER){
        return std::stod(value) != 0;
    }
    return type == token_type::TRUE;
}


std::ostream& operator<<(std::ostream& os, const var& v){
    if(is_bool_type(&v)){
        os<< (v.type == token_type::TRUE ? "true" : "false");
    } else if(v.type == token_type::NIL){
        os<< "nil";
    } else {
        os<< v.value;
    }
    return os;
}
