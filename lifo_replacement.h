/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.h
 * @author Azaan Khan
 * @brief A class implementing the LIFO (Last-In-First-Out) page replacement algorithm
 * @version 1.0
 */

#pragma once

#include "replacement.h"

/**
 * @brief A class to simulate the LIFO (Last-In-First-Out) page replacement algorithm.
 * This algorithm always removes the most recently loaded page.
 */
class LIFOReplacement : public Replacement {
private:
    int last_loaded_page;  // Tracks the most recently loaded page

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of virtual pages.
     * @param num_frames Total number of physical memory frames.
     */
    LIFOReplacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~LIFOReplacement();

    /**
     * @brief Handle a page fault when free frames are available.
     * Loads the page into an available frame and tracks it as the last loaded.
     * @param page_num The logical page number that caused the fault.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Handle a page fault when no free frames are available.
     * Replaces the most recently loaded page (LIFO behavior).
     * @param page_num The logical page number that caused the fault.
     * @return The frame number where the new page was loaded.
     */
    virtual int replace_page(int page_num);
};
