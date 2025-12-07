#include "inverted_index.h"
// Hash table
WordNode *hashTable[SIZE] = {NULL};
// Get index based on first letter
int get_index(char *word)
{
    if (isalpha(word[0]))
    return tolower(word[0]) - 'a';
    return 26;
}
// Check file exists
int insert_file(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    return -1;
    fclose(fp);
    return 0;
}
// Insert a word into hash table
int insert_word(char *word, char *filename)
{
    int index = get_index(word);
    WordNode *w = hashTable[index];
    while (w)
    {
        if (strcmp(w->word, word) == 0)
        {
            FileNode *f = w->files;
            while (f)
            {
                if (strcmp(f->filename, filename) == 0)
                {
                    f->count++;
                    return 1;
                }
                f = f->next;
            }
            // Add new file node
            FileNode *newf = malloc(sizeof(FileNode));
            strcpy(newf->filename, filename);
            newf->count = 1;
            newf->next = w->files;
            w->files = newf;
            w->file_count++;

            return 1;
        }
        w = w->next;
    }
    // Create new word node if not found
    WordNode *newWord = malloc(sizeof(WordNode));
    strcpy(newWord->word, word);
    newWord->file_count = 1;
    newWord->next = hashTable[index];

    // Create file node
    FileNode *newFile = malloc(sizeof(FileNode));
    strcpy(newFile->filename, filename);
    newFile->count = 1;
    newFile->next = NULL;
    newWord->files = newFile;
    hashTable[index] = newWord;
    return 1;
}
// Read file word-by-word
int process_file(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    return -1;
    char word[50];
    while (fscanf(fp, "%49s", word) != EOF)
    {
        insert_word(word, filename);
    }
    fclose(fp);
    return 1;
}
// Create database
void create_database()
{
    char file[50];
    printf("Enter file name: ");
    scanf("%s", file);

    if (process_file(file) == 1)
    printf("Database created for file: %s\n", file);
    else
    printf("File not found!\n");
}

// Update database
void update_database()
{
    char file[50];
    printf("Enter file name to update: ");
    scanf("%s", file);
    if (process_file(file) == 1)
    printf("Database updated with file: %s\n", file);
    else
    printf("File not found!\n");
}
// Display database
void display_database()
{
    printf("\n----------- INVERTED INDEX DATABASE -----------\n");
    for (int i = 0; i < SIZE; i++)
    {
        WordNode *w = hashTable[i];
        while (w)
        {
            printf("\nIndex : %d\n", i);
            printf("Word  : %s\n", w->word);
            printf("Files : %d\n", w->file_count);
            FileNode *f = w->files;
            while (f)
            {
                printf("   -> File: %-12s  Count: %d\n",f->filename, f->count);
                f = f->next;
            }
            w = w->next;
        }
    }
    printf("\n-----------------------------------------------\n");
}
// Search for a word
void search_word()
{
    char key[50];
    printf("Enter word to search: ");
    scanf("%s", key);
    int index = get_index(key);
    WordNode *w = hashTable[index];
    while (w)
    {
        if (strcmp(w->word, key) == 0)
        {
            printf("Found in %d file(s):\n", w->file_count);

            FileNode *f = w->files;
            while (f)
            {
                printf("%s -> %d times\n", f->filename, f->count);
                f = f->next;
            }
            return;
        }
        w = w->next;
    }
    printf("Word not found!\n");
}
// Save database to file
void save_database()
{
    char fname[50];
    printf("Enter file name to save: ");
    scanf("%s", fname);

    FILE *fp = fopen(fname, "w");
    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < SIZE; i++)
    {
        WordNode *w = hashTable[i];

        if (w)
            fprintf(fp, "#:%d\n", i);

        while (w)
        {
            fprintf(fp, "%s:%d:", w->word, w->file_count);
            FileNode *f = w->files;
            while (f)
            {
                fprintf(fp, "%s:%d:", f->filename, f->count);
                f = f->next;
            }
            fprintf(fp, "\n");
            w = w->next;
        }
    }
    fclose(fp);
    printf("Database saved!\n");
}
