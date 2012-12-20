/***********************************
*
*       product.c
*
***********************************/

#include "product.h"

void EnterProd(goods **head)
{
        int code = 0;
        char choice;
        char option;
        goods *product;
        goods *search;

        ClrScr();
        do
        {
                product = NULL;
                product = malloc(sizeof(struct goods));
                if(product != NULL)
				{
                        begin_input:;
                        search = *head;
                        SetCursorType(NORMAL_CURSOR);
                        ClrScr();
                        z = 0;
                        printf("ENTER PRODUCT\n\n");
                        printf("Product: ");
                        GetStr(product->product_name, 13);
                        printf("Code: ");
                        if(GetNum("%d" ,&code, 5) == NULL)
                        {
                                goto begin_input;
                        }
                        //check if a code already exist
                        while(search != NULL)
                        {
                                if(search->code == code)
                                {
                                        printf("Code %d already exist.", code);
                                        getch();
                                        goto begin_input;
                                }
                                search = search->next;
                        }
                        product->code = code;
                        printf("Price: ");
                        if(GetNum("%f" , &product->price, 4) == NULL)
                        {
                                goto begin_input;
                        }
                        printf("Supply: ");
                        if(GetNum("%d", &product->supply, 5) == NULL)
                        {
                                goto begin_input;
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
                                //simple menu, because I am lazy :)
								printf("\nb - Add product at the beginning of the list.\n");
								printf("e - Add product at the end of the list.\n");
                                printf("c - Cancel\n");
								choice = getch();
								switch(choice)
								{
									case 'b': AddBegin(head, product);
															  break;
													case 'e': AddEnd(head, product);
															  break;
													case 'c': free(product);
															  break;
													default : free(product);
								}
						}
                        printf("\nEnter another product?(Y/N)");
                        option = getch();
                }
                else
                {
                        printf("Out of memory!");
                        getch();
                        option = 'n';
                }
        }while(option == 'Y' || option == 'y');
}

void AddBegin(goods **head, goods *product)
{
        //add a new product at the begining of the list
        goods *first = NULL;
        first = *head;
        first->prev = product;
        product->prev = NULL;
        product->next = first;
        *head = product;
}

void AddEnd(goods **head, goods *product)
{
	goods *last = NULL;
	goods *search = NULL;
	search = *head;
	//serch for the last product in the list
	while(search != NULL)
	{
		last = search;
		search = search->next;
	}
	//add product to the end of a list
	last->next = product;
	product->next = NULL;
	product->prev = last;
}

void DeleteProd(goods **head)
{
        int code;
        char option;
        goods *search;

        ClrScr();
        SetCursorType(NO_CURSOR);
        if(*head == NULL)
        {
                printf("No products to delete.");
				getch();
                goto out;
        }
        do
        {
                begin_input:;
                ClrScr();
                SetCursorType(NORMAL_CURSOR);
                search = *head;
                printf("DELETE PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" , &code, 5) == NULL)
                {
                        goto begin_input;
                }
                while(search != NULL)
                {
                        if(search->code == code)
                        {
								z = 0;
                                //delete first product from the list
                                if(search->prev == NULL)
                                {
                                        //there is only one product in the list
                                        if(search->next == NULL)
                                        {
                                                free(search);
                                                *head = NULL;
                                                SetCursorType(NO_CURSOR);
                                                printf("Product has been deleted.\n");
                                                printf("No more products to delete.");
                                                getch();
                                                goto out;
                                        }
                                        //assign head to new first product
                                        *head = search->next;
                                        search->next->prev = NULL;
                                        free(search);
                                }
                                //delete last product in the list
                                else if(search->next == NULL)
                                {
                                        search->prev->next = NULL;
                                        free(search);
                                }
                                else
                                {
                                        search->prev->next = search->next;
                                        search->next->prev = search->prev;
                                        free(search);
                                }
                                printf("Product has been deleted.\n");
                                printf("Delete another product?(Y/N)");
                                option = getch();
                                break;
                        }
						search = search->next;
                }
                if(search == NULL)
                {
                        printf("Code %d doesn't belong to any product.\n", code);
                        printf("Delete another product?(Y/N)");
                        option = getch();
                }
        }while(option == 'Y' || option == 'y');
        out:;
}

void FindProd(goods **head)
{
        int code;
        char option;
        goods *search;

        ClrScr();
        if(*head == NULL)
        {
                SetCursorType(NO_CURSOR);
                printf("No products to find.");
				getch();
                goto out;
        }
        do
        {
                begin_input:;
                ClrScr();
                SetCursorType(NORMAL_CURSOR);
                search = *head;
                printf("FIND PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" , &code, 5) == NULL)
                {
                        goto begin_input;
                }
                while(search != NULL)
                {
                        if(search->code == code)
                        {
                                printf("%s, %.2f €,  %d pieces.\n\n", search->product_name, search->price, search->supply);
                                printf("Find another product?(Y/N)");
                                option = getch();
                                break;
                        }
                        search = search->next;
                        if(search == NULL)
                        {
                                printf("Code %d doesn't belong to any product.\n", code);
                                printf("Find another product?(Y/N)");
                                option = getch();
                                break;
                        }
                }
        }while(option == 'Y' || option == 'y');
        out:;
}

void SellProd(goods **head)
{
        int code;
        char option;
        goods *search;

        ClrScr();
        if(*head == NULL)
        {
                SetCursorType(NO_CURSOR);
                printf("No products to sell.");
				getch();
                goto out;
        }
        do
        {
                begin_input:;
                ClrScr();
                SetCursorType(NORMAL_CURSOR);
                search = *head;
                printf("SELL PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" , &code, 5) == NULL)
                {
                        goto begin_input;
                }
                while(search != NULL)
                {
                        if(search->code == code)
                        {
                                if(search->supply == 0)
                                {
                                        printf("This product is not available.\n\n");
                                        printf("Sell another product?(Y/N)");
                                        option = getch();
                                        break;
                                }
                                z = 0;
                                search->supply--;
                                printf("Product sold.\n");
                                printf("Supply: %d\n\n", search->supply);
                                printf("Sell another product?(Y/N)");
                                option = getch();
                                break;
                        }
                        search = search->next;
                        if(search == NULL)
                        {
                                printf("Code %d doesn't belong to any product.\n", code);
                                printf("Sell another product?(Y/N)");
                                option = getch();
                                break;
                        }
                }
        }while(option == 'Y' || option == 'y');
        out:;
}

void DisplayProd(goods **head)
{
        goods *product = NULL;
		int num_prod = 0;

        ClrScr();
        SetCursorType(NO_CURSOR);
		if(*head == NULL)
		{
			printf("No products to display.");
			getch();
			goto out;
		}
        product = *head;
        printf("DISPLAY ALL PRODUCTS\n\n");
        printf("|       Product|  Code|     Price|       Supply|\n");
        printf("------------------------------------------------\n");
        while(product != NULL)
		{ 
			num_prod++;
			printf("| %13s| %5d| %7.2f €| %5d pieces|\n", product->product_name, product->code, product->price, product->supply);
			product = product->next;
		}
        printf("\nTotal number of products: %d", num_prod);
        out:;
        getch();
        SetCursorType(NORMAL_CURSOR);
}

void SortProd(goods **head)
{
		//you won't get out with quicksort, let's rather have some fun with pointers ;)
        int j = 0;
        int k = 0;
        int sort = 0;
        goods *search_p;
        goods *search;
        char temp_name1[14];
        char temp_name2[14];

        SetCursorType(NO_CURSOR);
        ClrScr();
        if(*head == NULL)
		{
			printf("No products to sort.");
			getch();
			goto out;
		}
        //sort products alphabetical
        do
        {
                search_p = *head;
                search = search_p->next;
                sort = 0;
                while(search != NULL)
                {
                        strcpy(temp_name1, search_p->product_name);
                        strcpy(temp_name2, search->product_name);
                        for(j = 0; temp_name1[j] != 0; j++)
                        {
                                temp_name1[j] = toupper(temp_name1[j]);
                        }
                        for(k = 0; temp_name2[k] != 0; k++)
                        {
                                temp_name2[k] = toupper(temp_name2[k]);
                        }
                        if(strcmp(temp_name1, temp_name2) > 0)
                        {
                                //first product in the list
                                if(search_p->prev == NULL)
                                {
                                        search->next->prev = search_p;
                                        search_p->next = search->next;
                                        search_p->prev = search;
                                        search->prev = NULL;
                                        search->next = search_p;
                                        *head = search;
                                }
                                //last product in the list
                                else if(search->next == NULL)
                                {
                                        search_p->prev->next = search;
                                        search_p->next = NULL;
                                        search_p->prev = search;
                                        search->next = search_p;
                                        search->prev = search_p->prev;
                                }
                                else
                                {
                                        search_p->prev->next = search;
                                        search->next->prev = search_p;
                                        search->prev = search_p->prev;
                                        search_p->next = search->next;
                                        search_p->prev = search;
                                        search->next = search_p;
                                }
                                sort = 1;
                        }
                        search_p = search;
                        search = search->next;
                }
        }while(sort == 1);
        printf("Products sorted.");
        getch();
        out:;
}

int KeyPress(void)
{
        int key = getch();

        if(key == 0 || key == 224)
        {
                key = 256 + getch();
        }
        return key;
}

int Menu(void)
{
        int j = 0;
        int i = 0;
        int key;
        char shop[] = "                                 *** STORE 2 ***                                 ";
        char display[9][30] = {{"* Enter product"},
                               {"  Delete product"},
                               {"  Find product"},
                               {"  Sell product"},
                               {"  Display all products"},
                               {"  Sort products"},
                               {"  Load"},
                               {"  Save"},
                               {"  Exit"}};

        //display menu
        while(1)
        {
                //necessary delay for 50 miliseconds
                Delay(50);
                ShowCursor(0);
                ClrScr();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
                printf("--------------------------------------------------------------------------------");
                //move text every 100 miliseconds
                if(j == 2)
                {
                        MoveStr(shop, shop[0]);
                        printf("%s", shop);
                        j = 0;
                }
                else
                {
                        printf("%s", shop);
                        j++;
                }
                printf("--------------------------------------------------------------------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
                printf("\n\n\n");
				puts(display[0]);
                puts(display[1]);
                puts(display[2]);
                puts(display[3]);
                puts(display[4]);
                puts(display[5]);
                puts(display[6]);
                puts(display[7]);
                puts(display[8]);
                if(kbhit())
                {
                        key = KeyPress();
                        //change star location - up
                        if(key == ARROW_UP)
                        {
                                for(i = 0; i < 9; i++)
                                {
                                        if(display[i][0] == '*')
                                        {
                                                if( i == 0)
                                                {
                                                        i = 8;
                                                        display[0][0] = ' ';
                                                        display[8][0] = '*';
                                                        break;
                                                }
                                                display[i][0] = ' ';
                                                display[i-1][0] = '*';
                                                i--;
                                                break;
                                        }
                                }
                        }
                        //change star location - down
                        else if(key == ARROW_DOWN)
                        {
                                for(i = 0; i < 9; i++)
                                {
                                        if(display[i][0] == '*')
                                        {
                                                if(i == 8)
                                                {
                                                        i = 0;
                                                        display[8][0] = ' ';
                                                        display[0][0] = '*';
                                                        break;
                                                }
                                                display[i][0] = ' ';
                                                display[i+1][0] = '*';
                                                i++;
                                                break;
                                        }
                                }
                        }
                        //return star location
                        else if(key == RETURN)
                        {
                                return i;
                        }
                }
        }
}

void ClrScr(void)
{
		//get the top left position
	    COORD scrCoordinates = {0};                        
	    //visible characters
	    DWORD charsLenght;
	    DWORD d;                      
	    CONSOLE_SCREEN_BUFFER_INFO buff;

	    //get a handle to the console
	    HANDLE scrHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	    GetConsoleScreenBufferInfo(scrHandle, &buff);

	    //get number of characters
	    charsLenght = buff.dwSize.X * buff.dwSize.Y;

	    //put whitespaces into the screen buffer
	    FillConsoleOutputCharacter(scrHandle, TEXT(' '), charsLenght, scrCoordinates, &d);
	    GetConsoleScreenBufferInfo(scrHandle, &buff);
	    FillConsoleOutputAttribute(scrHandle, buff.wAttributes, charsLenght, scrCoordinates, &d);

	    //put cursor back to the top left position
	    SetConsoleCursorPosition(scrHandle, scrCoordinates);
}

void SetCursorType(int cursor)
{
	CONSOLE_CURSOR_INFO cursorInfo = {0};

	//show cursor
	if(cursor)
	{
		cursorInfo.dwSize = 30;
		cursorInfo.bVisible = TRUE;
		SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &cursorInfo);		
	}
	//hide cursor
	else 
	{
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &cursorInfo);
	}
}