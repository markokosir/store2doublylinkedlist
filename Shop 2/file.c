/***********************************
*
*       file.c
*
***********************************/

#include "file.h"

int CheckExist(const char *file_name)
{
        FILE *d;

        d = fopen(file_name, "r");
        if(d == NULL)
        {
                return 0;
        }
        else
        {
                fclose(d);
                return 1;
        }
}

void SaveProd(goods **head)
{
        int j = 0;
        int e = 0;
        int q = 0;
        char file_name[20];
        char option;
        goods* search;

        FILE *p;

        SetCursorType(NO_CURSOR);
        ClrScr();
        if(*head == NULL)
		{
			printf("No products to save.");
			getch();
			goto out;
		}
        search = *head;

        change:;
        ClrScr();
        SetCursorType(NORMAL_CURSOR);
        printf("SAVE\n\n");
        printf("Save as: ");
        GetStr(file_name, 15);
        for(j = 0; j < 17; j++)
        {
                if(file_name[j] == 0)
                {
                        file_name[j] = '.';
                        file_name[j+1] = 't';
                        file_name[j+2] = 'x';
                        file_name[j+3] = 't';
                        file_name[j+4] = 0;
                        break;
                }
        }
        e = CheckExist(file_name);
        if(e == 1)
        {
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s already exist, do you want to replace it?(Y/N)", file_name);
                option = getch();
                if(option == 'Y' || option == 'y')
                {
                        goto overwrite;
                }
                else
                {
                        goto change;
                }
        }
        else
        {
                overwrite:;
                p = fopen(file_name, "w");
                if(p == NULL)
                {
                        SetCursorType(NO_CURSOR);
                        ClrScr();
                        printf("File %s can not be opened!", file_name);
                        getch();
                }
                //save products in database
                else
                {
                        while(search != NULL)
                        {
                                for(q = 0; search->product_name[q] != 0; q++)
                                {
                                        if(search->product_name[q] == ' ')
                                        {
                                                search->product_name[q] = '_';
                                        }
                                }
                                fprintf(p, "%16s\t%d\t%f\t%d\n", search->product_name, search->code, search->price, search->supply);
                                for(q = 0; search->product_name[q] != 0; q++)
                                {
                                        if(search->product_name[q] == '_')
                                        {
                                                search->product_name[q] = ' ';
                                        }
                                }
                                search = search->next;
                        }
                        z = 1;
                        SetCursorType(NO_CURSOR);
                        ClrScr();
                        printf("File %s saved!", file_name);
                        getch();
                }
        fclose(p);
        }
        out:;
        SetCursorType(NORMAL_CURSOR);
}

void LoadProd(goods **head)
{
        int j = 0;
        int q = 0;
        int keep_on = 1;
        char choice;
        char file_name[20];
        goods *product;
        goods *search;

        FILE *k;

        ClrScr();
        printf("LOAD\n\n");
        printf("Open file: ");
        GetStr(file_name, 15);
        for(j = 0; j < 17; j++)
        {
                if(file_name[j] == 0)
                {
                        file_name[j] = '.';
                        file_name[j+1] = 't';
                        file_name[j+2] = 'x';
                        file_name[j+3] = 't';
                        file_name[j+4] = 0;
                        break;
                }
        }
        k = fopen(file_name, "r");
        if(k == NULL)
        {
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s can not be opened!", file_name);
                getch();
        }
        else
        {
                ClrScr();
                while(keep_on == 1)
                {
                        search = *head;
                        product = NULL;
                        product = malloc(sizeof(struct goods));
                        if(product != NULL)
                        {
                                if(fscanf(k, "%16s\t%d\t%f\t%d\n", product->product_name, &product->code, &product->price, &product->supply) == 4)
                                {
                                        keep_on = 1;

                                        for(q = 0; product->product_name[q] != 0; q++)
                                        {
                                                if(product->product_name[q] == '_')
                                                {
                                                        product->product_name[q] = ' ';
                                                }
                                        }
                                        
                                        //check if there are any duplicates
                                        while(search != NULL)
                                        {
                                                if(product->code == search->code)
                                                {
                                                        printf("-------------------------------------------------------------\n");
                                                        printf("Code %d already exist.\n", search->code);
                                                        printf("Current product: %s, %d, %.2f, %d\n", search->product_name, search->code, search->price, search->supply);
                                                        printf("Product from file (%s): %s, %d, %.2f, %d\n", file_name, product->product_name, product->code, product->price, product->supply);
                                                        printf("Replace current product?(Y/N)\n");
                                                        choice = getch();
                                                        //replace product with the new one
                                                        if(choice == 'Y' || choice == 'y')
                                                        {
                                                                //only one product in the list
                                                                if((search->prev == NULL) && (search->next == NULL))
                                                                {
                                                                        product->next = NULL;
                                                                        product->prev = NULL;
                                                                        *head = product;
                                                                        free(search);
                                                                        goto next_prod;
                                                                }
                                                                else
                                                                {
                                                                        //first product in the list
                                                                        if(search->prev == NULL)
                                                                        {
                                                                                product->prev = NULL;
                                                                                product->next = search->next;
                                                                                search->next->prev = product;
                                                                                //since is first product in the list reassign address
                                                                                *head = product;
                                                                        }
                                                                        //last product in the list
                                                                        else if(search->next == NULL)
                                                                        {
                                                                                product->next = NULL;
                                                                                product->prev = search->prev;
                                                                                search->prev->next = product;
                                                                        }
                                                                        else
                                                                        {
                                                                                product->next = search->next;
                                                                                product->prev = search->prev;
                                                                                search->next->prev = product;
                                                                                search->prev->next = product;
                                                                        }
                                                                        free(search);
                                                                        goto next_prod;
                                                                }
                                                        }
                                                        //do not insert current product
                                                        else
                                                        {
                                                                free(product);
                                                                goto next_prod;
                                                        }
                                                }
                                                search = search->next;
                                        }
                                        //first product in the list
                                        if(*head == NULL)
										{
											*head = product;
											product->next = NULL;
											product->prev = NULL;
										}
                                        else
                                        {
                                                AddBegin(head, product);
                                        }
                                }
                                else
                                {
                                        keep_on = 0;
                                }
                        }
                        else
                        {
                                printf("Out of memory!");
                                getch();
                                goto out;
                        }
                        next_prod:;
                }
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s successfully loaded!", file_name);
                getch();
                out:;
                z = 0;
                fclose(k);
        }
        SetCursorType(NORMAL_CURSOR);
}   

void CheckSave(const int save, goods **head)
{
        char option;
		COORD scrCoordinates = {0};

		scrCoordinates.X = 30;
		scrCoordinates.Y = 10;

        if(save == 0)
        {
                ClrScr();
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), scrCoordinates);
                printf("Save changes?(Y/N)");
                option = getch();
                if(option == 'Y' || option == 'y')
                {
                        SaveProd(&*head);
                }
        }
}