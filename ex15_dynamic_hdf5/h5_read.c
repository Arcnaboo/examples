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
 *   This example reads hyperslab from the SDS.h5 file
 *   created by h5_write.c program into two-dimensional
 *   plane of the three-dimensional array.
 *   Information about dataset in the SDS.h5 file is obtained.
 */

#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include "shared.h"
#include "hdf5.h"

#define H5FILE_NAME        "SDS.h5"
#define DATASETNAME "IntArray"
#define NX 7           /* output buffer dimensions */
#define NY 7
#define NZ  3
#define RANK         2
#define RANK_OUT     3
#define MAX_NAME 128

#define COLOUR_RED	"\x1b[31m"
#define COLOUR_GREEN	"\x1b[32m"
#define COLOUR_BLUE	"\x1b[33m"
#define COLOUR_YELLOW	"\x1b[34m"
#define COLOUR_RESET	"\x1b[0m"

#define NUM_COLOURS	4

static char* colours[NUM_COLOURS] = {
	COLOUR_RED,
	COLOUR_GREEN,
	COLOUR_BLUE,
	COLOUR_YELLOW
};

struct csv_data* read_dataset(hid_t dataset) {
	int status_n;
	//int rank;
	hid_t       dataspace;
	hsize_t     dims_out[2];           /* dataset dimensions */
	herr_t      status;

	dataspace = H5Dget_space(dataset);    /* dataspace handle */
	//rank      = H5Sget_simple_extent_ndims(dataspace);
	status_n  = H5Sget_simple_extent_dims(dataspace, dims_out, NULL);

	if (status_n < 0) {
		return NULL;
	}

	struct csv_data *cd = alloc_csv_data(dims_out[0], dims_out[1]);

	status = H5Dread(dataset, H5T_NATIVE_INT, H5S_ALL, dataspace, H5P_DEFAULT, cd->data[0]);

	if (status < 0) {
		return NULL;
	}

	return cd;
}

void scan_group(hid_t gid) {
	int i, x, y, max_rows = 0, max_columns = 0;
	ssize_t len;
	herr_t status;
	int otype;
	hid_t dsid;
	char group_name[MAX_NAME];
	char memb_name[MAX_NAME];

	/*
	 * Information about the group:
	 *  Name and attributes
	 *
	 *  Other info., not shown here: number of links, object id
	 */
	len = H5Iget_name(gid, group_name, MAX_NAME);
	if (len >= MAX_NAME) {
		err(2, "Group name too long, starting with: %s", group_name);
	}

	/*
	 *  Get all the members of the groups, one at a time.
	 */
	H5G_info_t ginfo;
	status = H5Gget_info(gid, &ginfo);
	if (status < 0) {
		err(1, "Unable to get group info");
	}

	struct csv_data** csvs = malloc(ginfo.nlinks * sizeof(struct csv_data*));

	char** ds_name = malloc(ginfo.nlinks * sizeof(char*));

	for (i = 0; i < ginfo.nlinks; i++) {
		ds_name[i] = malloc(MAX_NAME * sizeof(char));
		/*
		 *  For each object in the group, get the name and
		 *   what type of object it is.
		 */
		len = H5Gget_objname_by_idx(gid, (hsize_t)i, memb_name, (size_t)MAX_NAME );
		if (len >= MAX_NAME) {
			err(2, "Dataset name too long, starting with: %s", group_name);
		}
		otype =  H5Gget_objtype_by_idx(gid, (size_t)i );

		/*
		 * process each object according to its type
		 */
		switch(otype) {
			case H5G_DATASET:
				dsid = H5Dopen(gid,memb_name,H5P_DEFAULT);
				H5Iget_name(dsid, ds_name[i], MAX_NAME);
				csvs[i] = read_dataset(dsid);
				H5Dclose(dsid);
				if (csvs[i]->rows > max_rows) {
					max_rows = csvs[i]->rows;
				}
				if (csvs[i]->columns > max_columns) {
					max_columns = csvs[i]->columns;
				}
				break;
			default:
				break;
		}
	}

	char header[32];
	for (y = -1; y < max_rows; y++) {
		for (i = 0; i < ginfo.nlinks; i++) {
			printf("%s", colours[i % NUM_COLOURS]);
			for (x = 0; x < csvs[i]->columns; x++) {
				if (y == -1) {
					if (x == 0) {
						snprintf(header, 32, "%s (%d X %d):", ds_name[i], csvs[i]->columns, csvs[i]->rows);
						printf("%-12s", header);
					} else if (x > 2){
						printf("%4s", "");
					}
				} else {
					if (x < csvs[i]->columns && y < csvs[i]->rows) {
						printf("%4d", csvs[i]->data[y][x]);
					} else {
						printf("%4s", "-");
					}
				}
			}
		}
		printf("\n");
	}
	printf(COLOUR_RESET);

	for (i = 0; i < ginfo.nlinks; i++) {
		free(ds_name[i]);
		free_csv_data(csvs[i]);
	}
	free(ds_name);
	free(csvs);
}

int main (void)
{
	hid_t file, grp;         /* handles */

	/*
	 * Open the file and the dataset.
	 */
	file = H5Fopen(H5FILE_NAME, H5F_ACC_RDONLY, H5P_DEFAULT);

	if (file < 0) {
		printf("Unable to open " H5FILE_NAME "\n");
		return 1;
	}

	grp = H5Gopen(file,"/",H5P_DEFAULT);

	scan_group(grp);
	H5Gclose(grp);
	H5Fclose(file);

	return 0;
}
