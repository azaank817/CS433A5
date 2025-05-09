/**
 * Assignment 5: Page replacement algorithms
 * @file replacement.h
 * @author Azaan Khan
 * @brief A base class for different page replacement algorithms.
 * @version 1.0
 */

#pragma once

#include "pagetable.h"

/**
 * @brief A base class to simulate page replacement algorithms.
 * Specific algorithms like FIFO, LRU, and LIFO inherit from this class.
 */
class Replacement {
protected:
    PageTable page_table;      // Page table for address translation
    int num_pages;             // Total number of logical pages
    int num_frames;            // Total number of physical frames
    int free_frame_pointer;    // Tracks the index of next available frame
    int num_references;        // Total number of memory accesses
    int num_page_faults;       // Total number of page faults
    int num_page_replacements; // Total number of page replacements

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of logical pages.
     * @param num_frames Total number of available physical frames.
     */
    Replacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~Replacement();

    /**
     * @brief Simulate a single page access.
     * @details If the page is valid, it calls touch_page().
     *          If it's invalid but free frames exist, it calls load_page().
     *          If it's invalid and no free frame exists, it calls replace_page().
     * @param page_num The logical page number to access.
     * @param is_write Optional flag for memory write (unused here).
     * @return True if the access caused a page fault.
     */
    virtual bool access_page(int page_num, bool is_write = false);

    /**
     * @brief Called when a page already in memory is accessed.
     * Can be overridden for LRU-type behavior.
     * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num) {}

    /**
     * @brief Called when a page fault occurs and free frames exist.
     * Can be overridden by child classes.
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num) {}

    /**
     * @brief Called when a page fault occurs and memory is full.
     * Must be implemented in child classes to define replacement strategy.
     * @param page_num The logical page number of the page to load.
     * @return Frame number assigned to the page.
     */
    virtual int replace_page(int page_num) = 0;

    /**
     * @brief Get the frame number and metadata for a given page.
     * @param page_num Logical page number.
     * @return Corresponding PageEntry struct.
     */
    PageEntry getPageEntry(int page_num);

    /**
     * @brief Get the next available free frame index.
     * @return Frame index
     */
    int get_next_free_frame();

    /**
     * @brief Print current simulation statistics.
     */
    void print_statistics() const;
};
