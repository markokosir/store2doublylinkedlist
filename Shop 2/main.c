/********************************************************************************************************
Program: Store 2 - Doubly Linked List
Author: Marko Kosir

Store 2 is implemented using doubly linked list. When the program starts it allocates memory for 4 products on heap.

Files included:
                - products.txt	                sample database
                - codes.txt						codes for products
                - main.h & main.c				heart of a program
                - product.h & product.c	        general functions for working with products
                - file.h & file.c				functions for working with files
                - utils.h & utils.c				utilities functions

Note: All the code is written in pure C programming language, however header file conio.h is
      inlcuded in this program(windows.h is also included for rendering reasons), which is 
      not part of ANSI C standard.                         

Tested - Windows XP
Compiled - Microsoft Visual Studio 2005

Released: July 17th, 2005

Upgrade log:
ported to MVS 2010  (18.9.2010)
********************************************************************************************************/
#include "main.h"

int z = 1;

int main()
{
        goods *head = NULL;//pointer to first product in the list
        goods *product;
        //pointers for freeing memory
        goods *delete1;
        goods *delete2;
        int value;//star location
        int q;

        for(q = 0; q < 4; q++)
        {
                //save some products in memory
                product = NULL;
                product = malloc(sizeof(struct goods));
                if(product != NULL)
                {
                        if(q == 0)
                        {
                                strcpy(product->product_name, "APPLES");
                                product->code = 852;
                                product->price = 1.25;
                                product->supply = 30;
                        }
                        if(q == 1)
                        {
                                strcpy(product->product_name, "MILK");
                                product->code = 123;
                                product->price = 2;
                                product->supply = 30;
                        }
                        if(q == 2)
                        {
                                strcpy(product->product_name, "JUICE");
                                product->code = 121;
                                product->price = 2.39;
                                product->supply = 30;
                        }
                        if(q == 3)
                        {
                                strcpy(product->product_name, "CHOCOLATE");
                                product->code = 567;
                                product->price = 1.5;
                                product->supply = 30;
                        }
                        //first product in the list
                        if(head == NULL)
                        {
                                head = product;
                                product->next = NULL;
                                product->prev = NULL;
                        }
                        else
                        {
                                //add a new product at the begining of the list
                                goods *first;
                                first = head;
                                first->prev = product;
                                product->prev = NULL;
                                product->next = first;
                                head = product;
                        }
                }
                else
                {
                        printf("Not enough memory to start program!");
                        getch();
                        goto out;
                }
        }

        do
        {
                value = Menu();
                //turn on cursor
                SetCursorType(NORMAL_CURSOR);
                switch(value)             
                {
                        case 0: EnterProd(&head);
                                break;
                        case 1: DeleteProd(&head);
                                break;
                        case 2: FindProd(&head);
                                break;
                        case 3: SellProd(&head);
                                break;
                        case 4: DisplayProd(&head);
                                break;
                        case 5: SortProd(&head);
                                break;
                        case 6: LoadProd(&head);
                                break;
                        case 7: SaveProd(&head);
                                break;
                        case 8: CheckSave(z, &head);
                                break;
                }
        }while(value != 8);

        out:;
        //free allocated memory for all products
        if(head == NULL)
        {
                return 0;
        }
        delete1 = head;
        while(delete1 != NULL)
        {
                delete2 = delete1->next;
                free(delete1);
                delete1 = delete2;
        }
        head = NULL;

        return 0;
}
