/**
 * Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Azaan Khan
 * @brief A base class for different page replacement algorithms.
 * @version 1.0
 */

#include <iostream>
#include "replacement.h"

using namespace std;

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
    : page_table(num_pages), num_pages(num_pages), num_frames(num_frames) {
    // Mark all frames as free initially
    free_frame_pointer = 0;
    num_references = 0;
    num_page_faults = 0;
    num_page_replacements = 0;
}

// Destructor
Replacement::~Replacement() {
    // Nothing to clean up explicitly
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write) {
    num_references++; // Count every memory reference

    if (page_table.is_valid(page_num)) {
        // Page is already in memory
        touch_page(page_num);
        return false; // No page fault
    }

    // Page fault occurs
    if (free_frame_pointer < num_frames) {
        // Free frames are available
        load_page(page_num);
    } else {
        // No free frames, replacement needed
        replace_page(page_num);
    }

    return true; // Page fault occurred
}

// Get next free frame number
int Replacement::get_next_free_frame() {
    return free_frame_pointer++;
}

// Accessor to the page table entry
PageEntry Replacement::getPageEntry(int page_num) const {
    return page_table.get_entry(page_num);
}

// Print statistics
void Replacement::print_statistics() const {
    std::cout << "Number of references: \t\t"  << num_references << std::endl;
    std::cout << "Number of page faults: \t\t" << num_page_faults << std::endl;
    std::cout << "Number of page replacements: \t" << num_page_replacements << std::endl;
}
