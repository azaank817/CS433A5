/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Azaan Khan
 * @brief This class represents a traditional pagetable data structure.
 * @version 1.0
 */

#include "pagetable.h"

// Constructor
PageTable::PageTable(int num_pages) {
    this->num_pages = num_pages;
    // Initialize the page table with invalid entries
    page_table.resize(num_pages);
    for (int i = 0; i < num_pages; i++) {
        page_table[i].frame_num = -1;
        page_table[i].valid = false;
        page_table[i].dirty = false; // Not used, but set to false
    }
}

// Destructor
PageTable::~PageTable() {
    // No dynamic allocation to manually free
}

// Return the frame number for a given page number
int PageTable::get_frame_number(int page_num) const {
    return page_table[page_num].frame_num;
}

// Check if the page is currently valid (in memory)
bool PageTable::is_valid(int page_num) const {
    return page_table[page_num].valid;
}

// Update the entry for a given page number
void PageTable::set_entry(int page_num, int frame_num, bool valid) {
    page_table[page_num].frame_num = frame_num;
    page_table[page_num].valid = valid;
}

// Get the PageEntry struct for a page
PageEntry PageTable::get_entry(int page_num) const {
    return page_table[page_num];
}

// Get the total number of pages
int PageTable::get_num_pages() const {
    return num_pages;
}
