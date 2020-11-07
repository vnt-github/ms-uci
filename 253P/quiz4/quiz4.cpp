#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    int info;
    Node* next;
    Node(int newInfo, Node* newNext) {
        info = newInfo; next = newNext;   
    }
};

struct linked_list
{
    Node* head;
};

// returns  len of the list
int getLen(Node* head) {
    int len = 0;
    Node* curr = head;
    while (curr) {
        curr = curr->next;
        len += 1;
    }
    return len;
}

// return previous to ith node from end in the linked list
Node* getPrevIthNodeFromEnd(Node* head, int i) {
    Node *till_last = head;
    Node *prev_ith_node = head;
    for (int j = 0; j <= i && till_last; j++)
        till_last = till_last->next;
    
    if (!till_last)
        return nullptr;

    while (till_last) {
        till_last = till_last->next;
        prev_ith_node = prev_ith_node->next;
    }

    return prev_ith_node;
}

// remove the ith element from end in the linked list
linked_list* remove_ith_element(linked_list* head, int i) {
    if (!head->head || i <= 0 || i > getLen(head->head)) {
        head->head = nullptr;
        return nullptr;
    }
    Node* pre_head = new Node(-1, head->head);
    Node* prev_ith_node = getPrevIthNodeFromEnd(pre_head, i);
    if (!prev_ith_node) {
        pre_head->next = head->head->next;
        delete head->head;
    } else {
        Node* ithNode = prev_ith_node->next;
        prev_ith_node->next = ithNode->next;
        delete ithNode;
    }
    head->head = pre_head->next;
    return head;
}

void log(linked_list* head) {
    if (!head || !head->head) return;
    Node* curr = head->head;
    while (curr) {
        cout << curr->info << " ";
        curr=curr->next;
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    linked_list l1;
        
    for (int i = 1; i < 10; i++)
    {
        l1.head = nullptr;
        log(remove_ith_element(&l1, i));
    }
    cout << "-------" << endl;
    for (int i = 1; i < 10; i++)
    {
        l1.head = new Node(1, nullptr);
        log(remove_ith_element(&l1, i));
    }
    cout << "-------" << endl;
    for (int i = 0; i < 10; i++)
    {
        l1.head = new Node(1, (new Node(2, new Node(3, new Node(4, nullptr)))));
        log(remove_ith_element(&l1, i));
    }


    return 0;
}
