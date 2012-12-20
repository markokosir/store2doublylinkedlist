/***********************************
*
*       product.h
*
***********************************/

#ifndef PRODUCT_H
#define PRODUCT_H

#include "main.h"

#define ARROW_UP 328    
#define ARROW_DOWN 336
#define RETURN 13
#define NORMAL_CURSOR 1
#define NO_CURSOR 0

//function prototypes
void EnterProd(struct goods **head);
void AddBegin(struct goods **head, struct goods *product);
void AddEnd(struct goods **head, struct goods *product);
void DeleteProd(struct goods **heads);
void FindProd(struct goods **head);
void SellProd(struct goods **head);
void DisplayProd(struct goods **head);
void SortProd(struct goods **head);
int KeyPress(void);
int Menu(void);
void ClrScr(void);
void SetCursorType(int cursor);

#endif //PRODUCT_H