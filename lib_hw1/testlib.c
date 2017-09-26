#include "testlib.h"

int main(void) {
	char input[100];
	int i, j;
	
	for(i = 0 ; i < 10 ; i++) {
 		list_name[i] = (char *)malloc(sizeof(char) * 30);
		hash_name[i] = (char *)malloc(sizeof(char) * 30);
		bitmap_name[i] = (char *)malloc(sizeof(char) * 30);		
	}

	while(1) {
		memset(input, 0, sizeof(input));
		fflush(stdin);
		fscanf(stdin, "%[^\n]s", input);
		getchar();
		if(strlen(input) == 0) continue;

		// quit command
		if(strcmp(input, "quit") == 0) {
			break;
		}
		// create command
		else if(strncmp(input, "create", 6) == 0) {
			create_func(input);
		}
		// delete command
		else if(strncmp(input, "delete", 6) == 0) {
			strtok(input, " ");
			char *ds = (char *)malloc(sizeof(char) * 30);
			strcpy(ds, strtok(NULL, " "));
			delete_func(ds);
		}
		// dumpdata command
		else if(strncmp(input, "dumpdata", 8) == 0) {
			strtok(input, " ");
			char *name = (char *)malloc(sizeof(char) * 30);
			strcpy(name, strtok(NULL, " "));
			dumpdata(name);
		}
		// command
		else {
			command(input);
		}
	}// while
}// main

void create_func(char *input) {
	strtok(input, " ");
	
	char *ds = strtok(NULL, " ");	// data structure type
	
	char *name = strtok(NULL, " "); // data structure name
	
	if(strcmp(ds, "list") == 0) {
		create_list(name);
	}
	else if(strcmp(ds, "hashtable") == 0) {
		create_hash(name);
	}
	else if(strcmp(ds, "bitmap") == 0) {
		char *temp = strtok(NULL, " ");
		size_t t;
		sscanf(temp, "%d", &t);
		create_bitmap(name, t);
	}
}// create_func

void create_list(char *name) {
	strcpy(list_name[cnt_list], name);
	struct list *newlist =(struct list *)malloc(sizeof(struct list));
	list_arr[cnt_list] = newlist;
	list_init(list_arr[cnt_list]);
	cnt_list++;
}// create_list

void create_hash(char *name) {
	strcpy(hash_name[cnt_hash], name);
        struct hash *newhash =(struct hash *)malloc(sizeof(struct hash));
        hash_arr[cnt_hash] = newhash;
        hash_init(hash_arr[cnt_hash], &hash_normal, &value_compare_hash, NULL);
        cnt_hash++;
}// create_hash

void create_bitmap(char *name, size_t size) {
	strcpy(bitmap_name[cnt_bitmap], name);
	struct bitmap *newbitmap = (struct bitmap *)bitmap_create(size);
	if(newbitmap != NULL)
		bitmap_arr[cnt_bitmap] = newbitmap;
	cnt_bitmap++;
}// create_bitmap

int quit_func(char *input) {
	if(strcmp("quit", input) == 0) return 1;
	return 0;
}// quit_func

bool delete_func(char *name) {
	bool ret = 1;
	int i;

	for(i = 0 ; i < cnt_list ; i++) {
		if(strcmp(name, list_name[i]) == 0) {
			memset(list_name[i], 0, sizeof(list_name[i]));

			if(cnt_list > 1 && i < cnt_list - 1) {
				strcpy(list_name[i], list_name[cnt_list - 1]);
				list_arr[i] = list_arr[cnt_list - 1];
			}
			cnt_list--;
			return true;
		}
	}
	for(i = 0 ; i < cnt_hash ; i++) {
		if(strcmp(name, hash_name[i]) == 0) {
			memset(hash_name[i], 0, sizeof(hash_name[i]));

			if(cnt_hash > 1 && i < cnt_hash - 1) {
				strcpy(hash_name[i], hash_name[cnt_hash - 1]);
				hash_arr[i] = hash_arr[cnt_hash - 1];
			}
			cnt_hash--;
			return true;
		}
	}
	for(i = 0 ; i < cnt_bitmap ; i++) {
		if(strcmp(name, bitmap_name[i]) == 0) {
			memset(bitmap_name[i], 0, sizeof(bitmap_name[i]));
		
			if(cnt_bitmap > 1 && i < cnt_bitmap - 1) {
				strcpy(bitmap_name[i], bitmap_name[cnt_bitmap - 1]);
				bitmap_arr[i] = bitmap_arr[cnt_bitmap - 1];
			}
			cnt_bitmap--;
			return true;
		}
	}
	return ret;
}// delete_func

void dumpdata(char *name) {
	int i;
	for(i = 0 ; i < cnt_list ; i++) {
		if(strcmp(name, list_name[i]) == 0) {
			display_list(list_arr[i]);
			return;
		}
	}
	for(i = 0 ; i < cnt_hash ; i++) {
		if(strcmp(name, hash_name[i]) == 0) {
			display_hash(hash_arr[i]);
			return;
		}
	}
	for(i = 0 ; i < cnt_bitmap ; i++) {
		if(strcmp(name, bitmap_name[i]) == 0) {
			display_bitmap(bitmap_arr[i]);
			return;
		}
	}
}// dumpdata

int find_index(char *name) {
	int ret = -1, i;
	
	for(i = 0 ; i < cnt_list ; i++) {
		if(strcmp(name, list_name[i]) == 0)
			return i;
	}
	for(i = 0 ; i < cnt_hash ; i++) {
		if(strcmp(name, hash_name[i]) == 0)
			return i;
	}
	for(i = 0 ; i < cnt_bitmap ; i++) {
		if(strcmp(name, bitmap_name[i]) == 0)
			return i;
	}
	return ret;
}// find_index

void display_list(struct list *l) {
	
	if(list_empty(l)) {
		return ;
	}
	
	struct list_elem *temp;
	struct list_data *dat;

	for(temp = list_begin(l) ; temp != list_end(l) ; temp = list_next(temp)) {
		dat = list_entry(temp, struct list_data, elem);
		printf("%d ", dat->data);
	}
	printf("\n");
}// display_list

void display_hash(struct hash *h) {

	if(hash_empty(h)) {
		return ;
	}

	struct hash_iterator temp;
	hash_first(&temp, h);
	while(hash_next(&temp)) {
		struct hash_data *dat_data;

		dat_data = hash_entry(hash_cur(&temp), struct hash_data, elem);

		printf("%d ", dat_data->data);
	}
	printf("\n");
}// display_hash

void display_bitmap(struct bitmap *b) {
	size_t t = bitmap_size(b);
	size_t i;

	for(i = 0 ; i < t ; i++) {
		if(bitmap_test(b, i))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}// display_bitmap

struct list_elem *value_find(struct list *l, int data) {
	int size = list_size(l);
	struct list_elem *temp_elem;
	struct list_data *temp_data;

	for(temp_elem = list_begin(l) ; temp_elem != list_end(l) ; temp_elem = list_next(temp_elem)) {
		temp_data = list_entry(temp_elem, struct list_data, elem);
		if(temp_data->data == data) {
			return temp_elem;
		}
	}
	printf("Error : There is no data in list\n");
}// value_find

struct list_elem *order_find(struct list *l, int data) {
	struct list_elem *temp_elem;
	int size = list_size(l), i;
	
	temp_elem = list_begin(l);
	for(i = 0 ; i < data ; i++) {
		if(temp_elem == list_end(l)) {
			printf("list_end\n");
			break;
		}
		else {
			temp_elem = list_next(temp_elem);
		}
	}// for
	return temp_elem;
}//order_find

unsigned hash_normal(const struct hash_elem *h, void *aux) {
	struct hash_data *temp_data = hash_entry(h, struct hash_data, elem);
	unsigned int temp = temp_data->data;
	return hash_int(temp);
}
unsigned hash_square(const struct hash_elem *h, void *aux) {
	struct hash_data *temp_data = hash_entry(h, struct hash_data, elem);
	unsigned int temp = temp_data->data;
	return hash_int_2(temp * temp);
}
unsigned hash_cube(const struct hash_elem *h, void *aux) {
	struct hash_data *temp_data = hash_entry(h, struct hash_data, elem);
        unsigned int temp = temp_data->data;
        return hash_int_2(temp * temp * temp);
}

static bool value_compare_list(const struct list_elem *a, const struct list_elem *b, void *aux) {
	struct list_data *l1 = list_entry(a, struct list_data, elem);
	struct list_data *l2 = list_entry(b, struct list_data, elem);
	return (l1->data) < (l2->data);
}
static bool value_compare_hash(const struct hash_elem *a, const struct hash_elem *b, void *aux) {
	struct hash_data *h1 = hash_entry(a, struct hash_data, elem);
	struct hash_data *h2 = hash_entry(b, struct hash_data, elem);
	return (h1->data) < (h2->data);
}

void hash_action_square(struct hash_elem *h, void *aux) {
	struct hash_data *hd = hash_entry(h, struct hash_data, elem);
	hd->data = hd->data * hd->data;
}
void hash_action_cube(struct hash_elem *h, void *aux) {
	struct hash_data *hd = hash_entry(h, struct hash_data, elem);
	hd->data = hd->data * hd->data * hd->data;
}

// command function
void command(char *input) {
	char *cmd = (char *)malloc(sizeof(char) * 20);		//command
	char *ds = (char *)malloc(sizeof(char) * 20);		//data structure
	char *arg = (char *)malloc(sizeof(char) * 20);	//argument
	char *temp = strtok(input, " ");

	if(temp != NULL)
		strcpy(cmd, temp);
	temp = strtok(NULL, " ");
	if(temp != NULL)
		strcpy(ds, temp);
	temp = strtok(NULL, "");
	if(temp != NULL)
		strcpy(arg, temp);

/***************************
 *
 *       list command 
 *
 ***************************    
 */
	if(strcmp(cmd, "list_insert") == 0) {
		
		int arg1, arg2, i;
		sscanf(arg, "%d %d", &arg1, &arg2);

		struct list_data *newlist = (struct list_data *)malloc(sizeof(struct list_data));
		newlist->data = arg2;

		// search the list
		int idx = find_index(ds);
		if(idx == -1) {
			printf("There is no list\n");
			return ;
		}

		struct list *temp_list = list_arr[idx];
		struct list_elem *temp_elem = list_head(temp_list);

		for(i = 0 ; i <= arg1 ; i++) {
			temp_elem = list_next(temp_elem);
		}

		list_insert(temp_elem, &(newlist->elem));
	
	}// list_insert
	else if(strcmp(cmd, "list_splice") == 0) {
		
		int idx1 = find_index(ds), des_idx = 0;
		char src[20] = {0, };
		int first, last;
		sscanf(arg, "%d %s %d %d", &des_idx, src, &first, &last);
		
		int idx2 = find_index(src);
		struct list_elem *before_elem = order_find(list_arr[idx1], des_idx);
		struct list_elem *first_elem = order_find(list_arr[idx2], first);
		struct list_elem *last_elem = order_find(list_arr[idx2], last);

		list_splice(before_elem, first_elem, last_elem);
	
	}// list_splice
	else if(strcmp(cmd, "list_push_front") == 0) {
		
		int arg1 = 0;
		sscanf(arg, "%d", &arg1);
		struct list_data *newlist = (struct list_data *)malloc(sizeof(struct list_data));
		newlist->data = arg1;

		int idx = find_index(ds);

		list_push_front(list_arr[idx], &(newlist->elem));
	
	}// list_push_front
	else if(strcmp(cmd, "list_push_back") == 0) {
		
		int arg1 = 0;
		sscanf(arg, "%d", &arg1);
		struct list_data *newlist = (struct list_data *)malloc(sizeof(struct list_data));
		newlist->data = arg1;

		int idx = find_index(ds);

		list_push_back(list_arr[idx], &(newlist->elem));
	
	}// list_push_back
	else if(strcmp(cmd, "list_remove") == 0) {
		
		int idx = find_index(ds);
		int temp_idx = 0;
		sscanf(arg, "%d", &temp_idx);
		struct list_elem *remove_elem = order_find(list_arr[idx], temp_idx);
		
		list_remove(remove_elem);
	
	}// list_remove
	else if(strcmp(cmd, "list_pop_front") == 0) {

		int idx = find_index(ds);
		struct list_elem *temp_elem = list_pop_front(list_arr[idx]);
		if(temp_elem == NULL) {
			printf("list_pop_front's return value is NULL\n");
		}
	
	}// list_pop_front
	else if(strcmp(cmd, "list_pop_back") == 0) {

		int idx = find_index(ds);
		struct list_elem *temp_elem = list_pop_back(list_arr[idx]);
		if(temp_elem == NULL) {
			printf("list_pop_back's return value is NULL\n");
		}
	
	}// list_pop_back
	else if(strcmp(cmd, "list_front") == 0) {

		int idx = find_index(ds);
		struct list_elem *temp_elem = list_front(list_arr[idx]);
		struct list_data *temp_data;

		if(temp_elem == NULL) {
			printf("front return is NULL\n");
		}
		else {
			temp_data = list_entry(temp_elem, struct list_data, elem);
			printf("%d\n", temp_data->data);
		}
	
	}// list_front
	else if(strcmp(cmd, "list_back") == 0) {
		
		int idx = find_index(ds);
		struct list_elem *temp_elem = list_back(list_arr[idx]);
		struct list_data *temp_data;
		if(temp_elem == NULL) {
			printf("rear return is NULL\n");
		}
		else {
			temp_data = list_entry(temp_elem, struct list_data, elem);
			printf("%d\n", temp_data->data);
		}
	
	}// list_back
	else if(strcmp(cmd, "list_size") == 0) {
		
		int idx = find_index(ds);
		printf("%d\n", list_size(list_arr[idx]));
       
	}// list_size
	else if(strcmp(cmd, "list_empty") == 0) {

		int idx = find_index(ds);
		bool temp = list_empty(list_arr[idx]);
		if(temp == 1) {
			printf("true\n");
		}
		else {
			printf("false\n");
		}

	}// list_empty
	else if(strcmp(cmd, "list_reverse") == 0) {

		int idx = find_index(ds);

		list_reverse(list_arr[idx]);

	}// list_reverse
	else if(strcmp(cmd, "list_sort") == 0) {

		int idx = find_index(ds);

		list_sort(list_arr[idx], value_compare_list,NULL);

	}// list_sort
	else if(strcmp(cmd, "list_insert_ordered") == 0) {

		int idx = find_index(ds);
		int data = 0;
		sscanf(arg, "%d", &data);
		struct list_data *newlist = (struct list_data *)malloc(sizeof(struct list_data));
		newlist->data = data;

		list_insert_ordered(list_arr[idx], &(newlist->elem), value_compare_list, NULL);

	}// list_insert_ordered
	else if(strcmp(cmd, "list_unique") == 0) {

		int idx = find_index(ds);
		char *temp = (char *)malloc(sizeof(char) * 20);
		if(strlen(arg) > 0) {
			sscanf(arg, "%s", temp);
			int idx2 = find_index(temp);
			list_unique(list_arr[idx], list_arr[idx2], value_compare_list, NULL);
		}
		else {
			list_unique(list_arr[idx], NULL, value_compare_list, NULL);
		}

	}// list_unique
	else if(strcmp(cmd, "list_max") == 0) {

		int idx = find_index(ds);
		struct list_elem *max_elem = list_max(list_arr[idx], value_compare_list, NULL);
		struct list_data *temp_data = list_entry(max_elem, struct list_data, elem);
		printf("%d\n", temp_data->data);
		
	}// list_max
	else if(strcmp(cmd, "list_min") == 0) {

		int idx = find_index(ds);
                struct list_elem *min_elem = list_min(list_arr[idx], value_compare_list, NULL);
                struct list_data *temp_data = list_entry(min_elem, struct list_data, elem);
                printf("%d\n", temp_data->data);

	}// list_min
	else if(strcmp(cmd, "list_swap") == 0) {

		int idx = find_index(ds), idx1, idx2;

		sscanf(arg, "%d %d", &idx1, &idx2);

		if(idx2 < idx1) {
			int temp = idx2;
			idx2 = idx1;
			idx1 = temp;
		}
		struct list_elem *a, *b;
		a = order_find(list_arr[idx], idx1);
		b = order_find(list_arr[idx], idx2);

		list_swap(a, b);

        }// list_swap
	else if(strcmp(cmd, "list_shuffle") == 0) {

		int idx = find_index(ds);

		list_shuffle(list_arr[idx]);

	}// list_shuffle
/***************************
 *
 *	 hash command 
 *
 ***************************	
 */
	else if(strcmp(cmd, "hash_insert") == 0) {

		int idx = find_index(ds);
		int data = 0;
		sscanf(arg, "%d", &data);
		struct hash_data *newhash = (struct hash_data *)malloc(sizeof(struct hash_data));
		newhash->data = data;

		hash_insert(hash_arr[idx], &(newhash->elem));

	}// hash_insert
	else if(strcmp(cmd, "hash_replace") == 0) {

		int idx = find_index(ds);
		int data = 0;
		sscanf(arg, "%d", &data);
		struct hash_data *newhash = (struct hash_data *)malloc(sizeof(struct hash_data));
		newhash->data = data;

		hash_replace(hash_arr[idx], &(newhash->elem));

	}// hash_replace
	else if(strcmp(cmd, "hash_find") == 0) {

		int idx = find_index(ds);
		int data = 0;
		sscanf(arg, "%d", &data); 
		struct hash_data *newhash = (struct hash_data *)malloc(sizeof(struct hash_data));
		newhash->data = data;

		struct hash_elem *temp_elem = NULL;
		temp_elem = hash_find(hash_arr[idx], &(newhash->elem));

		if(temp_elem) {
			printf("%d\n", data);
		}

	}// hash_find
	else if(strcmp(cmd, "hash_delete") == 0) {

		int idx = find_index(ds);
		int data = 0;
		sscanf(arg, "%d", &data); 
		struct hash_data *newhash = (struct hash_data *)malloc(sizeof(struct hash_data));
		newhash->data = data;

		hash_delete(hash_arr[idx], &(newhash->elem));

	}// hash_delete
	else if(strcmp(cmd, "hash_clear") == 0) {

	int idx = find_index(ds);

	hash_clear(hash_arr[idx], NULL);

	}// hash_clear
	else if(strcmp(cmd, "hash_size") == 0) {

		int idx = find_index(ds);

		printf("%d\n", hash_size(hash_arr[idx]));

	}// hash_size
	else if(strcmp(cmd, "hash_empty") == 0) {

		int idx = find_index(ds);

		if(hash_empty(hash_arr[idx])) {
			printf("true\n");
		}
		else {
			printf("false\n");
		}

	}// hash_empty
	else if(strcmp(cmd, "hash_apply") == 0) {

		int idx = find_index(ds);
		if(strcmp(arg, "square") == 0) {
			hash_apply(hash_arr[idx], &hash_action_square);
		}
		else if(strcmp(arg, "triple") == 0) {
			hash_apply(hash_arr[idx], &hash_action_cube);
		}
		else {
			printf("Error - hash_apply\n");
		}

	}// hash_apply



}
 





























