#include <stdlib.h>

#include "blockchain.h"

/**
 * _blockchain_destroy - Deallocates a Blockchain structure
 *
 * @blockchain: Pointer to the Blockchain structure to be freed
 */
void _blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;

	llist_destroy(blockchain->chain, 1, (node_dtor_t)free);

	free(blockchain);
}
