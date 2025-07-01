/**
 * @file inputs_user.h
 * @author Studentes: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file inputs_user.h, inputs user
 *
 * This header file stores the defined functions, used in the inputs_user.c file.
*/

#ifndef INPUT_GERAL_UTIL_H
#define INPUT_GERAL_UTIL_H

#include "companies.h"

/**
 * @brief Validates the position of a comment in a company.
 * 
 * @param companies The companies to validate in.
 * @param pos_nif The position of the company in the companies.
 * @param id_comment The ID of the comment to validate.
 * 
 * @return An integer indicating the validity of the comment's position.
 */
int validation_pos_comment(Companies companies, int pos_nif, int id_comment);

/**
 * @brief Prints the information of the comment at the given position in a company.
 * 
 * @param companies The companies to print the information from.
 * @param pos_nif The position of the company in the companies.
 * @param pos_comment The position of the comment in the company.
 */
void information_comments(Companies companies, int pos_nif, int pos_comment);

/**
 * @brief Validates an email address.
 * 
 * @param email The email address to validate.
 * 
 * @return An integer indicating the validity of the email address.
 */
int validation_email(char *email);

/**
 * @brief Consults the names of the companies.
 * 
 * @param companies The companies to consult.
 */
void consult_comp_name(Companies companies);

/**
 * @brief Consults the categories of the companies.
 * 
 * @param companies The companies to consult.
 */
void consult_comp_category(Companies companies);

/**
 * @brief Consults the localities of the companies.
 * 
 * @param companies The companies to consult.
 */
void consult_comp_locality(Companies companies);

#endif /* INPUT_GERAL_UTIL_H */