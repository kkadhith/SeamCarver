#ifndef DEBUGUTIL_HPP_
#define DEBUGUTIL_HPP_

#include <string>
#include <iostream>


[[noreturn]] void signal_error(const char *msg) {
    printf("Error: %s", msg);
    std::exit(1);
}


#endif  // DEBUGUTIL_HPP_
