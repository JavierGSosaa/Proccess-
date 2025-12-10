// debug.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include "Partition.h"
#include "Process.h"
#include "MemoryManager.h"


int main() {
    int nParts, nProcs;

    std::cout << "Enter number of memory partitions: ";
    if (!(std::cin >> nParts) || nParts <= 0) {
        std::cout << "Invalid number of partitions.\n";
        return 1;
    }
    std::vector<Partition> memory;
    for (int i = 0; i < nParts; i++) {
        int size;
        std::cout << "Partition " << i + 1 << " size: ";
        std::cin >> size;
        memory.push_back(Partition("P" + std::to_string(i + 1), size));
    }
    std::cout << "\nEnter number of processes: ";
    if (!(std::cin >> nProcs) || nProcs < 0) {
        std::cout << "Invalid number of processes.\n";
        return 1;
    }
    std::vector<Process> processes;
    for (int i = 0; i < nProcs; i++) {
        int size;
        std::cout << "Process " << i + 1 << " size: ";
        std::cin >> size;
        processes.push_back(Process("J" + std::to_string(i + 1), size));
    }
    std::cout << "\n\n==== Running Algorithms ====\n";
    MemoryManager mm;
    mm.BestFit(memory, processes);
    mm.FirstFit(memory, processes);
    mm.NextFit(memory, processes);
    mm.WorstFit(memory, processes);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
