/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.h
 * @author Azaan Khan
 * @brief This class represents a traditional pagetable data structure.
 * @version 1.0
 */

#pragma once

#include <vector>
using namespace std;

/**
 * @brief A page table entry. This class is used to represent a page table entry.
 * Each page has one entry in the page table containing:
 * - frame number
 * - valid bit (whether the page is in physical memory)
 * - dirty bit (not used in this assignment)
 */
class PageEntry {
public:
    int frame_num;    // Frame number in physical memory
    bool valid = false; // Valid bit indicating if the page is loaded
    bool dirty = false; // Dirty bit, not used in this assignment
};

/**
 * @brief PageTable represents the virtual-to-physical address translation mapping.
 * It's implemented as an array of PageEntry structures.
 */
class PageTable {
private:
    vector<PageEntry> page_table; // Internal table of page entries
    int num_pages;                // Total number of pages

public:
    /**
     * @brief Constructor
     * @param num_pages Number of pages in logical memory
     */
    PageTable(int num_pages);

    /**
     * @brief Destructor
     */
    ~PageTable();

    /**
     * @brief Get the physical frame number mapped to the given page number
     * @param page_num Logical page number
     * @return Frame number
     */
    int get_frame_number(int page_num) const;

    /**
     * @brief Check whether the page is valid (in memory)
     * @param page_num Logical page number
     * @return True if the page is valid
     */
    bool is_valid(int page_num) const;

    /**
     * @brief Set the page table entry
     * @param page_num Logical page number
     * @param frame_num Frame number in physical memory
     * @param valid Valid bit status
     */
    void set_entry(int page_num, int frame_num, bool valid);

    /**
     * @brief Get the page entry object for the specified page
     * @param page_num Logical page number
     * @return PageEntry reference
     */
    PageEntry get_entry(int page_num) const;

    /**
     * @brief Get total number of pages
     * @return Number of pages
     */
    int get_num_pages() const;

    /**
     * @brief Overloaded [] operator for direct access to page entries
     */
    PageEntry& operator[](int i) {
        return page_table[i];
    }
};
