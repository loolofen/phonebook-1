#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
// #define OPT 1

typedef struct __DETAIL {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *detailInfo;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;


#ifdef HASH
#define HASH_TABLE_SIZE 2000
entry *hash_table[HASH_TABLE_SIZE];
entry *hash_table_cur[HASH_TABLE_SIZE];//cur linked list end
void free_ht();
unsigned int BKDR_hash(char lastName[], int hash_table_size);
unsigned int DJB2_hash(char lastName[], int hash_table_size);
#endif

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);




#endif
