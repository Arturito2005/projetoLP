/**
 * @file inputs_branch.h
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file inputs branchs
 *
 * This header file stores the defined functions and messages, used in the inputs_branch.c file.
*/

#ifndef INPUTS_BRANCH_H
#define INPUTS_BRANCH_H

#include "branchs.h"

#define MSG_INSERT_STATE_BRANCH "Introduza o estado do ramo (0: Ativa/ 1: Inativa)-->" /**< Defines the message to enter the state of the branch. */
#define USED_BRANCH_IN_COMPANY "Está associado a alguma empresa --> Sim\n" /**< Defines the message that the branch is being used in some company. */
#define DONT_USED_BRANCH_IN_COMPANY "Está associado a alguma empresa --> Não\n" /**< Defines the message that the branch isn't being used in some company. */

/**
 * @brief Compares the branch activity with the given branch.
 * 
 * @param branchs The branch activity to compare.
 * @param Branch The branch to compare with.
 * 
 * @return An integer indicating the result of the comparison.
 */
int compare_branch (Branch_Activity branchs, char *Branch);

/**
 * @brief Searches for the position of the branch in the branch activity.
 * 
 * @param branchs The branch activity to search in.
 * @param name_branch The name of the branch to search for.
 * 
 * @return The position of the branch in the branch activity.
 */
int search_branch_pos(Branch_Activity branchs, char *name_branch);

/**
 * @brief Checks if the branch is used in the given companies.
 * 
 * @param companies The companies to check in.
 * @param name_branch The name of the branch to check for.
 * 
 * @return An integer indicating whether the branch is used in the companies.
 */
int used_bracnh_comp(Companies companies, char *name_branch);

/**
 * @brief Inserts an ID into the branch activity.
 * 
 * @param branchs The branch activity to insert the ID into.
 * 
 * @return An integer indicating the success of the insertion.
 */
int insert_id_branch (Branch_Activity *branchs);

/**
 * @brief Prints the information of the branch at the given position in the branch activity.
 * 
 * @param branchs The branch activity to print the information from.
 * @param pos The position of the branch in the branch activity.
 */
void information_branch(Branch_Activity branchs, int pos);

/**
 * @brief Fills the fields of the branch at the given position in the branch activity.
 * 
 * @param branchs The branch activity to fill the fields in.
 * @param pos The position of the branch in the branch activity.
 */
void fields_branch(Branch_Activity *branchs, int pos);

#endif /* INPUTS_BRANCH_H */