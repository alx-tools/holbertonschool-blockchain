#ifndef _LLIST_H_
# define _LLIST_H_

/*****************************************************************************/
/********************************** DEFINES **********************************/
/*****************************************************************************/

# define ADD_NODE_FRONT		(1 << 0)
# define ADD_NODE_REAR		(~ADD_NODE_FRONT)

# define ADD_NODE_BEFORE	(1 << 0)
# define ADD_NODE_AFTER		(~ADD_NODE_BEFORE)

# define SORT_LIST_ASC		(1 << 0)
# define SORT_LIST_DESC		(~SORT_LIST_ASC)

# define MT_SUPPORT_TRUE	(1 << 0)
# define MT_SUPPORT_FALSE	(~MT_SUPPORT_TRUE)

/*****************************************************************************/
/*********************************** TYPES ***********************************/
/*****************************************************************************/

/**
 * enum _LLIST - All the different functions errors
 *
 * @LLIST_SUCCESS:           Success
 * @LLIST_NODE_NOT_FOUND:     No matching node found
 * @LLIST_NULL_ARGUMENT:      NULL argument
 * @LLIST_OUT_OF_RANGE:       Index out of range
 * @LLIST_MALLOC_ERROR:       Memory allocation error
 * @LLIST_MULTITHREAD_ISSUE:  Multithreading error
 */
typedef enum _LLIST
{
	LLIST_SUCCESS = 0,
	LLIST_NODE_NOT_FOUND,
	LLIST_NULL_ARGUMENT,
	LLIST_OUT_OF_RANGE,
	LLIST_MALLOC_ERROR,
	LLIST_MULTITHREAD_ISSUE
} E_LLIST;

extern int llist_errno;

/* Opaque linked list structure */
typedef struct __list llist_t;
typedef void *llist_node_t;

/* function prototypes */
typedef int (*node_func_t)(llist_node_t node, unsigned int idx, void *arg);
typedef void (*node_dtor_t)(llist_node_t node);

/**
 * node_cmp_t - Function to compare two nodes
 *
 * @first:  Pointer to the first node
 * @second: Pointer to the second node
 * @arg:    Extra user-defined parameter
 *
 * Reurn: An integer less than, equal to, or greater than zero if first,
 *        respectively, is less than, equal, or greater than second
 */
typedef int (*node_cmp_t)(llist_node_t first, llist_node_t second, void *arg);

/**
 * node_ident_t - Function to identify a node
 *
 * @node: Pointer to the node to identify
 * @arg:  Extra user-defined parameter
 *
 * Return: Any non-zero value if @node is positively identified, 0 otherwise
 */
typedef int (*node_ident_t)(llist_node_t node, void *arg);

/*****************************************************************************/
/********************************* FUNCTIONS *********************************/
/*****************************************************************************/

/**
 * llist_create - Creates a list
 *
 * @flags: Used to identify whether we create a thread safe linked-list
 *         Value can be `MT_SUPPORT_FALSE` or `MT_SUPPORT_TRUE`
 *
 * Return: Pointer to new list upon success. Upon failure, NULL is returned
 *         and, the global variable `llist_errno` is set with the
 *         appropriate value
 */
llist_t *llist_create(unsigned int flags);

/**
 * llist_destroy - Destroys a list
 *
 * Description: Call this function only if the list was created using
 *              `llist_create()`. Static initialized lists cannot be destroyed
 *              using this function
 *
 * @list:          A pointer to the list to destroy
 * @destroy_nodes: 1 if the nodes should be destroyed, 0 otherwise
 * @destructor:    Node destructor used if @destroy_nodes is 1. If NULL,
 *                 the GlibC free() function is used
 *
 * Return: 0 upon success. Upon failure, -1 is returned, andthe global variable
 *         `llist_errno` is set with the appropriate value.
 */
int llist_destroy(llist_t *list, int destroy_nodes, node_dtor_t destructor);

/**
 * llist_add_node - Adds a node to a list
 *
 * @list:  Pointer to the list to add a node to
 * @node:  Pointer to the data to add as a node
 * @flags: Value can be `ADD_NODE_FRONT` or `ADD_NODE_REAR`
 *
 * Return: 0 upon success. Upon failure, -1 is returned, andthe global variable
 *         `llist_errno` is set with the appropriate value.
 */
int llist_add_node(llist_t *list, llist_node_t node, int flags);

/**
 * llist_insert_node - Inserts a node at a specific location in a list
 *
 * @list:       Pointer to the list to insert a node into
 * @node:       Pointer to the data to add as a node
 * @identifier: Function called to identify the reference node from
 *              the list. The first node for which this function returns
 *              a non-zero value will be considered the reference.
 * @arg:        Parameter to be passed to the @identifier function
 * @flags:      Value can be `ADD_NODE_BEFORE` or `ADD_NODE_AFTER`. Either
 *              add the new node before or after the reference node
 *
 * Return: 0 upon success. Upon failure, -1 is returned, andthe global variable
 *         `llist_errno` is set with the appropriate value.
 */
int llist_insert_node(llist_t *list, llist_node_t node,
	node_ident_t identifier, void *arg, int flags);

/**
 * llist_remove_node - Removes a node from a list
 *
 * @list:         Pointer to the list to delete a node from
 * @identifier:   Function called to identify the node to remove from
 *                the list. The first node for which this function returns
 *                a non-zero value will be removed from the list.
 * @arg:          Parameter to be passed to the @identifier function
 * @destroy_node: 1 if the node should be destroyed, 0 otherwise
 * @destructor:   Node destructor used if @destroy_node is 1. If NULL,
 *                the free() function is used
 *
 * Return: 0 upon success. Upon failure, -1 is returned, andthe global variable
 *         `llist_errno` is set with the appropriate value.
 */
int llist_remove_node(llist_t *list, node_ident_t identifier, void *arg,
	int destroy_node, node_dtor_t destructor);

/**
 * llist_find_node - Finds a node in a list
 *
 * @list:       Pointer to the list to search
 * @identifier: Function called to identify the node to remove from
 *              the list. The first node for which this function returns
 *              a non-zero value will be removed from the list.
 * @arg:        Parameter to be passed to the @identifier function
 *
 * Return: Pointer to the node found upon success. Upon failure, NULL is
 *         returned and, the global variable `llist_errno` is set with the
 *         appropriate value
 */
llist_node_t llist_find_node(llist_t *list, node_ident_t identifier,
	void *arg);

/**
 * llist_get_node_at - Gets a node at a specific index in a list
 *
 * @list:  Pointer to the list to search
 * @index: Index at which to retrieve the node
 *
 * Return: Pointer to the node found upon success. Upon failure, NULL is
 *         returned and, the global variable `llist_errno` is set with the
 *         appropriate value
 */
llist_node_t llist_get_node_at(llist_t *list, unsigned int index);

/**
 * llist_for_each - Operates on each element of a list
 *
 * @list:   Pointer to the list to operate upon
 * @action: Function to be performed for each node in the list
 * @arg:    Parameter to be passed to the @func function
 *
 * Return: 0 upon success. Upon failure, -1 is returned, andthe global variable
 *         `llist_errno` is set with the appropriate value.
 */
int llist_for_each(llist_t *list, node_func_t action, void *arg);

/**
 * llist_get_head - Retrieves the head node of a list
 *
 * @list: Pointer to the list to get the head node of
 *
 * Return: A pointer to the tail node upon success. Upon failure, NULL is
 *         returned, and the global variable `llist_errno` is set with the
 *         appropriate value
 */
llist_node_t llist_get_head(llist_t *list);

/**
 * llist_get_tail - Retrieves the tail node of a list
 *
 * @list: Pointer to the list to get the tail node of
 *
 * Return: A pointer to the tail node upon success. Upon failure, NULL is
 *         returned, and the global variable `llist_errno` is set with the
 *         appropriate value
 */
llist_node_t llist_get_tail(llist_t *list);

/**
 * llist_pop - Pops out the head of the list
 *
 * @list: Pointer to the list to pops out the head from
 *
 * Return: A pointer to the former head node of the list upon success, NULL is
 *         returned upon failure and the global variable `llist_errno` is set
 *         with the appropriate value
 */
llist_node_t llist_pop(llist_t *list);

/**
 * llist_size - Gets the number of nodes in a list
 *
 * @list: Pointer to the list to get the size of
 *
 * Return: Number of nodes in the list upon success. Upon failure, -1 is
 *         returned, andthe global variable `llist_errno` is set with the
 *         appropriate value.
 */
int llist_size(llist_t *list);

/**
 * llist_is_empty - Checks if a list is empty
 *
 * @list: Pointer to the list to check
 *
 * Return: 0 if the list contains at least one node, 1 otherwise
 */
int llist_is_empty(llist_t *list);

/**
 * llist_append - Concatenates the second list to the first list
 *
 * Description: The nodes from the second list will be removed and inserted in
 *              the first list, so after calling this function, the second list
 *              is empty. Remember to call `llist_destroy()` on the second
 *              list (if it was created by `llist_create()`)
 *
 * @first:  Pointer to the first list to operate on
 * @second: Pointer to the second list to operate on.
 *
 * Return: 0 upon success. Upon failure, -1 is returned, andthe global variable
 *         `llist_errno` is set with the appropriate value.
 */
int llist_append(llist_t *first, llist_t *second);

/**
 * llist_reverse - Reverses the order of the nodes inside a list
 *
 * @list: Pointer to the list to reverse
 *
 * Return: 0 upon success. Upon failure, -1 is returned, andthe global variable
 *         `llist_errno` is set with the appropriate value.
 */
int llist_reverse(llist_t *list);

/**
 * llist_sort - Sorts a list
 *
 * @list:     Pointer to the list to sort
 * @cmp_func: Function used to compare two nodes
 * @arg:      Parameter to be passed to the @cmp_func function
 * @flags:    Value can be `SORT_LIST_ASC` or `SORT_LIST_DESC`
 *
 * Return: 0 upon success. Upon failure, -1 is returned, andthe global variable
 *         `llist_errno` is set with the appropriate value.
 */
int llist_sort(llist_t *list, node_cmp_t cmp_func, void *arg, int flags);

#endif /* ! _LLIST_H_ */
