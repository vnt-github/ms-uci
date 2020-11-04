/**
 * clones the linked list Nodes with head and return the hash map
 * maintaining the mapping of head's nodes reference to new nodes reference
 * @param head linked list to be replicated
 * @return hashmap with original head node mapped to new Nodes
*/
unordered_map<Node*, Node*> getCopyNodeMap(Node* head) {
    Node* curr = head;
    unordered_map<Node*, Node*> nodeMap;
    while (curr) {
        nodeMap[curr] = new Node(curr->val);
        curr = curr->next;
    }
    return nodeMap;
}

/**
 * copy the linked list with additional random pointer
 * @param head of the linked list to be replicated
 * @return head of the replicated/cloned linked list
 * */
Node* copyRandomList(Node* head) {
    unordered_map<Node*, Node*> nodeMap = getCopyNodeMap(head);
    for (auto &&each : nodeMap) {
        if (!each.first) continue;
        each.second->next = nodeMap[each.first->next];
        each.second->random = nodeMap[each.first->random];
    }
    return nodeMap[head];
}