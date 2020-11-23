#include "unittest_exception.hpp"

mhl::UnitTestException::UnitTestException(const std::string& message,
                                          int error_code)
    : runtime_error(message), error_code_(error_code) {}

mhl::UnitTestException::~UnitTestException() {}