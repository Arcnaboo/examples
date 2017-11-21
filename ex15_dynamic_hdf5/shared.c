#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"


static int** alloc_array(int rows, int columns) {
	// Need enough room for x pointers and x*y values
	size_t size = rows * sizeof(int*) + columns * rows * sizeof(int);
	int** a = malloc(size);
	memset(a, 0, size);

	int* data = (int*) &a[rows];
	int i;
	for (i = 0; i < rows; i++) {
		a[i] = &data[i * columns];
	}
	return a;
}

struct csv_data* alloc_csv_data(int rows, int columns) {
	struct csv_data *cd = malloc(sizeof(*cd));
	cd->rows = rows;
	cd->columns = columns;
	cd->data = alloc_array(rows, columns);
	return cd;
}

void free_csv_data(struct csv_data *cd) {
	free(cd->data);
	free(cd);
}

void print_csv_data(struct csv_data* cd) {
	int x = 0, y = 0;
	for (y = 0; y < cd->rows; y++) {
		for (x = 0; x < cd->columns; x++) {
			printf("%4d", cd->data[y][x]);
		}
		printf("\n");
	}
}
