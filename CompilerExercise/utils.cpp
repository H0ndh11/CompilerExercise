#include "utils.h"

bool isDigit(char c) {
    if ('0' <= c && c <= '9') {
        return true; 
    }
    return false;
}

bool isIdenfitifierStartChar(char c) {
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
        return true;
    }
    return false; 
}

bool isIdentifierChar(char c) {
    return isDigit(c) || isIdenfitifierStartChar(c); 
}
