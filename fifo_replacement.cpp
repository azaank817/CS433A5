/**
 * FIFO Replacement Algorithm Implementation
 * @file fifo_replacement.cpp
 * @author Azaan Khan
 */

#include "fifo_replacement.h"
#include <iostream>

using namespace std;

// Constructor
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {}

// Destructor
FIFOReplacement::~FIFOReplacement() {}

// Load a page when a free frame is available
void FIFOReplacement::load_page(int page_num) {
    int frame_num = get_next_free_frame();

    // Update page table: mark as valid and set frame number
    page_table.set_entry(page_num, frame_num, true);

    // Add to FIFO queue
    fifo_queue.push(page_num);

    // Track page fault
    num_page_faults++;
}

// Replace a page using FIFO strategy (evict oldest page)
int FIFOReplacement::replace_page(int page_num) {
    int victim_page = fifo_queue.front();
    fifo_queue.pop();

    int frame_num = page_table.get_frame_number(victim_page);

    // Invalidate the victim page
    page_table.set_entry(victim_page, -1, false);

    // Replace it with the new page
    page_table.set_entry(page_num, frame_num, true);
    fifo_queue.push(page_num);

    num_page_faults++;
    num_page_replacements++;

    return frame_num;
}

