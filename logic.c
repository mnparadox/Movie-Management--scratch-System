#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"

void push_movie(Movie **head, char *new_title, char *new_category, int new_year, float new_rating)
{
    Movie *new_node = (Movie *)malloc(sizeof(Movie));
    if (!new_node)
        return;

    new_node->title = strdup(new_title);
    new_node->category = strdup(new_category);
    new_node->year = new_year;
    new_node->rating = new_rating;

    new_node->next = *head;
    *head = new_node;
    printf("[*] Pushed: %s to stack.\n", new_title);
}

void pop_movie(Movie **head)
{
    if (*head == NULL)
    {
        printf("[!] Empty Stack! No film to pop.\n");
        return;
    }

    Movie *temp = *head;
    *head = (*head)->next;

    printf("[*] Popped movie: %s (Deleted from the list)\n", temp->title);

    free(temp->title);
    free(temp->category);
    free(temp);
}

void update_movie(Movie *head, char *name_to_fix)
{
    Movie *temp = head;
    while (temp != NULL && strcmp(temp->title, name_to_fix) != 0)
    {
        temp = temp->next;
    }

    if (temp != NULL)
    {
        char buffer[100];
        printf("Movie found! Enter new category: ");
        scanf(" %[^\n]", buffer);
        free(temp->category);
        temp->category = strdup(buffer);

        printf("Enter new rating: ");
        scanf("%f", &temp->rating);
        printf("Enter new year: ");
        scanf("%d", &temp->year);
        printf("[*] Updated successfully!\n");
    }
    else
    {
        printf("[!] Cannot find movie: %s\n", name_to_fix);
    }
}

void delete_movie(Movie **head, char *name_to_delete)
{
    Movie *temp = *head, *prev = NULL;
    while (temp != NULL && strcmp(temp->title, name_to_delete) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL)
    {
        if (prev == NULL)
            *head = temp->next;
        else
            prev->next = temp->next;

        free(temp->title);
        free(temp->category);
        free(temp);
        printf("[*] Deleted successfully!\n");
    }
    else
    {
        printf("[!] Movie not found!\n");
    }
}

void search_by_category(Movie *head, char *choosen_category)
{
    Movie *temp = head;
    int found = 0;
    while (temp != NULL)
    {
        if (strcmp(temp->category, choosen_category) == 0)
        {
            printf("\nTitle: %s | Rating: %.1f | Year: %d", temp->title, temp->rating, temp->year);
            found++;
        }
        temp = temp->next;
    }
    if (found == 0)
        printf("\nNo movies found in category: %s", choosen_category);
}

void sort_by_rating(Movie *head)
{
    if (head == NULL)
        return;
    for (Movie *i = head; i->next != NULL; i = i->next)
    {
        for (Movie *j = i->next; j != NULL; j = j->next)
        {
            if (j->rating > i->rating)
            {
                // Hoán đổi Rating & Year
                float temp_r = i->rating;
                i->rating = j->rating;
                j->rating = temp_r;
                int temp_y = i->year;
                i->year = j->year;
                j->year = temp_y;

                char *temp_t = i->title;
                i->title = j->title;
                j->title = temp_t;
                char *temp_c = i->category;
                i->category = j->category;
                j->category = temp_c;
            }
        }
    }
    printf("\n[*] Sorted by rating successfully!\n");
}

void display_all(Movie *head)
{
    if (!head)
    {
        printf("\nLibrary is empty!\n");
        return;
    }
    Movie *temp = head;
    while (temp != NULL)
    {
        printf("\n[%-20s] | Cat: %-10s | Rating: %.1f | Year: %d", temp->title, temp->category, temp->rating, temp->year);
        temp = temp->next;
    }
}

void save_to_file(Movie *head, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        return;
    Movie *temp = head;
    while (temp != NULL)
    {
        fprintf(f, "%s|%s|%.1f|%d\n", temp->title, temp->category, temp->rating, temp->year);
        temp = temp->next;
    }
    fclose(f);
    printf("\n[*] Data saved to %s\n", filename);
}

Movie *load_from_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return NULL;
    Movie *head = NULL;
    char line[512];
    while (fgets(line, sizeof(line), f))
    {
        char t[100], c[100];
        float r;
        int y;

        line[strcspn(line, "\r\n")] = 0;
        if (sscanf(line, "%[^|]|%[^|]|%f|%d", t, c, &r, &y) == 4)
        {
            push_movie(&head, t, c, y, r);
        }
    }
    fclose(f);
    return head;
}

void free_all(Movie *head)
{
    while (head != NULL)
    {
        Movie *next = head->next;
        free(head->title);
        free(head->category);
        free(head);
        head = next;
    }
}