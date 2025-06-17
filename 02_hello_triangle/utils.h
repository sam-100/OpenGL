#ifndef UTILS_H
#define UTILS_H
#include <string>

void error(const char *msg, int error_code);
std::string load_file(const char *file_name);

#endif