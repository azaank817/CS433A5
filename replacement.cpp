/**
 * Base Replacement Class Implementation
 * @file replacement.cpp
 * @author Azaan Khan
 */

#include <iostream>
#include "replacement.h"

using namespace std;

// Constructor initializes counters and page table
Replacement::Replacement(int num_pages, int num_frames)
    : page_table(num_pages),
      num_pages(num_pages),
      num_frames(num_frames),
      free_frame_pointer(0),
      num_references(0),
      num_page_faults(0),
      num_page_replacements(0) {}

// Destructor
Replacement::~Replacement() {}

// Handle access to a page, simulating page replacement logic
bool Replacement::access_page(int page_num, bool is_write) {
    num_references++;

    if (page_table.is_valid(page_num)) {
        // Page already in memory
        touch_page(page_num);
        return false;
    }

    // Page fault
    if (free_frame_pointer < num_frames) {
        load_page(page_num);
    } else {
        replace_page(page_num);
    }

    return true;
}

// Return next available free frame
int Replacement::get_next_free_frame() {
    return free_frame_pointer++;
}

// Return page table entry
PageEntry Replacement::getPageEntry(int page_num) const {
    return page_table.get_entry(page_num);
}

// Output statistics for the simulation
void Replacement::print_statistics() const {
    cout << "Number of references: \t\t" << num_references << endl;
    cout << "Number of page faults: \t\t" << num_page_faults << endl;
    cout << "Number of page replacements: \t" << num_page_replacements << endl;
}

