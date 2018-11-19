# Linked list C library

C API to create and manipulate linked lists.

## Install

This library has been compiled for Linux 64 bit.

Run the following command to install it: `sudo ./install.bash`

## Usage

Don't forget to compile your program using the following link flags:

```
gcc [...] -lllist -pthread
```

## API

### **llist_create** - Creates a list

- Prototype: `llist_t *llist_create(unsigned int flags);`

### **llist_destroy** - Destroys a list

- Prototype: `int llist_destroy(llist_t *list, int destroy_nodes, node_dtor_t destructor);`

### **llist_add_node** - Adds a node to a list

- Prototype: `int llist_add_node(llist_t *list, llist_node_t node, int flags);`

### **llist_insert_node** - Inserts a node at a specific location in a list

- Prototype: `int llist_insert_node(llist_t *list, llist_node_t node, node_ident_t identifier, void *arg, int flags);`


### **llist_remove_node** - Removes a node from a list

- Prototype: `int llist_remove_node(llist_t *list, node_ident_t identifier, void *arg, int destroy_node, node_dtor_t destructor);`

### **llist_find_node** - Finds a node in a list

- Prototype: `llist_node_t llist_find_node(llist_t *list, node_ident_t identifier, void *arg);`

### **llist_get_node_at** - Gets a node at a specific index in a list

- Prototype: `llist_node_t llist_get_node_at(llist_t *list, unsigned int index);`

### **llist_for_each** - Operates on each element of a list

- Prototype: `int llist_for_each(llist_t *list, node_func_t action, void *arg);`

### **llist_get_head** - Retrieves the head node of a list

- Prototype: `llist_node_t llist_get_head(llist_t *list);`

### **llist_get_tail** - Retrieves the tail node of a list

- Prototype: `llist_node_t llist_get_tail(llist_t *list);`

### **llist_pop** - Pops out the head of the list

- Prototype: `llist_node_t llist_pop(llist_t *list);`

### **llist_size** - Gets the number of nodes in a list

- Prototype: `int llist_size(llist_t *list);`

### **llist_is_empty** - Checks if a list is empty

- Prototype: `int llist_is_empty(llist_t *list);`

### **llist_append** - Concatenates the second list to the first list

- Prototype: `int llist_append(llist_t *first, llist_t *second);`

### **llist_reverse** - Reverses the order of the nodes inside a list

- Prototype: `int llist_reverse(llist_t *list);`

### **llist_sort** - Sorts a list

- Prototype: `int llist_sort(llist_t *list, node_cmp_t cmp_func, void *arg, int flags);`
