// return the pointer to the middle of the linked list using the turtle hare method
ListNode* splitListHalf(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head->next;

    while(fast && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next;
        if (fast != NULL && fast->next != NULL)
            fast = fast->next;
    }
    ListNode* middle = slow->next;
    slow->next = NULL;
    return middle;
}

// merge the sorted lists
ListNode* mergeSorted(ListNode* leftHead, ListNode* rightHead) {
    ListNode* left = leftHead;
    ListNode* right = rightHead;
    ListNode sortedHead(NULL);
    ListNode* curr = &sortedHead;
    while(left != NULL && right != NULL) {
        if(left->val < right->val) {
            curr->next = left;
            left = left->next;
        } else {
            curr->next = right;
            right = right->next;
        }
        curr = curr->next;
    }
    if (left == NULL) curr->next = right;
    else if (right == NULL) curr->next = left;
    return sortedHead.next;
}

// sort the list
ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* middle = splitListHalf(head);
    ListNode* rightHead = sortList(head);
    ListNode* leftHead = sortList(middle);
    ListNode* sortedHead = mergeSorted(rightHead, leftHead);
    return sortedHead;
}