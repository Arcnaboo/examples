/**
 *
 * Title: ex16_memcached/main.c, Memcached Example
 *
 * Description: This example shows how memcached can be used.
 *				A value is set and retrieved from memcached.
 *
 * Reference: https://memcached.org/
 *			  
 *
 * Modified by: MD & VS
 *
 * Date: 20/7/2016
 */

#include <libmemcached/memcached.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	
	//memcached_servers_parse (char *server_strings);
  	memcached_server_st *servers = NULL;
  	memcached_st *memc;
  	memcached_return rc;
  	char *key = "keystring";
  	char *value = "keyvalue";

  	char *retrieved_value;
  	size_t value_length;
  	uint32_t flags;

  	memc = memcached_create(NULL);
	servers = memcached_server_list_append(servers, "localhost", 11211, &rc);

	// Connect to memcached server
	rc = memcached_server_push(memc, servers);

	if (rc == MEMCACHED_SUCCESS) {
		printf("Added server successfully\n");
	} else {
		printf("ERROR Couldn't add server: %s\n", memcached_strerror(memc, rc));
	}
	  
	//Set a key value in memcached
	rc = memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);

	if (rc == MEMCACHED_SUCCESS) {
		printf("Key stored successfully\n");
	} else {
		printf("Couldn't store key: %s\n", memcached_strerror(memc, rc));
	}

	// Get a key value from memcached
	retrieved_value = memcached_get(memc, key, strlen(key), &value_length, &flags, &rc);
	
	if (rc == MEMCACHED_SUCCESS) {
		printf("Key retrieved successfully\n");
		printf("The key '%s' returned value '%s'.\n", key, retrieved_value);
	
	} else {
		printf("Couldn't retrieve key: %s\n", memcached_strerror(memc, rc));
	}//*/

  	return 0;
}
