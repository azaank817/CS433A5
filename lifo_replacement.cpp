/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Azaan Khan
 * @brief A class implementing the Last-In-First-Out (LIFO) page replacement algorithm
 * @version 1.0
 */

#include "lifo_replacement.h"
#include <iostream>

using namespace std;

// Constructor
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {
    // No special setup needed beyond what the base class does
}

// Destructor
LIFOReplacement::~LIFOReplacement() {
    // Nothing special to clean up in this class
}

// Called when an invalid page is accessed and there are free frames
void LIFOReplacement::load_page(int page_num) {
    // Get next available free frame
    int frame_num = get_next_free_frame();

    // Update page table: mark valid and set frame number
    page_table->set_entry(page_num, frame_num, true);

    // Store the most recently loaded page number (for LIFO)
    last_loaded_page = page_num;

    // Increment page fault counter
    num_page_faults++;
}

// Called when an invalid page is accessed and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    // Get frame number of the most recently loaded page
    int frame_num = page_table->get_frame_number(last_loaded_page);

    // Invalidate the last loaded page
    page_table->set_entry(last_loaded_page, -1, false);

    // Replace with new page
    page_table->set_entry(page_num, frame_num, true);

    // Update last_loaded_page with the current page
    last_loaded_page = page_num;

    // Update stats
    num_page_faults++;
    num_page_replacements++;

    return frame_num;
}
