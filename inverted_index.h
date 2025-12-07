#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 27   // 26 letters + 1 for others

typedef struct FileNode
{
    char filename[50];
    int count;
    struct FileNode *next;
} FileNode;

typedef struct WordNode
{
    char word[50];
    int file_count;
    FileNode *files;
    struct WordNode *next;
} WordNode;

extern WordNode *hashTable[SIZE];
int get_index(char *word);
int insert_file(char *filename);
int insert_word(char *word, char *filename);
int process_file(char *filename);
void create_database();
void update_database();
void display_database();
void search_word();
void save_database();
#endif

