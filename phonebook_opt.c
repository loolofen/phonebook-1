#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "phonebook_opt.h"

#ifdef HASH
unsigned int BKDR_hash(char lastName[], int hash_table_size)
{

    unsigned int seed = 131;
    unsigned int hash = 0;
    int i = 0;
    while(lastName[i] != '\0') {
        hash = hash * seed + lastName[i];
        i++;
    }

    return hash %= hash_table_size;
}


unsigned int DJB2_hash(char lastName[], int hash_table_size)
{
    unsigned int hash = 5381;
    int c;
    int i = 0;

    while (c = lastName[i++])
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash %= hash_table_size;
}
#endif

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastName[], entry *pHead)
{
#ifdef HASH
    entry *find = hash_table[DJB2_hash(lastName, HASH_TABLE_SIZE)];
    while(find != NULL) {
        if(strcasecmp(lastName, find->lastName) == 0)
            return find;
        find = find->pNext;
    }
    return NULL;
#else
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
#endif
}

entry *append(char lastName[], entry *e)
{
#ifdef HASH
    int hash_num = DJB2_hash(lastName, HASH_TABLE_SIZE);
    if(hash_table[hash_num]) { //head already exist
        entry* ap =  hash_table_cur[hash_num];
        ap->pNext = (entry*) malloc(sizeof(entry));
        ap = ap->pNext;
        strcpy(ap->lastName, lastName);
        ap->pNext = NULL;
        hash_table_cur[hash_num] = ap;
        return ap;
    } else { //first time create head
        hash_table[hash_num] = (entry *)malloc(sizeof(entry));
        strcpy(hash_table[hash_num]->lastName, lastName);
        hash_table[hash_num]->pNext = NULL;
        hash_table_cur[hash_num] = hash_table[hash_num];
        return hash_table[hash_num];
    }
#else
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
#endif
}

#ifdef HASH
void free_ht()
{
    for(int i=0; i<HASH_TABLE_SIZE; i++) {
        if(hash_table[i]) {
            entry *cur = hash_table[i];
            while(cur != NULL) {
                entry *tmp = cur;
                cur = cur->pNext;
                free(tmp);
            }
        }
    }
}
#endif
