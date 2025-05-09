/**
 * Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Azaan Khan
 * @brief A class implementing the FIFO page replacement algorithm
 * @version 1.0
 */

#include "fifo_replacement.h"
#include <iostream>

using namespace std;

// Constructor
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {
    // Initialize FIFO queue to track the order of loaded pages
}

// Destructor
FIFOReplacement::~FIFOReplacement() {
    // No dynamic allocation in this class; nothing special needed here
}

// Called when an invalid page is accessed and there are free frames
void FIFOReplacement::load_page(int page_num) {
    // Get the next free frame
    int frame_num = get_next_free_frame();

    // Update the page table: mark valid and set frame number
    page_table->set_entry(page_num, frame_num, true);

    // Push the new page number into the queue (FIFO order)
    fifo_queue.push(page_num);

    // Increment statistics
    num_page_faults++;
}

// Called when an invalid page is accessed and memory is full
int FIFOReplacement::replace_page(int page_num) {
    // Get the oldest page (front of the queue)
    int victim_page = fifo_queue.front();
    fifo_queue.pop(); // Remove victim page from the queue

    // Get frame number of victim
    int frame_num = page_table->get_frame_number(victim_page);

    // Invalidate victim in page table
    page_table->set_entry(victim_page, -1, false);

    // Load the new page into the frame
    page_table->set_entry(page_num, frame_num, true);
    fifo_queue.push(page_num); // Add the new page to the back of the queue

    // Increment statistics
    num_page_faults++;
    num_page_replacements++;

    return frame_num;
}
