#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hash.h"
#include "bitmap.h"

/* list data structure */
struct list_data {
	struct list_elem elem;
	int data;
};
/* hash data structure */
struct hash_data {
	struct hash_elem elem;
	int data;
};

char *list_name[10];
char *hash_name[10];
char *bitmap_name[10];

/* array of list, hash, bitmap table */
struct list *list_arr[10];
struct hash *hash_arr[10];
struct bitmap *bitmap_arr[10];

/* global variables of number of list, hash, bitmap */
int cnt_list = 0;
int cnt_hash = 0;
int cnt_bitmap = 0;

/* functions declare */
void create_func(char *input);
void create_list(char *name);
void create_hash(char *name);
void create_bitmap(char *name, size_t cnt);
int quit_func(char *input);
bool delete_func(char *name);
void dumpdata(char *name);
void display_list(struct list *l);
void display_hash(struct hash *h);
void display_bitmap(struct bitmap *b);

int find_index(char *name);
void command(char *input);

/* list function */
struct list_elem *value_find(struct list *l, int data);
struct list_elem *order_find(struct list *l, int data);

/* hash function */
unsigned hash_normal(const struct hash_elem *h, void *aux);
unsigned hash_square(const struct hash_elem *h, void *aux);
unsigned hash_cube(const struct hash_elem *h, void *aux);

/* value compare function*/
static bool value_compare_list(const struct list_elem *a, const struct list_elem *b, void *aux);
static bool value_compare_hash(const struct hash_elem *a, const struct hash_elem *b, void *aux);

void hash_action_square(struct hash_elem *h, void *aux);
void hash_action_cube(struct hash_elem *h, void *aux);
