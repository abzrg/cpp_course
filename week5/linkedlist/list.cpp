//===----------------------------------------------------------------------===//
//
// Philipp Schubert
//
//    Copyright (c) 2017 - 2021
//    Secure Software Engineering Group
//    Heinz Nixdorf Institute
//    Paderborn University
//    philipp.schubert@upb.de
//
//===----------------------------------------------------------------------===//

#include <iostream>

struct Node {
    int data;
    Node *next;
    Node(int i) : data(i), next(nullptr) {}
    friend std::ostream &operator<<(std::ostream &os, const Node &n) {
        os << "Node\n"
           << "\tdata: " << n.data << "\n\tthis: " << &n
           << "\n\tnext: " << n.next;
        return os;
    }
};

void addElement(Node **head, int data) {
    Node *n = new Node(data);
    if (n == nullptr) {
        fprintf(stderr, "ERROR: Could not allocate enough memory!");
        exit(EXIT_FAILURE);
    }

    // If it's an empty list
    if (*head == nullptr) {
        *head = n;
        return;
    }

    // Traverse down to last Node
    Node *last = *head;
    while (last->next != nullptr) last = last->next;
    last->next = n;
}

void printList(const Node *head) {
    while (head != nullptr) {
        std::cout << *head << std::endl;
        head = head->next;
    }
}

void deleteList(Node *head) {
    // if it's an empty list then do nothing
    if (head == nullptr) return;

    // If the list contains only one element
    if (head->next == nullptr) {
        delete head;
        return;
    }

    deleteList(head->next);
    delete head;
}

int main() {
    Node *list = nullptr;
    addElement(&list, 1);
    addElement(&list, 2);
    addElement(&list, 3);
    addElement(&list, 4);
    printList(list);
    deleteList(list);
    return 0;
}
