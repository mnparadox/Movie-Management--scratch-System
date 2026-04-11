#ifndef LOGIC_H
#define LOGIC_H

// 1. Định nghĩa cấu trúc dữ liệu
typedef struct Movie
{
    char *title;
    char *category;
    float rating;
    int year;
    struct Movie *next;
} Movie;

void push_movie(Movie **head, char *new_title, char *new_category, int new_year, float new_rating);
void pop_movie(Movie **head);
void update_movie(Movie *head, char *name_to_fix);
void delete_movie(Movie **head, char *name_to_delete);
void search_by_category(Movie *head, char *choosen_category);
void sort_by_rating(Movie *head);
void display_all(Movie *head);
void free_all(Movie *head);
void save_to_file(Movie *head, const char *filename);
Movie *load_from_file(const char *filename);

#endif