/**
 * LIFO Replacement Algorithm Implementation
 * @file lifo_replacement.cpp
 * @author Azaan Khan
 */

#include "lifo_replacement.h"
#include <iostream>

using namespace std;

// Constructor
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames), last_loaded_page(-1) {}

// Destructor
LIFOReplacement::~LIFOReplacement() {}

// Load a page into a free frame and update last loaded tracker
void LIFOReplacement::load_page(int page_num) {
    int frame_num = get_next_free_frame();
    page_table.set_entry(page_num, frame_num, true);
    last_loaded_page = page_num;
    num_page_faults++;
}

// Replace the most recently loaded page (LIFO)
int LIFOReplacement::replace_page(int page_num) {
    int frame_num = page_table.get_frame_number(last_loaded_page);

    // Invalidate and replace last loaded page
    page_table.set_entry(last_loaded_page, -1, false);
    page_table.set_entry(page_num, frame_num, true);
    last_loaded_page = page_num;

    num_page_faults++;
    num_page_replacements++;

    return frame_num;
}

