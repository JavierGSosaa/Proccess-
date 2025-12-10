#pragma once
#include <iostream>
#include <vector>
#include <string>

class Partition {
public:
    std::string name;
    int size;
    bool used;
    std::string assignedProcess;

    Partition(std::string n, int s) {
        name = n;
        size = s;
        used = false;
        assignedProcess = "";
    }
};
