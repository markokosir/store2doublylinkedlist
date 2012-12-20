/***********************************
*
*       main.h
*
***********************************/

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include "product.h"
#include "utils.h"
#include "file.h"

typedef struct goods
{
		char product_name[14];
        int code;
        int supply;
		float price;
        struct goods *next;
        struct goods *prev;
}goods;

//global variables
extern int z;//products saved?

#endif //MAIN_H