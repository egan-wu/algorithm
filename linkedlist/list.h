#include <stdio.h>
#include <stdlib.h>

namespace list
{
    struct list_node {
        int data;
        list_node* next;
    };

    struct list {
        list_node* head_node;
        list_node* tail_node;
        int list_num;
    };

    void init_list (list* list) {
        list->head_node = (list_node*)malloc(sizeof(list_node));
        list->tail_node = NULL;
        list->list_num = 0;
    }

    // insert node "after" current node
    void insert_node(list* list, list_node* curr_node, list_node* node) {
        list_node* tmp = curr_node->next;
        curr_node->next = node;
        node->next = tmp;
        list->list_num++;
    }

    // insert node as first node
    void insert_head(list* list, list_node* node) {
        insert_node(list, head_node, node);
    }

    // insert node as last node
    void insert_tail(list* list, list_node* node) {
        insert_node(list, tail_node, node);
    }

    void insert(list* list, list_node* node) {
        insert_tail(list, node);
    }

    void print_list(list* list) {
        list* curr = list->head_node->next;
        while (curr != NULL) {
            printf("(%d) ", curr->data);
        }
        print("\n");
    }
}

