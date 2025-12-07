#include "inverted_index.h"
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./a.out <filename>\n");
        return 0;
    }
    if (insert_file(argv[1]) == 0)
        printf("File added: %s\n", argv[1]);
    else
    {
        printf("File does not exist!\n");
        return 0;
    }
    int ch;
    char c;
    do
    {
        printf("\n----- MENU -----\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Update Database\n");
        printf("4. Search Word\n");
        printf("5. Save Database\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1: create_database(); 
            break;
            case 2: display_database(); 
            break;
            case 3: update_database(); 
            break;
            case 4: search_word(); 
            break;
            case 5: save_database();
            break;
            default: printf("Invalid choice!\n");
        }
        printf("\nContinue? (y/n): ");
        scanf(" %c", &c);
    } 
    while (c == 'y' || c == 'Y');
    return 0;
}
