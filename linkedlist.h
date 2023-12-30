#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

/** 
 * A circular doubly linked-list node.
 */
typedef struct cll_node_s {
    int is_head;
    int value;
    struct cll_node_s *prev;
    struct cll_node_s *next;
} cll_node;


/**
 * Returns a pointer to the head node of the list, given a pointer to any node 
 * in the list. If the provided pointer is `NULL`, instead returns `NULL`. The
 * head node is the only node with `is_head` set to 1.
 */
cll_node *cll_head(cll_node *list);

/**
 * Returns a pointer to the "last" node in the list, given a pointer to any node 
 * in the list. If the provided pointer is `NULL`, instead returns `NULL`. The
 * "last" node is the node just before the head node (i.e., the node who's `next`
 * pointer points to a node with `is_head` set to 1.  The head may also be the tail.
 */
cll_node *cll_tail(cll_node *list);

/**
 * Returns the number of nodes in the list, which is the same for all nodes
 * in the list and 0 for `NULL`.
 */
unsigned long cll_length(cll_node *list);

/**
 * Given a pointer to a node in a list, returns a pointer to the first node
 * at or *after* that node which has the given `value`. If given `NULL`, or
 * if no such node exists, returns `NULL`.  That is, start looking at `list`'s
 * value and then follow next until you return to the given `list` node.
 */
cll_node *cll_find(cll_node *list, int value);


/**
 * Given a pointer to a node in a list, remove that node from the list,
 * `free`ing its memory in the process. Returns a pointer to the node that now
 * occupies the same position in the list that the removed node used to occupy.
 * 
 * If given `NULL`, this function does nothing and returns `NULL`.
 */
cll_node *cll_remove(cll_node *list);

/**
 * Extend a list by one by adding `value` next to `list`. If `before` is 0,
 * inserts `value` immediately following the node pointed to by `list`;
 * otherwise inserts `value` immediately before that node. If `list` is NULL,
 * the newly inserted node is the entire list and the `is_head` value is set
 * to 1 for this node. If `list` is not NULL, be sure to initialize all
 * fields of the node. In all cases, the new node is allocated using `malloc` 
 * and returned by the function.
 */
cll_node *cll_insert(int value, cll_node *list, int before);

/**
 * Displays the contents of the list separated by commas and surrounded by
 * brackets, with the pointed-to node highlighted with asterisks. Display
 * starts at the head node.
 */
void cll_show(cll_node *list);


#endif /* ifdef __LINKEDLIST_H */
