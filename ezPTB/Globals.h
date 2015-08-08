#ifndef GLOBALS_H
#define GLOBALS_H

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/lexical_cast.hpp>

typedef boost::multiprecision::cpp_dec_float_100 dec_float_100;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1000>> dec_float_1000;
typedef dec_float_1000 mpnum;

#endif