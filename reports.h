/**
 * @file reports.h
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file reports
 *
 * This header file has the functions and messages defined, used in reports.c
*/

#ifndef REPORTS_H
#define REPORTS_H

#include "companies.h"

#define MSG_REPORT2_COMMENTS_COMPANY_LESS_OR_MORE "A empresa %s é a empresa que possui %s comentarios, com %d comentarios! Sendo eles:\n" /**< Defines the message to report a company with less or more comments. */
#define MSG_REPORT2_COMMENTS_COMPANY_LESS_EQUAL_0 "A empresa %s é a empresa que possui menos comentarios, com %d comentarios!\n" /**< Defines the message to report a company with zero or less comments. */

/**
 * @brief Generates a report on company classifications.
 *
 * @param companies The Companies struct.
 */
void report_classi(Companies companies);

/**
 * @brief Generates a report on company comments.
 *
 * @param companies The Companies struct.
 */
void report_comment(Companies companies);

/**
 * @brief Generates a report on company searches.
 *
 * @param search_comp The Search_comp struct.
 */
void report_search(Search_comp search_comp);

#endif /* REPORTS_H */

