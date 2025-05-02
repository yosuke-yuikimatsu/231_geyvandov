#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    int num;

    
    while (scanf("%d", &num) == 1 && num != 0) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) {
            
            Node* current = head;
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                free(temp);
            }
            return 1;
        }
        new_node->data = num;
        new_node->next = NULL;

        if (tail == NULL) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;

    
    Node* temp = head;
    if (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        while (temp != NULL) {
            printf(" %d", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }

    
    while (head != NULL) {
        Node* to_free = head;
        head = head->next;
        free(to_free);
    }

    return 0;
}