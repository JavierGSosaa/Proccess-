#include <iostream>
#include "Process.h"
#include "Partition.h"
#include "MemoryManager.h"

void MemoryManager::PrintResults(const std::string& title, std::vector<Partition> mem, std::vector<Process>& jobs)
{
    std::cout << "\n=============================\n";
    std::cout << "   " << title << " Results\n";
    std::cout << "=============================\n";
    int totalWaste = 0;
    std::cout << "\nInitial Memory Allocation:\n";
    std::cout << "--------------------------\n";
    for (auto& p : mem) {
        std::cout << p.name << " (" << p.size << "): ";
        if (p.used)
            std::cout << p.assignedProcess << '\n';
        else
            std::cout << "FREE\n";
    }
    std::cout << "\nMemory Waste per Partition:\n";
    std::cout << "---------------------------\n";
    for (auto& p : mem) {
        if (p.used) {
            for (auto& j : jobs) {
                if (j.name == p.assignedProcess) {
                    int waste = p.size - j.size;
                    std::cout << p.name << ": " << waste << '\n';
                    totalWaste += waste;
                }
            }
        }
        else {
            std::cout << p.name << ": " << p.size << " (unused)\n";
            totalWaste += p.size;
        }
    }
    std::cout << "\nTotal Waste = " << totalWaste << "\n";
    std::cout << "\nProcesses in WAIT state:\n";
    std::cout << "-------------------------\n";
    bool waiting = false;
    for (auto& j : jobs) {
        if (j.status == "Wait") {
            std::cout << j.name << " (" << j.size << ")\n";
            waiting = true;
        }
    }
    if (!waiting)  std::cout << "None\n";
    std::cout << std::endl;
}
void MemoryManager::BestFit(std::vector<Partition> mem, std::vector<Process>& jobs) {
    for (auto& j : jobs) {
        int bestIdx = -1;
        int bestDiff = 400;
        for (int i = 0; i < (int)mem.size(); i++) {
            if (!mem[i].used && mem[i].size >= j.size) {
                int diff = mem[i].size - j.size;
                if (diff < bestDiff) {
                    bestDiff = diff;
                    bestIdx = i;
                }
            }
        }
        if (bestIdx != -1) {
            mem[bestIdx].used = true;
            mem[bestIdx].assignedProcess = j.name;
            j.status = "Run";
        }
    }
    PrintResults("Best-Fit", mem, jobs);
}
void MemoryManager::FirstFit(std::vector<Partition> mem, std::vector<Process>& jobs) {
    for (auto& j : jobs) {
        for (int i = 0; i < (int)mem.size(); i++) {
            if (!mem[i].used && mem[i].size >= j.size) {
                mem[i].used = true;
                mem[i].assignedProcess = j.name;
                j.status = "Run";
                break;
            }
        }
    }
    PrintResults("First-Fit", mem, jobs);
}
void MemoryManager::NextFit(std::vector<Partition> mem, std::vector<Process>& jobs) {
    int pos = 0;
    int n = mem.size();
    for (auto& j : jobs) {
        bool allocated = false;
        int start = pos;
        do {
            if (!mem[pos].used && mem[pos].size >= j.size) {
                mem[pos].used = true;
                mem[pos].assignedProcess = j.name;
                j.status = "Run";
                allocated = true;
                break;
            }

            pos = (pos + 1) % n;

        } while (pos != start);
    }
    PrintResults("Next-Fit", mem, jobs);
};
void MemoryManager::WorstFit(std::vector<Partition> mem, std::vector<Process>& jobs) {
    for (auto& j : jobs) {
        int worstIdx = -1;
        int worstSize = -1;
        for (int i = 0; i < (int)mem.size(); i++) {
            if (!mem[i].used && mem[i].size >= j.size) {
                if (mem[i].size > worstSize) {
                    worstSize = mem[i].size;
                    worstIdx = i;
                }
            }
        }
        if (worstIdx != -1) {
            mem[worstIdx].used = true;
            mem[worstIdx].assignedProcess = j.name;
            j.status = "Run";
        }
    }
    PrintResults("Worst-Fit", mem, jobs);
};