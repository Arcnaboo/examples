/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at the  *
 * root level of an installed copy of the electronic HDF5 document set and   *
 * is linked from the top-level documents page.  It can also be found at     *
 * http://hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have          *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 *  This example writes data to the HDF5 file.
 *  Data conversion is performed during write operation.
 */

#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"
#include "shared.h"

#define H5FILE_NAME        "SDS.h5"
#define RANK   2

struct csv_data* gen_data(void) {
	int x, y;
	unsigned int rows = rand() % 10 + 2;
	unsigned int columns = rand() % 10 + 2;

	struct csv_data* cd = alloc_csv_data(rows,columns);

	for (y = 0; y < rows; y++) {
		for (x = 0; x < columns; x++) {
			cd->data[y][x] = rand() % 100;
		}
	}
	return cd;
}

void write_rand_dataset(hid_t file) {
	hid_t       datatype, dataspace, dataset;   /* handles */
	hsize_t     dimsf[2];              /* dataset dimensions */
	herr_t      status;
	int i;

	char ds_name[5];
	for (i = 0; i < 4; i++) {
		ds_name[i] = (rand() % ('A' - 'Z')) + 'A';
	}

	struct csv_data *cd = gen_data();
	printf("%s (%d X %d):\n", ds_name, cd->rows, cd->columns);
	print_csv_data(cd);

	/*
	 * Describe the size of the array and create the data space for fixed
	 * size dataset.
	 */
	dimsf[0] = cd->rows;
	dimsf[1] = cd->columns;
	dataspace = H5Screate_simple(2, dimsf, NULL);

	/*
	 * Define datatype for the data in the file.
	 * We will store little endian INT numbers.
	 */
	datatype = H5Tcopy(H5T_NATIVE_INT);
	status = H5Tset_order(datatype, H5T_ORDER_LE);


	/*
	 * Create a new dataset within the file using defined dataspace and
	 * datatype and default dataset creation properties.
	 */
	dataset = H5Dcreate2(file, ds_name, datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	/*
	 * Write the data to the dataset using default transfer properties.
	 */
	status = H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, cd->data[0]);
	if (status < 0) {
		err(EACCES, "Unable to write to \"%s\"", H5FILE_NAME);
	}

	free_csv_data(cd);
	H5Sclose(dataspace);
	H5Tclose(datatype);
	H5Dclose(dataset);
}

int main(int argc, const char* argv[]){
	hid_t       file;
	int         i;

	if (argc > 1) {
		int seed = strtol(argv[1], NULL, 0);
		srand(seed);
	}

	file = H5Fcreate(H5FILE_NAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

	for (i = 0; i < 3; i++) {
		write_rand_dataset(file);
	}
	H5Fclose(file);

	return 0;
}
