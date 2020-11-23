#include "argument_exception.hpp"

mhl::ArgumentException::ArgumentException(const std::string& message,
                                          int error_code)
    : runtime_error(message), error_code_(error_code) {}

mhl::ArgumentException::~ArgumentException() {}