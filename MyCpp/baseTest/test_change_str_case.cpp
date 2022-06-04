#include <iostream>
#include <algorithm> // for_each

bool startWith(const std::string& a, const std::string& b) {
    return a.rfind(b, 0) == 0;
}

bool filterTemporaryKeys(const std::string& key)
{
    return key.rfind("_", 0) == 0;
}

void to_uppercase(std::string& str) {
    std::for_each(str.begin(), str.end(), [](char & c) {
        c = ::toupper(c);
    });
}

void to_lowercase(std::string& str) {
    std::for_each(str.begin(), str.end(), [](char & c) {
        c = (char)::tolower(c);
    });
}

void test(std::string& str) {
    std::cout << "is " << str.c_str() << " start witch hello : " << startWith(str, "hello") << std::endl;
    to_uppercase(str);
    std::cout << "In Upper Case : " << str << std::endl;
    to_lowercase(str);
    std::cout << "In Lower Case : " << str << std::endl;
}

int main() {
    std::string str = "hello world!";
    std::cout << str.c_str() << std::endl;
    test(str);
    return 0;
}
