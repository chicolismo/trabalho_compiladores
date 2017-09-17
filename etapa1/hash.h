
#ifndef __HASH_H__
#define __HASH_H__

#define HASH_SIZE 1000

struct HashNode {
    char *string;
    int type;
    struct HashNode *next;
};

typedef struct HashNode HashNode;

void initializeHashTable();
int generateHash(const char *string);
HashNode *createHashNode(const char *string, int type);
HashNode *destroyHashNode(HashNode **node);
HashNode *getHashNode(const char *string);
HashNode *setHashNode(const char *string, int type);
void printHashTable();

#endif // __HASH_H__
