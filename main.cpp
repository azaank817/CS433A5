/**
 * Assignment 5: Page replacement algorithms
 * @file main.cpp
 * @author Azaan Khan
 * @brief Main driver program to test FIFO, LIFO, and LRU page replacement algorithms
 * @version 1.0
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <chrono>

#include "fifo_replacement.h"
#include "lru_replacement.h"
#include "lifo_replacement.h"

using namespace std;
using namespace std::chrono;

// Check if a number is a power of two
bool isPowerOfTwo(unsigned int x) {
    return x && (!(x & (x - 1)));
}

int main(int argc, char *argv[]) {
    // Introductory info
    std::cout << "=================================================================" << std::endl;
    std::cout << "CS 433 Programming Assignment 5" << std::endl;
    std::cout << "Author: Azaan Khan" << std::endl;
    std::cout << "Date: Spring 2025" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description: Program to simulate different page replacement algorithms" << std::endl;
    std::cout << "=================================================================\n" << std::endl;

    if (argc < 3) {
        std::cout << "Error: Please provide two command-line arguments:" << std::endl
                  << "1. Page size (256–8192 bytes, power of 2)" << std::endl
                  << "2. Physical memory size (4–64 MB, power of 2)" << std::endl;
        exit(1);
    }

    // Parse and validate arguments
    unsigned int page_size = atoi(argv[1]);
    if (!isPowerOfTwo(page_size) || page_size < 256 || page_size > 8192) {
        std::cerr << "Invalid page size. Must be power of 2 between 256 and 8192." << std::endl;
        return 1;
    }

    unsigned int phys_mem_size = atoi(argv[2]) << 20; // Convert MB to bytes
    if (!isPowerOfTwo(phys_mem_size) || phys_mem_size < (4 << 20) || phys_mem_size > (64 << 20)) {
        std::cerr << "Invalid physical memory size. Must be power of 2 between 4 and 64 MB." << std::endl;
        return 1;
    }

    // Calculate memory specs
    int logic_mem_bits = 27;
    int phys_mem_bits = std::log2(phys_mem_size);
    int page_offset_bits = std::log2(page_size);
    int num_pages = 1 << (logic_mem_bits - page_offset_bits);
    int num_frames = 1 << (phys_mem_bits - page_offset_bits);

    std::cout << "Page size = " << page_size << " bytes" << std::endl;
    std::cout << "Physical Memory size = " << phys_mem_size << " bytes" << std::endl;
    std::cout << "Number of pages = " << num_pages << std::endl;
    std::cout << "Number of physical frames = " << num_frames << std::endl;

    // Test 1 — Small reference list
    std::cout << "\n================================ Test 1 ==============================================\n";
    std::ifstream in("small_refs.txt");
    if (!in.is_open()) {
        std::cerr << "Cannot open small_refs.txt. Please check your path." << std::endl;
        return 1;
    }

    std::vector<int> small_refs;
    int val;
    while (in >> val) {
        small_refs.push_back(val);
    }
    in.close();

    FIFOReplacement vm(num_pages, num_frames);
    for (int addr : small_refs) {
        int page_num = addr >> page_offset_bits;
        bool isPageFault = vm.access_page(page_num, 0);
        PageEntry pg = vm.getPageEntry(page_num);
        std::cout << "Logical address: " << addr << ", \tpage number: " << page_num
                  << ", \tframe number: " << pg.frame_num << ", \tis page fault? "
                  << (isPageFault ? "Yes" : "No") << std::endl;
    }
    vm.print_statistics();

    // Test 2 — Large reference list
    std::cout << "\n================================ Test 2 ==============================================\n";

    std::ifstream in2("large_refs.txt");
    if (!in2.is_open()) {
        std::cerr << "Cannot open large_refs.txt. Please check your path." << std::endl;
        return 1;
    }

    std::vector<int> large_refs;
    while (in2 >> val) {
        large_refs.push_back(val);
    }
    in2.close();

    // FIFO Test
    std::cout << "\n**************** Simulating FIFO Replacement ****************\n";
    auto start = high_resolution_clock::now();
    FIFOReplacement fifo(num_pages, num_frames);
    for (int addr : large_refs) {
        int page_num = addr >> page_offset_bits;
        fifo.access_page(page_num, 0);
    }
    auto end = high_resolution_clock::now();
    fifo.print_statistics();
    std::cout << "Execution time: "
              << duration_cast<milliseconds>(end - start).count() << " ms\n";

    // LIFO Test
    std::cout << "\n**************** Simulating LIFO Replacement ****************\n";
    start = high_resolution_clock::now();
    LIFOReplacement lifo(num_pages, num_frames);
    for (int addr : large_refs) {
        int page_num = addr >> page_offset_bits;
        lifo.access_page(page_num, 0);
    }
    end = high_resolution_clock::now();
    lifo.print_statistics();
    std::cout << "Execution time: "
              << duration_cast<milliseconds>(end - start).count() << " ms\n";

    // LRU Test
    std::cout << "\n**************** Simulating LRU Replacement *****************\n";
    start = high_resolution_clock::now();
    LRUReplacement lru(num_pages, num_frames);
    for (int addr : large_refs) {
        int page_num = addr >> page_offset_bits;
        lru.access_page(page_num, 0);
    }
    end = high_resolution_clock::now();
    lru.print_statistics();
    std::cout << "Execution time: "
              << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}
