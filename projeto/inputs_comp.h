/**
 * @file inputs_comp.h
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file inputs companies
 *
 * This header file stores the defined functions and messages, used in the inputs_comp.c file.
*/

#ifndef INPUTS_EMP_H
#define INPUTS_EMP_H

#include "companies.h"

#define MSG_INSERT_BRANCH "Introduza o ramo de atividade -->" /**< Defines the message to request the activity branch. */

#define MSG_EMP_COM_COMENTARIO_ED "Só será possível editar o estado da empresa, porque a mesma já possui %d comentarios de utilizadores!\n" /**< Defines the message to inform that it's only possible to edit the company status because it already has user comments. */
#define MSG_EMP_COM_COMENTARIO_DEL "Não é possível elimnar a empresa, porque a mesma já possui %d comentarios de utilizadores!\n" /**< Defines the message to inform that it's not possible to delete the company because it already has user comments. */

#define MSG_CATEGORY "Categoria --> %s" /**< Defines the message to display the category. */

/**
 * @brief Checks if there are comments in the Companies struct.
 *
 * @param companies The Companies struct.
 * @return int Returns 1 if there are comments, 0 otherwise.
 */
int exist_comm(Companies companies);

/**
 * @brief Checks if there are classifications in the Companies struct.
 *
 * @param companies The Companies struct.
 * @return int Returns 1 if there are classifications, 0 otherwise.
 */
int exist_classi(Companies companies);

/**
 * @brief Validates the postal code.
 *
 * @param cod_postal The postal code to validate.
 * @return int Returns 1 if the postal code is valid, 0 otherwise.
 */
int validation_cod_postal(char *cod_postal);

/**
 * @brief Displays information about a company.
 *
 * @param companies The Companies struct.
 * @param pos The position of the company in the struct.
 */
void information_company(Companies companies, int pos);

/**
 * @brief Validates the branches in the Branch_Activity struct.
 *
 * @param branchs The Branch_Activity struct.
 * @return int Returns 1 if the branches are valid, 0 otherwise.
 */
int valids_branch(Branch_Activity branchs);

/**
 * @brief Validates a branch in the Companies struct.
 *
 * @param companies A pointer to the Companies struct.
 * @param branchs The Branch_Activity struct.
 * @param name_branch The name of the branch to validate.
 * @param pos_comp The position of the company in the struct.
 * @return int Returns 1 if the branch is valid, 0 otherwise.
 */
int validation_branch(Companies *companies, Branch_Activity branchs, char *name_branch, int pos_comp);

/**
 * @brief Fills the fields of a company in the Companies struct.
 *
 * @param companies A pointer to the Companies struct.
 * @param branchs The Branch_Activity struct.
 * @param pos The position of the company in the struct.
 */
void fields_company(Companies *companies, Branch_Activity branchs, int pos);

#endif /* INPUTS_EMP_H */

