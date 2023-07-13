#pragma once

#include <string>
#include <iostream>


[[noreturn]] void signal_error(const char *msg) {
    printf("Error: %s", msg);
    std::exit(1);
}
