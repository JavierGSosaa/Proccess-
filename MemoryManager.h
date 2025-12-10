#pragma once
#include "Process.h"
#include "Partition.h"
#include <iostream>
#include <vector>
#include <string>

class MemoryManager {
public:
	void PrintResults(const std::string& title, std::vector<Partition> mem, std::vector<Process>& jobs);
	void BestFit(std::vector<Partition> mem, std::vector<Process>& jobs);
	void WorstFit(std::vector<Partition> mem, std::vector<Process>& jobs);
	void NextFit(std::vector<Partition> mem, std::vector<Process>& jobs);
	void FirstFit(std::vector<Partition> mem, std::vector<Process>& jobs);
};
