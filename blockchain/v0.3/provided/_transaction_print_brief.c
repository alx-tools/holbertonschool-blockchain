#include <stdlib.h>
#include <stdio.h>

#include "transaction.h"

void _print_hex_buffer(uint8_t const *buf, size_t len);

int _transaction_print_brief_loop(transaction_t const *transaction,
	unsigned int idx, char const *indent)
{
	tx_out_t const *out;

	if (!transaction)
		return (0);

	out = llist_get_head(transaction->outputs);

	printf("%sTransaction: {\n", indent);

	printf("%s\tamount: %u from %d inputs,\n", indent, out->amount,
		llist_size(transaction->inputs));
	printf("%s\treceiver: ", indent);
	_print_hex_buffer(out->pub, EC_PUB_LEN);
	printf("\n");
	printf("%s\tid: ", indent);
	_print_hex_buffer(transaction->id, sizeof(transaction->id));
	printf("\n");

	printf("%s}\n", indent);

	(void)idx;
	return (0);
}

/**
 * _transaction_print_brief - Prints the content of a transaction structure
 *
 * @transaction: Pointer to the transaction structure to be printed
 */
void _transaction_print_brief(transaction_t const *transaction)
{
	tx_out_t const *out;

	if (!transaction)
		return;

	out = llist_get_head(transaction->outputs);

	printf("Transaction: {\n");

	printf("\tamount: %u from %d inputs,\n", out->amount,
		llist_size(transaction->inputs));
	printf("\treceiver: ");
	_print_hex_buffer(out->pub, EC_PUB_LEN);
	printf("\n");
	printf("\tid: ");
	_print_hex_buffer(transaction->id, sizeof(transaction->id));
	printf("\n");

	printf("}\n");
}
