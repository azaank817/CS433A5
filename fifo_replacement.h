/**
 * Assignment 5: Page replacement algorithms
 * @file fifo_replacement.h
 * @author Azaan Khan
 * @brief A class implementing the FIFO page replacement algorithm
 * @version 1.0
 */

#pragma once

#include "replacement.h"
#include <queue>  // For FIFO queue

/**
 * @brief A class to simulate the FIFO (First-In, First-Out) page replacement algorithm.
 * This class maintains the order in which pages are loaded and replaces the oldest one first.
 */
class FIFOReplacement : public Replacement {
private:
    std::queue<int> fifo_queue;  // Queue to track the order of loaded pages

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of virtual pages.
     * @param num_frames Total number of physical memory frames.
     */
    FIFOReplacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~FIFOReplacement();

    /**
     * @brief Handle a page fault when free frames are available.
     * Loads the page into an available frame and updates data structures.
     * @param page_num The logical page number that caused the fault.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Handle a page fault when no free frames are available.
     * Replaces the page that has been in memory the longest.
     * @param page_num The logical page number that caused the fault.
     * @return The frame number where the new page was loaded.
     */
    virtual int replace_page(int page_num);
};
