/**
 * @file inputs_file_memory.h
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file inputs file memory
 * 
 * This header file has defined the functions and file names, used in the inputs_file_memory.c file.
 * 
*/

#ifndef INPUTS_FILE_H
#define INPUTS_FILE_H

#include "companies.h"

#define FILE_COMPANY "ficheiro_empresas.bin" /**< Defines the filename for the companies file. */
#define FILE_BRANCH "ficheiro_branch.bin" /**< Defines the filename for the branch activity file. */
#define FILE_SEARCH "ficheiro_procurar.bin" /**< Defines the filename for the search file. */

/**
 * @brief Loads data from files and allocates memory for the respective struct.
 *
 * This function loads data from the files defined by FILE_COMPANY, FILE_BRANCH, and FILE_SEARCH into the Companies, 
 * Branch_Activity, and Search_comp struct and allocates memory for the respective struct.
 *
 * @param companies A pointer to the Companies struct.
 * @param branchs A pointer to the Branch_Activity struct.
 * @param search_comp A pointer to the Search_comp struct.
 */
void load_file(Companies *companies, Branch_Activity *branchs, Search_comp *search_comp);

/**
 * @brief Saves the Companies struct to a file.
 *
 * This function saves the data in the Companies struct to the file defined by FILE_COMPANY.
 *
 * @param companies A pointer to the Companies struct.
 */
void save_file_comp(Companies *companies);

/**
 * @brief Saves the Branch_Activity struct to a file.
 *
 * This function saves the data in the Branch_Activity struct to the file defined by FILE_BRANCH.
 *
 * @param branchs A pointer to the Branch_Activity struct.
 */
void save_file_branchs(Branch_Activity *branchs);

/**
 * @brief Saves the Search_comp struct to a file.
 *
 * This function saves the data in the Search_comp struct to the file defined by FILE_SEARCH.
 *
 * @param search_comp A pointer to the Search_comp struct.
 */
void save_search_comp(Search_comp *search_comp);

#endif /* INPUTS_FILE_H */