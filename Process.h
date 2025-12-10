#pragma once
#include <iostream>
#include <vector>
#include <string>

class Process {
public:
    std::string name;
    int size;
    std::string status;       // "Run" or "Wait"
    int assignedPart;    // -1 if not assigned
    Process(std::string n, int s) {
        name = n;
        size = s;
        status = "Wait";
        assignedPart = -1;
    }
};