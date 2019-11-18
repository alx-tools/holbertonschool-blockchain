#include <stdlib.h>
#include <stdio.h>

#include "transaction.h"

void _print_hex_buffer(uint8_t const *buf, size_t len);

static int _tx_in_print(tx_in_t const *in, unsigned int idx,
	char const *indent)
{
	printf("%s\t\t{\n", indent);

	printf("%s\t\t\tblock_hash: ", indent);
	_print_hex_buffer(in->block_hash, sizeof(in->block_hash));
	printf(",\n");
	printf("%s\t\t\ttx_id: ", indent);
	_print_hex_buffer(in->tx_id, sizeof(in->tx_id));
	printf(",\n");
	printf("%s\t\t\ttx_out_hash: ", indent);
	_print_hex_buffer(in->tx_out_hash, sizeof(in->tx_out_hash));
	printf(",\n");
	printf("%s\t\t\tsig: ", indent);
	if (in->sig.len)
		_print_hex_buffer(in->sig.sig, in->sig.len);
	else
		printf("null");
	printf("\n");

	printf("%s\t\t}\n", indent);

	(void)idx;
	return (0);
}

static int _tx_out_print(tx_out_t const *out, unsigned int idx,
	char const *indent)
{
	printf("%s\t\t{\n", indent);

	printf("%s\t\t\tamount: %u,\n", indent, out->amount);
	printf("%s\t\t\tpub: ", indent);
	_print_hex_buffer(out->pub, sizeof(out->pub));
	printf(",\n");
	printf("%s\t\t\thash: ", indent);
	_print_hex_buffer(out->hash, sizeof(out->hash));
	printf("\n");

	printf("%s\t\t}\n", indent);

	(void)idx;
	return (0);
}

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
