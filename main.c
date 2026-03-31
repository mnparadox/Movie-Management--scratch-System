#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"

void print_divider() { printf("\n==========================================================\n"); }
void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    Movie *my_list = NULL;
    int choice;
    char filename[] = "text.txt";

    // Truyền biến 'filename'
    my_list = load_from_file(filename);

    do
    {
        print_divider();
        printf("          🎬 MOVIE MANAGEMENT SYSTEM v1.0 🎬          ");
        print_divider();
        printf("  [1] Add Movie  [2] Display All  [3] Update  [4] Delete\n");
        printf("  [5] Search     [6] Sort Rating  [8] Save    [0] Exit\n");
        print_divider();
        printf("  Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[!] Invalid input!\n");
            clear_buffer();
            continue;
        }
        clear_buffer();

        switch (choice)
        {
        case 1:
        {
            char t[100], c[100];
            float r;
            int y;
            printf("Title: ");
            scanf(" %[^\n]", t);
            printf("Category: ");
            scanf(" %[^\n]", c);
            printf("Year: ");
            scanf("%d", &y);
            printf("Rating: ");
            scanf("%f", &r);
            add_movie(&my_list, t, c, y, r);
            break;
        }
        case 2:
            display_all(my_list);
            break;
        case 3:
        {
            char t[100];
            printf("Title to update: ");
            scanf(" %[^\n]", t);
            update_movie(my_list, t);
            break;
        }
        case 4:
        {
            char t[100];
            printf("Title to delete: ");
            scanf(" %[^\n]", t);
            delete_movie(&my_list, t);
            break;
        }
        case 5:
        {
            char cat[100];
            printf("Category: ");
            scanf(" %[^\n]", cat);
            search_by_category(my_list, cat);
            break;
        }
        case 6:
            sort_by_rating(my_list);
            display_all(my_list);
            break;
        case 8:
            save_to_file(my_list, filename);
            break;
        case 0:
            save_to_file(my_list, filename);
            free_all(my_list);
            printf("\nGoodbye!\n");
            break;
        default:
            printf("\n[!] Invalid choice.");
            break;
        }
        if (choice != 0)
        {
            printf("\nPress Enter...");
            getchar();
        }
    } while (choice != 0);

    return 0;
}