/**
 * Assignment 5: Page replacement algorithms
 * @file lru_replacement.h
 * @author Azaan Khan
 * @brief A class implementing the LRU (Least Recently Used) page replacement algorithm
 * @version 1.0
 */

#pragma once

#include "replacement.h"
#include <vector>

/**
 * @brief A class to simulate the Least Recently Used (LRU) page replacement algorithm.
 * Tracks the last access time of each page and evicts the least recently accessed one.
 */
class LRUReplacement : public Replacement {
private:
    std::vector<int> last_used_time; // Stores last accessed time for each page
    int current_time;                // Logical clock to track usage recency

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of virtual pages.
     * @param num_frames Total number of physical memory frames.
     */
    LRUReplacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~LRUReplacement();

    /**
     * @brief Called when a page already in physical memory is accessed.
     * Updates the usage time of the accessed page.
     * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num);

    /**
     * @brief Handles a page fault when free frames are available.
     * Loads the page and tracks its access time.
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Handles a page fault when no free frames are available.
     * Evicts the least recently used page and replaces it.
     * @param page_num The logical page number.
     * @return Frame number assigned to the new page.
     */
    virtual int replace_page(int page_num);
};
