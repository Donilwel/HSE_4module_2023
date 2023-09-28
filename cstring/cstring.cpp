#define sc static_cast<int>
#include "cstring.h"

size_t Strlen(const char* str) {
    size_t l = 0;
    while (str[l] != '\0') {
        ++l;
    }
    return l;
}

int Strcmp(const char* first, const char* second) {
    while (*first && (*first == *second)) {
        ++second;
        ++first;
    }
    return sc(*first) - sc(*second);
}
char* Strcpy(char* dest, const char* src) {
    char* s = dest;
    while ((*dest = *src)) {
        dest++;
        src++;
    }
    return s;
}
int Strncmp(const char* first, const char* second, size_t count) {
    while (count && *first && *first == *second) {
        --count;
        ++first;
        ++second;
    }
    if (count != 0) {
        return sc(*first) - sc(*second);
    }
    return 0;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    char* s = dest;
    while (count && (*dest++ = *src++)) {
        --count;
    }
    while (count--) {
        *dest++ = '\0';
    }
    return s;
}
const char* Strchr(const char* str, char symbol) {
    while (*str != symbol) {
        if (!(*str++)) {
            return nullptr;
        }
    }
    return str;
}
char* Strcat(char* dest, const char* src) {
    char* s = dest;
    while (*dest) {
        ++dest;
    }
    while ((*dest++ = *src++)) {
    }
    return s;
}

char* Strncat(char* dest, const char* src, size_t count) {
    char* s = dest;
    while (*dest) {
        ++dest;
    }
    while (count && (*dest++ = *src++)) {
        --count;
    }
    if (count) {
        *dest = '\0';
    }
    return s;
}

const char* Strrchr(const char* str, char symbol) {
    const char* l = 0;
    if (symbol == '\0') {
        return str + Strlen(str);
    }
    while (*str) {
        if (*str == symbol) {
            l = str;
        }
        str++;
    }
    return l;
}
const char* Strpbrk(const char* dest, const char* breakset) {
    const char* ptr = nullptr;
    while (*dest) {
        for (ptr = breakset; *ptr && *dest != *ptr; ++ptr) {
        }
        if (*ptr) {
            return dest;
        }
        ++dest;
    }
    return nullptr;
}
size_t Strspn(const char* dest, const char* src) {
    const char* ptr = src;
    size_t count = 0;
    while (*dest) {
        for (ptr = src; *ptr && *dest != *ptr; ++ptr) {
        }
        if (*ptr) {
        } else {
            break;
        }
        ++count;
        ++dest;
    }
    return count;
}

size_t Strcspn(const char* dest, const char* src) {
    const char* ptr = src;
    size_t count = 0;
    while (*dest) {
        for (ptr = src; *ptr && *dest != *ptr; ++ptr) {
        }
        if (*ptr) {
            break;
        }
        ++count;
        ++dest;
    }
    return count;
}

const char* Strstr(const char* str, const char* pattern) {
    if (!*pattern) {
        return str;
    }
    const char* part_1 = str;
    const char* part_2 = pattern;
    while (*part_1 && *part_2) {
        if (*part_1 == *part_2) {
            ++part_1;
            ++part_2;
        } else {
            part_1 = ++str;
            part_2 = pattern;
        }
    }
    if (*part_2) {
        return 0;
    } else {
        return str;
    }
}
