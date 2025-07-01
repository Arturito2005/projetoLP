/**
 * @file reports.c
 * @author Alunos: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 *
 * @brief File reports.c, stores all functions that perform the administrator’s reports.
 *
 * This file stores all 3 reports of the user’s use of options, by the same, where one of the reports is about the 
 * comments made to the companies, showing all and the most and least commented company(s), another report for the 
 * ratings, where it shows the average rating of each company and the company(s) with the highest and lowest average 
 * rating, and another report that shows of the 3 methods of searching for companies which were the most and least used. 
*/

#include <stdio.h>
#include <stdlib.h>

#include "reports.h"
#include "inputs_geral.h"
#include "inputs_user.h"
#include "inputs_comp.h"
#include "op_user.h"

static int i = 0, y = 0;

/**
 * @brief Creates a report on the ratings of companies.
 *
 * This function calculates the average rating of each company and identifies the company(s) with the highest and 
 * lowest average ratings.
 * It then prints a report detailing the average ratings of all companies and highlighting the company(s) 
 * with the highest and lowest averages.
 *
 * @param companies struct Companies that contains all the companies and their ratings.
 * @note If there is only one company, the function will simply calculate and print its average rating. 
 */
void report_classi(Companies companies) {
    int pos_more = 0, pos_less = 0, equal_more = 0, equal_less = 0;
    float more_media = 0.00, less_media = 6, tot = 0.00, media = 0.00;
    
    printf("Relatorio 1 (Classificação das empresas)\n");
    
    if(companies.cont_comp > 1) {
        for(i = 0; i < companies.cont_comp; i++) {
            printf("Empresa nº%d\n", i + 1);
            
            for(y = 0; y < companies.company[i].cont_classi; y++) {
                tot = tot + companies.company[i].comp_class[y].class;
            }
            
            media = tot / companies.company[i].cont_classi;

            if(media > more_media) {
                more_media = media;
                pos_more = i;
                equal_more = 0;
            } else if(media == more_media) {
                equal_more++;
            }

            if(media < less_media) {
                less_media = media;
                pos_less = i;
                equal_less = 0;
            } else if(media == less_media) {
                equal_less++;
            }
            
            if (companies.company[i].cont_classi > 0) {
                printf("A empresa %s tem media de %0.2f\n\n", companies.company[i].name_compa, media);
            } else {
                printf("A empresa %s tem media de 0\n\n", companies.company[i].name_compa);
            }         
            
            tot = 0;
            media = 0;
        }
        
        if(equal_more > 0) {
            printf("Existem %d empresas empatadas com a maior media, %0.2f, que são:\n", equal_more + 1, more_media);
            for(i = 0; i < companies.cont_comp; i++) {
                for(y = 0; y < companies.company[i].cont_classi; y++) {
                    tot = tot + companies.company[i].comp_class[y].class;
                }
                media = tot / companies.company[i].cont_classi;
                
                if(media == more_media) {
                    printf("Empresa %s\n", companies.company[i].name_compa);                
                }
                
                tot = 0;
                media = 0;   
            }
        } else {
            printf("A maior media foi da empresa %s, com %0.2f de media!\n", companies.company[pos_more].name_compa, more_media);
        }
        
        if(equal_less > 0) {
            printf("Existem %d empresas empatadas com a menor media, %0.2f, que são:\n", equal_less + 1, less_media);
            
            for(i = 0; i < companies.cont_comp; i++) {
                for(y = 0; y < companies.company[i].cont_classi; y++) {
                    tot = tot + companies.company[i].comp_class[y].class;
                }
                
                media = tot / companies.company[i].cont_classi;
                
                if(media == less_media) {
                    printf("Empresa %s\n", companies.company[i].name_compa);                
                }
                
                tot = 0;
                media = 0;
            }
        } else { 
            printf("A menor media foi da empresa %s, com %0.2f de media!\n", companies.company[pos_less].name_compa, less_media);
        }
    } else {
        for(i = 0; i < companies.company[0].cont_classi; i++) {
            tot = tot + companies.company[0].comp_class[i].class;
        }
    
        media = tot / companies.company[0].cont_classi;
        tot = 0;
        pos_less = 0;
               
        printf("Só existe uma empresa!\n");
        printf("A empresa %s tem media de %0.2f\n", companies.company[0].name_compa, media);
        media = 0;
    }
}

/**
 * @brief Creates a report on the comments of companies.
 *
 * This function calculates the total number of comments for each company and identifies the company(s) with the highest and lowest 
 * number of comments.
 * It then creates a report detailing the total number of comments of all companies and highlighting the company(s) 
 * with the highest and lowest number of comments.
 * At the beginning of the report, it shows the data of all companies with comments and all the comments of them.
 * @param companies Struct Companies, which contains the information of all companies and their respective comments.
 * @note If there is only one company, the function will simply print its comments.
 */
void report_comment(Companies companies) {
    int more_comme = 0, less_comme = companies.company[i].cont_coments + 1, pos_more = 0, pos_less = 0, equal_more = 0, equal_less = 0;
    
    printf("Relatorio 2 (Comentarios das empresas)\n\n");  
    if(companies.cont_comp > 0) {
        for(i = 0; i < companies.cont_comp; i++) {
            if(companies.company[i].cont_coments > more_comme) {
                more_comme = companies.company[i].cont_coments;
                pos_more = i;
                equal_more = 0;
            } else if (companies.company[i].cont_coments == more_comme) {
                equal_more++;
            }

            if(companies.company[i].cont_coments < less_comme) {
                less_comme = companies.company[i].cont_coments;
                pos_less = i;
                equal_less = 0;
            } else if (companies.company[i].cont_coments == less_comme) {
                equal_less++;
            }

            printf("Empresa nº%d\n", i + 1);
            printf("Total de comentarios da empresa %s --> %d\n", companies.company[i].name_compa, companies.company[i].cont_coments); 
            
            if(companies.company[i].cont_coments > 0) {
                for(y = 0; y < companies.company[i].cont_coments; y++) {
                    printf("Comentario nº%d\n", y + 1);
                    information_comments(companies, i, y);
                }
            }
        }
        printf("\n");
        
        if(equal_more > 0) {
            printf("Existem %d empresas, empatas com o maior numero de comentarios, %d, que são:\n", equal_more, more_comme);
            for(i = 0; i < companies.cont_comp; i++) {
                if(companies.company[i].cont_coments == more_comme) {
                    printf("Empresa nº%d\n", i + 1);
                    printf("Nome da empresa --> %s\n", companies.company[i].name_compa);
                    for(y = 0; y < companies.company[i].cont_coments; y++) {
                        printf("Comentario nº%d\n", i + 1);
                        information_comments(companies, i, y);
                    }
                }
            }
        } else {
            printf("A empresa %s é a empresa com mais comentarios, %d comentarios, sendo eles:\n", companies.company[pos_more].name_compa, more_comme);
            for(i = 0; i < companies.company[pos_more].cont_coments; i++) {
                printf("Comentario nº%d\n", i + 1);
                information_comments(companies, pos_more, i);
            }
        }
        
        if(equal_less > 0) {
            printf("Existem %d empresas, empatas com o menor numero de comentarios, %d, que são:\n", equal_less, less_comme);
            for(i = 0; i < companies.cont_comp; i++) {
                if(companies.company[i].cont_coments == less_comme) {
                    printf("Empresa nº%d\n", i + 1);
                    printf("Nome da empresa --> %s\n", companies.company[i].name_compa);
                    for(y = 0; y < companies.company[i].cont_coments; y++) {
                        printf("Comentario nº%d\n", i + 1);
                        information_comments(companies, i, y);
                    }
                }
            }
        } else {
            if(less_comme > 0) {
                printf("A empresa %s é a empresa com menos comentarios, %d comentarios, sendo eles:\n", companies.company[pos_less].name_compa, less_comme);
                
                for(i = 0; i < companies.company[pos_less].cont_coments; i++) {
                    printf("Comentario nº%d\n", i + 1);
                    information_comments(companies, pos_less, i);
                }
            } else {
                printf("A empresa %s é a empresa com nemos comentarios, não tendo nenhum comentario!\n", companies.company[pos_less].name_compa);
            }   
        }
    } else {
        printf("Só existe uma empresa, a empresa %s e os seus comentarios são os seguintes:\n", companies.company[0].name_compa);
        for(i = 0; i < companies.company[0].cont_coments; i++) {
            printf("Comentário nº%d\n", i + 1);
            information_comments(companies, 0, i);
        }
    }
}

/**
 * @brief Creates a report on the usage of company search options.
 *
 * It calculates the total number of times the user searched for a company, and then shows how many times each search
 * method was used.
 *
 * Then it compares how many times each option was used and shows the most and least used option(s) or if both were used 
 * the same number of times.
 * @param search_comp Struct Search_comp, which contains the counter for each search method.
 * @note If only one search method was used in total, that method will be presented. 
 */
void report_search(Search_comp search_comp) {
    int tot = 0;
    tot = search_comp.cont_name + search_comp.cont_category + search_comp.cont_loc;
    
    printf("Total de vezes que a opção de pesquisar pelo nome foi usada --> %d\n", search_comp.cont_name);
    printf("Total de vezes que a opção de pesquisar pela categoria foi usada --> %d\n", search_comp.cont_category);
    printf("Total de vezes que a opção de pesquisar pela localidade foi usada --> %d\n", search_comp.cont_loc);
    
    if (tot == 1) {
        if (search_comp.cont_name > 0) {
            printf("De momento o único método de procura por empresa que o utilizador utilizou foi pela nome, %d vezes.\n", search_comp.cont_name);
        } else if (search_comp.cont_category > 0) {
            printf("De momento o único método de procura por empresa que o utilizador utilizou foi pela categoria, %d vezes.\n", search_comp.cont_name);
        } else if (search_comp.cont_loc > 0) {
            printf("De momento o único método de procura por empresa que o utilizador utilizou foi pela localidade, %d vezes.\n", search_comp.cont_loc);
        }
    } else { 
        if (search_comp.cont_name > search_comp.cont_category && search_comp.cont_name > search_comp.cont_loc) {
            printf("A opção de procurar pelo o nome é a mais utilizada, %d vezes.\n", search_comp.cont_name);
            
            if (search_comp.cont_category > search_comp.cont_loc) {
                printf("A opção de procuara pela a locadidade é a que foi utilizada menos vezes pelo utilizador, sendo utilizada %d vezes.\n", search_comp.cont_loc);
            } else if (search_comp.cont_loc > search_comp.cont_category){
                printf("A opção de procuara pela a categoria é a que foi utilizada menos vezes pelo utilizador, sendo utilizada %d vezes.\n", search_comp.cont_category);
            } else if (search_comp.cont_loc == search_comp.cont_category) {
                printf("A opção de procurar pela a localidade e pela categoria são as que forma menos utilizados, sendo usadas %d vezes,\n", search_comp.cont_category);
            }
        } else if (search_comp.cont_category > search_comp.cont_name && search_comp.cont_category > search_comp.cont_loc) {
            printf("A opção de procurar pela categoria é a mais utilizada, %d vezes.\n", search_comp.cont_category);
            
            if (search_comp.cont_name > search_comp.cont_loc) {
                printf("A opção de procuara pela a locadidade é a que foi utilizada menos vezes pelo utilizador, sendo utilizada %d vezes.\n", search_comp.cont_loc);
            } else if (search_comp.cont_loc > search_comp.cont_name){
                printf("A opção de procuara pela o nome é a que foi utilizada menos vezes pelo utilizador, sendo utilizada %d vezes.\n", search_comp.cont_name);
            } else if (search_comp.cont_loc == search_comp.cont_name) {
                printf("A opção de procurar pela a localidade e pelo nome são as que forma menos utilizados, sendo usadas %d vezes,\n", search_comp.cont_name);
            }
        } else if (search_comp.cont_loc > search_comp.cont_name && search_comp.cont_loc > search_comp.cont_category) {
            printf("A opção de procurar pela localidade é a mais utilizada, %d vezes.\n", search_comp.cont_loc);
            
            if (search_comp.cont_name > search_comp.cont_category) {
                printf("A opção de procuara pela a categoria é a que foi utilizada menos vezes pelo utilizador, sendo utilizada %d vezes.\n", search_comp.cont_category);
            } else if (search_comp.cont_category > search_comp.cont_name){
                printf("A opção de procuara pela o nome é a que foi utilizada menos vezes pelo utilizador, sendo utilizada %d vezes.\n", search_comp.cont_name);
            } else if (search_comp.cont_name == search_comp.cont_category) {
                printf("A opção de procurar pela categoria e pelo nome são as que forma menos utilizados, sendo usadas %d vezes,\n", search_comp.cont_name);
            }
        } else if (search_comp.cont_name == search_comp.cont_category && search_comp.cont_name > search_comp.cont_loc) {
            printf("A opção de procurar pelo e nome e pela a categoria são as mais usadas, %d vezes.\n", search_comp.cont_name);
            printf("A opção de procuara pela localidade foi a menos utilizada, %d vezes.\n", search_comp.cont_loc);
        } else if (search_comp.cont_name == search_comp.cont_loc && search_comp.cont_name > search_comp.cont_category) {
            printf("A opção de procurar pelo e nome e pela localidade são as mais usadas, %d vezes.\n", search_comp.cont_name);
            printf("A opção de procuara pela categoria foi a menos utilizada, %d vezes.\n", search_comp.cont_category);
        } else if (search_comp.cont_category == search_comp.cont_loc && search_comp.cont_category > search_comp.cont_name) {
            printf("A opção de procurar pela categoria e pela localidade são as mais usadas, %d vezes.\n", search_comp.cont_category);
            printf("A opção de procuara pelo nome foi a menos utilizada, %d vezes.\n", search_comp.cont_name);
        } else if (search_comp.cont_name == search_comp.cont_category && search_comp.cont_name == search_comp.cont_loc) {
            printf("Todas as opções foram usadas o mesmo numero de vezes, sendo utilizadas %d vezes.\n", search_comp.cont_category);           
        }   
    }
}