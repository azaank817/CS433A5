/**
 * LRU Replacement Algorithm Implementation
 * @file lru_replacement.cpp
 * @author Azaan Khan
 */

#include "lru_replacement.h"
#include <iostream>
#include <limits>

using namespace std;

// Constructor
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames), current_time(0) {
    last_used_time.resize(num_pages, 0);
}

// Destructor
LRUReplacement::~LRUReplacement() {}

// Update access time when a page is touched
void LRUReplacement::touch_page(int page_num) {
    current_time++;
    last_used_time[page_num] = current_time;
}

// Load a new page into a free frame
void LRUReplacement::load_page(int page_num) {
    int frame_num = get_next_free_frame();
    page_table.set_entry(page_num, frame_num, true);

    current_time++;
    last_used_time[page_num] = current_time;

    num_page_faults++;
}

// Replace the least recently used page
int LRUReplacement::replace_page(int page_num) {
    int oldest_time = numeric_limits<int>::max();
    int lru_page = -1;

    // Find least recently used valid page
    for (int i = 0; i < page_table.get_num_pages(); ++i) {
        if (page_table.is_valid(i) && last_used_time[i] < oldest_time) {
            oldest_time = last_used_time[i];
            lru_page = i;
        }
    }

    // Evict LRU page
    int frame_num = page_table.get_frame_number(lru_page);
    page_table.set_entry(lru_page, -1, false);
    page_table.set_entry(page_num, frame_num, true);

    current_time++;
    last_used_time[page_num] = current_time;

    num_page_faults++;
    num_page_replacements++;

    return frame_num;
}

