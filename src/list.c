/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#include <assert.h>
#include "errors.h"
#include "list.h"

/* Create list node with data. */
struct list_node *
list_node_new(void *data)
{
    struct list_node *node = malloc(sizeof(struct list_node));

    if (node != NULL) {
        node->data = data;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

/* Free list node. */
void
list_node_free(struct list_node *node)
{
    if (node != NULL)
        free(node);
}

/* Create an empty list. */
struct list *
list_new(void)
{
    struct list *list = malloc(sizeof(struct list));

    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

/* Free list. */
void
list_free(struct list *list)
{
    if (list != NULL) {
        list_clear(list);
        free(list);
    }
}

/* Clear list. */
void
list_clear(struct list *list) {
    assert(list != NULL);
    while(list_lpop(list) != NULL);
}

/* Push an item to list on the left. */
error_t
list_lpush(struct list *list, void *data)
{
    assert(list != NULL);

    struct list_node *node = list_node_new(data);

    if (node == NULL)
        return ERR_NOMEM;

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        list->head = node;
        list->tail = node;
    } else {
        assert(list->head != NULL && list->tail != NULL);
        struct list_node *head = list->head;
        assert(head->prev == NULL && node->prev == NULL);
        head->prev = node;
        node->next = head;
        list->head = node;
    }

    list->size += 1;
    return ERR_OK;
}

/* Push an item to list on the right. */
error_t
list_rpush(struct list *list, void *data)
{
    assert(list != NULL);

    struct list_node *node = list_node_new(data);

    if (node == NULL)
        return ERR_NOMEM;

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        list->head = node;
        list->tail = node;
    } else {
        assert(list->head != NULL && list->tail != NULL);
        struct list_node *node = list->tail;
        assert(tail->next == NULL && node->next == NULL);
        tail->next = node;
        node->prev = tail;
        list->tail = node;
    }

    list->size += 1;
    return ERR_OK;
}

/* Pop an item from list on the left. */
void *
list_lpop(struct list *list)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);

    struct list_node *head = list->head;
    struct list_node *node = head->next;

    if (node == NULL) {
        assert(list->size == 1);
        list->tail = NULL;
    } else {
        assert(list->size >= 2);
        node->prev = NULL;
    }

    list->head = node;
    list->size -= 1;

    void *data = head->data;
    list_node_free(head);
    return data;
}

/* Pop an item from list on the right. */
void *
list_rpop(struct list *list)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);

    struct list_node *tail = list->tail;
    struct list_node *node = tail->prev;

    if (node == NULL) {
        assert(list->size == 1);
        list->head = NULL;
    } else {
        assert(list->size >= 2);
        node->next = NULL;
    }

    list->tail = node;
    list->size -= 1;

    void *data = tail->data;
    list_node_free(tail);
    return data;
}

/* Get the head node data, NULL on empty list. */
void *
list_head(struct list *list)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);
    return list->head->data;
}

/* Get the tail node data, NULL on empty list. */
void *
list_tail(struct list *list)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);
    return list->tail->data;
}