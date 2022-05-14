#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "list_mm.h"

#define _POSIX_C_SOURCE 200809L

bool equal_elements(Element* first, Element* second) {
    return strcmp(first->date, second->date) == 0;
}

void replace_char(char* str,  int length, char char_to_replace, char replacement){
    for(int i = 0; i < length; i++){
        if(str[i] == char_to_replace){
            str[i] = replacement;
        }
    }
}

int main() {
    char filename[] = "data.iade";
    ListMM list = list_create(filename);
    if (list == NULL) {
        list = list_open(filename);
    }

    char* line = NULL;
    size_t line_chars = 0;
    while (true) {
        int size = getline(&line, &line_chars, stdin);
        replace_char(line, size, '\n','\0');
        
        if (strcmp(line, "") == 0) {
            break;
        }
        char* command = strtok(line, " ");
        
        if (strcmp(command, "AR") == 0) {
            char* date = strtok(NULL, " ");
            char* temperature = strtok(NULL, " ");
            Element element;
            element.temperature = strtof(temperature, NULL);
            strcpy(element.date, date);
            list_insert_last(list, &element);

            printf("Valor registado com sucesso.\n");
        } else if (strcmp(command, "CR") == 0) {
            char* date = strtok(NULL, " ");
            date[8] = '\0';
            // * Implementar uma função que compara elementos
            // * Criar um elemento com a data
            Element element;
            strcpy(element.date, date);
            // * Invocar list_find
            int idx = list_find(list, equal_elements, &element);
            // * Mostrar a temperatura para a data indicada
            if (idx >= 0) {
                Element target = list_get(list, idx);
                printf("A temperatura em %s foi %1.2f\n", target.date, target.temperature);
            } else {
                printf("Data sem registo.\n");
            }
        } else if (strcmp(command, "LR") == 0) {
            for(size_t i=0; i<list_size(list); i++) {
                Element element = list_get(list, i);
                printf("%s -> %1.2f\n", element.date, element.temperature);
            }
        }
        else if (strcmp(command, "ER") == 0) {
            char* date = strtok(NULL, " ");
            date[8] = '\0';
            Element element;
            strcpy(element.date, date);
            int idx = list_find(list, equal_elements, &element);
            if(idx < 0) {
                printf("Registo inexistente.\n");
            }
            else {
                list_remove(list, idx);
                printf("Registo removido com sucesso.\n");
            }
        }
    }

    list_close(list);

    free(line);
    return 0;
}