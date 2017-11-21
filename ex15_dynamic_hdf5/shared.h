
#ifndef SHARED_H
#define SHARED_H

struct csv_data {
	int rows;
	int columns;
	int** data;
};

extern struct csv_data* alloc_csv_data(int x, int y);
extern void free_csv_data(struct csv_data* cd);
extern void print_csv_data(struct csv_data* cd);

#endif
