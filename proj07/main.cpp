#include <iostream>
#include "FifoMap.h"
#include <string>
#include <vector> 

int main() {
    FifoMap map;
    std::vector<std::string> v{"alfa", "bravo", "charlie", "delta", "echo"};
    for (std::string& s : v) {
        map[s] = s.size();
    }

    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
        std::cout << map.count(v[i]) << " " << 1 << std::endl;
        std::cout << map.size() << " "  << v.size() - i << std::endl;
        map.erase(v[i]);
        std::cout << map.count(v[i]) << " " <<  0 << std::endl;
    }
}
