#include <stdio.h>
#include <string.h>

#include "blockchain.h"

void _print_hex_buffer(uint8_t const *buf, size_t len);
int _transaction_print_loop(transaction_t const *transaction,
	unsigned int idx, char const *indent);
int _transaction_print_brief_loop(transaction_t const *transaction,
	unsigned int idx, char const *indent);

/**
 * _block_print - Prints information about a Block
 *
 * @block:  Pointer to the Block to be printed
 * @index:  Index of the Block in the Blockchain
 * @indent: Lines prefix
 *
 * Return: FOREACH_CONTINUE
 */
static int _block_print(block_t const *block, unsigned int index,
	char const *indent)
{
	char indent2[10] = {0};

	if (!block)
	{
		printf("%snil\n", indent);
		return (0);
	}

	printf("%sBlock: {\n", indent);

	printf("%s\tinfo: {\n", indent);
	printf("%s\t\tindex: %u,\n", indent, block->info.index);
	printf("%s\t\tdifficulty: %u,\n", indent, block->info.difficulty);
	printf("%s\t\ttimestamp: %lu,\n", indent, block->info.timestamp);
	printf("%s\t\tnonce: %lu,\n", indent, block->info.nonce);
	printf("%s\t\tprev_hash: ", indent);
	_print_hex_buffer(block->info.prev_hash, SHA256_DIGEST_LENGTH);
	printf("\n%s\t},\n", indent);

	printf("%s\tdata: {\n", indent);
	printf("%s\t\tbuffer: \"%s\",\n", indent, block->data.buffer);
	printf("%s\t\tlen: %u\n", indent, block->data.len);
	printf("%s\t},\n", indent);

	printf("%s\ttransactions [%d]: [\n", indent,
		llist_size(block->transactions));
	memcpy(indent2, indent, strlen(indent));
	memcpy(indent2 + strlen(indent), "\t\t", 2);
	llist_for_each(block->transactions,
		(node_func_t)_transaction_print_loop, (void *)indent2);
	printf("%s\t]\n", indent);

	printf("%s\thash: ", indent);
	_print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);

	printf("\n%s}\n", indent);

	(void)index;
	return (0);
}

/**
 * _block_print_brief - Prints information about a Block (brief mode)
 *
 * @block:  Pointer to the Block to be printed
 * @index:  Index of the Block in the Blockchain
 * @indent: Lines prefix
 *
 * Return: FOREACH_CONTINUE
 */
static int _block_print_brief(block_t const *block, unsigned int index,
	char const *indent)
{
	char indent2[10] = {0};

	if (!block)
	{
		printf("%snil\n", indent);
		return (0);
	}

	printf("%sBlock: {\n", indent);

	printf("%s\tinfo: { ", indent);
	printf("%u, ", block->info.index);
	printf("%u, ", block->info.difficulty);
	printf("%lu, ", block->info.timestamp);
	printf("%lu, ", block->info.nonce);
	_print_hex_buffer(block->info.prev_hash, SHA256_DIGEST_LENGTH);
	printf(" },\n");

	printf("%s\tdata: { ", indent);
	printf("\"%s\", ", block->data.buffer);
	printf("%u", block->data.len);
	printf(" },\n");

	printf("%s\ttransactions [%d]: [\n", indent,
		llist_size(block->transactions));
	memcpy(indent2, indent, strlen(indent));
	memcpy(indent2 + strlen(indent), "\t\t", 2);
	llist_for_each(block->transactions,
		(node_func_t)_transaction_print_brief_loop, (void *)indent2);
	printf("%s\t]\n", indent);

	printf("%s\thash: ", indent);
	_print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);

	printf("\n%s}\n", indent);

	(void)index;
	return (0);
}

/**
 * _blockchain_print - Prints an entire Blockchain
 *
 * @blockchain: Pointer to the Blockchain to be printed
 */
void _blockchain_print(blockchain_t const *blockchain)
{
	printf("Blockchain: {\n");

	printf("\tchain [%d]: [\n", llist_size(blockchain->chain));
	llist_for_each(blockchain->chain,
		(node_func_t)_block_print, "\t\t");
	printf("\t]\n");

	printf("}\n");
	fflush(NULL);
}

/**
 * _blockchain_print_brief - Prints an entire Blockchain (brief mode)
 *
 * @blockchain: Pointer to the Blockchain to be printed
 */
void _blockchain_print_brief(blockchain_t const *blockchain)
{
	printf("Blockchain: {\n");

	printf("\tchain [%d]: [\n", llist_size(blockchain->chain));
	llist_for_each(blockchain->chain,
		(node_func_t)_block_print_brief, "\t\t");
	printf("\t]\n");

	printf("}\n");
	fflush(NULL);
}
