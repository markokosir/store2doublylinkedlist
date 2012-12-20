/***********************************
*
*       file.h
*
***********************************/

#ifndef FILE_H
#define FILE_H

#include "main.h"

//function prototypes
int CheckExist(const char *file_name);
void SaveProd(struct goods **head);
void LoadProd(struct goods **head);
void CheckSave(const int save, struct goods **head);

#endif //FILE_H