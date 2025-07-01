/**
 * @file inputs_file_memory.c
 * @author Studentes: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 *  
 * @brief inputs_file_memory.c file, Manage program memory and data storage
 * 
 * In inputs_file_memory.c, there are all the inputs, responsible for saving all the data from the program into a 
 * file, and also the necessary input to load the data from the file into the corresponding struct and to allocate 
 * dynamic memory for them.
 */

#include <stdio.h>
#include <stdlib.h>

#include "inputs_file_memory.h"
#include "op_user.h"

static int i = 0, y = 0;

/**
 * @brief Load the information saved in the file and allocate dynamic memory based on it
 *
 * In this option, all the information saved in the files "ficheiro_empresas.bin", "ficheiro_branch.bin" and 
 * "ficheiro_procurar.bin" is loaded and based on the value of their counters, memory is allocated for the fields that 
 * need it and all information saved in them is loaded into the corresponding struct(s).
 * The function starts by opening one file at a time, first opening the companies file and when the process of loading the 
 * data from the file, if any, and allocating memory for the companies is finished, the same file is closed and the file 
 * of the branches of activity is opened, which performs the same process until it is closed (of loading the branches of 
 * activity and allocating memory), finally after the branches file is closed, the search companies file is opened and 
 * only the data from the file is loaded because in this struct none of the fields need dynamic memory.
 * 
 * @param companies Pointer to the Companies struct.
 * @param branchs Pointer to the Branch_Activity struct.
 * @param search_comp Pointer to the Search_comp struct.
 * 
 * @note If the counter of the companies, branches, ratings or comments comes to 0 the value of the respective size
 * will be 1.
 * @note If any of the mentioned files is not created, it is created in this function.
 * @note The fields that need dynamic memory of the companies are: companies.company (For the companies), 
 * companies.company[i].comment (For each company comment), companies.company[i].comp_class (For the company ratings) 
 * @note The field that needs dynamic memory of the branches of activity is: branchs.branch (For the branches of activity)  
 */
void load_file(Companies *companies, Branch_Activity *branchs, Search_comp *search_comp) {
    FILE *file_comp = fopen(FILE_COMPANY, "rb");
    
    if (file_comp == NULL) {
        FILE *new_file_comp = fopen(FILE_COMPANY, "wb");
        
        if (new_file_comp == NULL) {
            printf("Erro ao criar o novo ficheiro.\n");
        }

        printf("Ficheiro para as empresas criado com sucesso!\n");
        
        if (ferror(new_file_comp)) {
            perror("Erro:");
        }
        
        fclose(new_file_comp);
    } else {
        fseek(file_comp, 0, SEEK_SET);
        fread(&companies->cont_comp, sizeof(int), 1, file_comp);
        
        if (companies->cont_comp == 0) {
            companies->size_company = 1;
        } else {
            companies->size_company = companies->cont_comp; 
        }
    }
    
    companies->company = (Data_companies *) malloc(sizeof(Data_companies) * companies->size_company);
    
    if (companies->company == NULL) {
        printf("Erro a alocar memoria para as empresas.\n");
    } else {
        fread(&companies->company, sizeof(Data_companies), companies->cont_comp, file_comp);
        for (i = 0; i < companies->cont_comp; i++) {
            fread(&companies->company[i], sizeof(Data_companies), 1, file_comp);
            
            if (companies->company[i].cont_coments == 0) {
                companies->company[i].size_comments = 1;
            } else {
                companies->company[i].size_comments = companies->company[i].cont_coments;
            }

            companies->company[i].comment = (Comments *) malloc(sizeof(Comments) * companies->company[i].size_comments);
            
            if (companies->company[i].comment == NULL) {
                printf("Erro: Falha ao realocar memória, para os comentarios.\n");
            } else {
                fread(companies->company[i].comment, sizeof(Comments), companies->company[i].cont_coments, file_comp);
            }

            if (companies->company[i].cont_classi == 0) {
                companies->company[i].size_classi = 1;
            } else {
                companies->company[i].size_classi = companies->company[i].cont_classi;
            }
            
            companies->company[i].comp_class = (Classification *) malloc(sizeof(Classification) * companies->company[i].size_classi);
          
            if (companies->company[i].comp_class == NULL) {
                printf("Erro: Falha ao realocar memória, para as classificações.\n");
            } else {
                fread(companies->company[i].comp_class, sizeof(Classification), companies->company[i].cont_classi, file_comp);
            }          
        }
    }
    fclose(file_comp);
    
    FILE *file_bran = fopen(FILE_BRANCH, "rb");
    
    if(file_bran == NULL) {
        FILE *new_file_bran = fopen(FILE_BRANCH, "wb");
        
        if (new_file_bran == NULL) {
            printf("Erro ao criar o novo ficheiro.\n");
        }

        printf("Ficheiro para os ramos criado com sucesso!\n");
        
        if (ferror(new_file_bran)) {
            perror("Erro:");
        }
        
        fclose(new_file_bran);
    } else {
        fseek(file_bran,0,SEEK_SET);
        fread(&branchs->cont_branch, sizeof (int), 1, file_bran);
        
        if (branchs->cont_branch == 0) {
            branchs->size_branch = 1;
        } else {
            branchs->size_branch = branchs->cont_branch;
        }
    }
    
    branchs->branch = (Data_Branch *) malloc(sizeof(Data_Branch) * branchs->size_branch);
    
    if (branchs->branch == NULL) {
        printf("Erro a alocar memoria para os ramos.\n");
    } else {
        for(i = 0; i < branchs->cont_branch; i++){
            fread(&branchs->branch[i], sizeof (Data_Branch), 1, file_bran);
        }
    }

    fclose(file_bran);
    
    FILE *file_search = fopen(FILE_SEARCH, "rb");
    
    if(file_search == NULL) {
        FILE *new_file_search = fopen(FILE_SEARCH, "wb");
        
        if (new_file_search == NULL) {
            printf("Erro ao criar o novo ficheiro.\n");
        }

        printf("Ficheiro para os procurar empresa criado com sucesso!\n");
        
        if (ferror(new_file_search)) {
            perror("Erro:");
        }
        
        fclose(new_file_search);
    } else {
        fseek(file_search,0,SEEK_SET);
        fread(&search_comp->cont_name, sizeof(int), 1, file_search);
        fread(&search_comp->cont_category, sizeof(int), 1, file_search);
        fread(&search_comp->cont_loc, sizeof(int), 1, file_search);
    }
    fclose(file_search);   
}

/**
 * @brief Saves the company data to a file.
 * 
 * This function stores in the file "ficheiro_empresas.bin" all data from the companies' struct (their information, 
 * their comments and their ratings) and the companies' counter.
 * This function takes all the data from the company struct and rewrites each one in the company file.
 * 
 * @param companies Pointer to the Companies struct.
 * @note The function uses the fopen, fseek, fwrite, and fclose functions from the standard library. 
 * @note This function uses the "rb+" file opening mode to read and write companies in the file.
 */
void save_file_comp(Companies *companies) {
    FILE *file_comp = fopen(FILE_COMPANY, "rb+");
    
    if (file_comp == NULL) {
        printf("O ficheiro das empresas não existe!\n");
    } else {
        fseek(file_comp, 0, SEEK_SET);
        fwrite(&companies->cont_comp, sizeof(int), 1, file_comp);
        
        for(i = 0; i < companies->cont_comp; i++) {
            fwrite(&companies->company[i], sizeof(Data_companies), 1, file_comp); 
            
            for(y = 0; y < companies->company[i].cont_coments; y++) {
                fwrite(&companies->company[i].comment[y], sizeof(Comments), 1, file_comp);
            }
            for(y = 0; y < companies->company[i].cont_classi; y++) {
                fwrite(&companies->company[i].comp_class[y], sizeof(Classification), 1, file_comp);
            }
        }
    }

    fclose(file_comp);
}

/**
 * @brief Saves the branch activity data to a file.
 * 
 * This function stores in the file "ficheiro_branch.bin" all data from the branchs activity and the branchs counter.
 * This function takes all the data from the Branch_Activity struct and rewrites each one in the branchs file.
 * 
 * @param branchs Pointer to the Branch_Activity struct.
 * 
 * @note The function uses the fopen, fseek, fwrite, and fclose functions from the standard library. 
 * @note This function uses the "rb+" file opening mode to read and write branchs in the file.
 */
void save_file_branchs(Branch_Activity *branchs) {
    FILE *file_branch = fopen(FILE_BRANCH, "rb+");

    if (file_branch == NULL) {
        printf("O ficheiro dos ramos não existe!\n");
    } else {
        fseek(file_branch, 0, SEEK_SET);
        fwrite(&branchs->cont_branch, sizeof(int), 1, file_branch);
        
        for(i = 0; i < branchs->cont_branch; i++) {
            fwrite(&branchs->branch[i], sizeof(Data_Branch), 1, file_branch);     
        }
    }

    fclose(file_branch);
}

/**
 * @brief Saves the search data to a file.
 * 
 * This function stores in the file "ficheiro_procurar.bin" all data from the Search_comp struct.
 * This function takes all the data from the Search_comp struct and rewrites each one in the search comp file.
 * 
 * @param search_comp Pointer to the Search_comp struct.
 * 
 * @note The function uses the fopen, fseek, fwrite, and fclose functions from the standard library. 
 * @note This function uses the "rb+" file opening mode to read and write searh_Comp struct in the file.
 */
void save_search_comp(Search_comp *search_comp) {
    FILE *file_search = fopen(FILE_SEARCH, "rb+");

    if (file_search == NULL) {
        printf("O ficheiro dos procura de empresas não existe!\n");
    } else {
        fseek(file_search, 0, SEEK_SET);
        fwrite(&search_comp->cont_name, sizeof(int), 1, file_search);
        fwrite(&search_comp->cont_category, sizeof(int), 1, file_search);
        fwrite(&search_comp->cont_loc, sizeof(int), 1, file_search);
    }

    fclose(file_search);
}