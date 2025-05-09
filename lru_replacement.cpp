/**
 * Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Azaan Khan
 * @brief A class implementing the LRU (Least Recently Used) page replacement algorithm
 * @version 1.0
 */

#include "lru_replacement.h"
#include <iostream>
#include <limits>

using namespace std;

// Constructor
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames), current_time(0) {
    // Initialize all page timestamps to 0
    last_used_time.resize(num_pages, 0);
}

// Destructor
LRUReplacement::~LRUReplacement() {
    // Nothing special to free
}

// Called when an already-loaded page is accessed (used to track recency)
void LRUReplacement::touch_page(int page_num) {
    current_time++;
    last_used_time[page_num] = current_time;
}

// Called when an invalid page is accessed and free frames are available
void LRUReplacement::load_page(int page_num) {
    int frame_num = get_next_free_frame();

    // Mark page as valid and assign frame
    page_table->set_entry(page_num, frame_num, true);

    // Track access time
    current_time++;
    last_used_time[page_num] = current_time;

    num_page_faults++;
}

// Called when an invalid page is accessed and memory is full
int LRUReplacement::replace_page(int page_num) {
    int oldest_time = std::numeric_limits<int>::max();
    int lru_page = -1;

    // Find the least recently used valid page
    for (int i = 0; i < page_table->get_num_pages(); ++i) {
        if (page_table->is_valid(i) && last_used_time[i] < oldest_time) {
            oldest_time = last_used_time[i];
            lru_page = i;
        }
    }

    // Evict the LRU page
    int frame_num = page_table->get_frame_number(lru_page);
    page_table->set_entry(lru_page, -1, false);

    // Load the new page
    page_table->set_entry(page_num, frame_num, true);

    // Update access time for the new page
    current_time++;
    last_used_time[page_num] = current_time;

    num_page_faults++;
    num_page_replacements++;

    return frame_num;
}
