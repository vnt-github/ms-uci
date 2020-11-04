#include <iostream>

using namespace std;

struct Node {
    Node* next;
    string _title;
    string _artist;
    Node(string title,  string artist) {
        _title = title;
        _artist = artist;
        next = nullptr;
    }
    string strNode() {
        return _title + " [" + _artist + "]";
    }
}; 

struct SimplePlayList {
    Node* current_node;
    Node* head;
    
    int numberSongs() {
        int ans = 0;
        Node* curr=head;
        while (curr) {
            curr = curr->next;
            ans += 1;
        }
        return ans;
    }


    // add song to front and return bool representing status
    void push(string title, string artist) {
        Node* new_node = new Node(title, artist);
        new_node->next = head;
        head = new_node;
        if (!current_node) current_node = head;
    }

    // returns last song in the playlist
    Node* getTail() {
        if (!head) return head;
        Node* curr = head;
        while (curr->next) curr=curr->next;
        return curr;
    }

    // append to the end of playlist
    bool queue(string title, string artist) {
        Node* new_node = new Node(title, artist);
        Node* tail = getTail();
        if (!tail) head = new_node;
        else tail->next = new_node;
        if (!current_node) current_node = head;
    }

    // set current as head
    void restart() {
        current_node = head;
    }

    // return pointer to the node previous to current node(node)
    Node* getPrevNode(Node* node) {
        if (!head) return head;
        if (!node) return node;
        if (node == head) return getTail();
        Node* curr = head;
        while (curr && curr->next != node) curr = curr->next;
        return curr;
    }

    // return pointer to the node next to current node(node)
    Node* getNextNode(Node* node) {
        if (!head) return head;
        if (!node) return node;
        if (!node->next) return head;
        return node->next;
    }

    // logs the song pointerd by node, previous song and the next song to node
    void logSong(Node* node) {
        if (!node) {
            cout << "empty playlist" << endl;
        } else {
            Node* prev_node = getPrevNode(node);
            Node* next_node = getNextNode(node);
            cout << "the current_node song is: " << node->strNode() << endl;
            if (prev_node) cout << "\tthe previous song is: " << prev_node->strNode() << endl;
            if (next_node) cout << "\tthe next song is: " << next_node->strNode() << endl;
        }
    }

    // log current song, previous song and next song to current song
    void current() {
        logSong(current_node);
    }

    // delete current song and make next the current node in cyclic order
    void delete_curr() {
        if (!current_node || !head) return;
        Node* next_node = current_node->next;
        if (!next_node) {
            delete current_node;
            current_node = head;
            return;
        }
        current_node->_title = next_node->_title;
        current_node->_artist = next_node->_artist;
        current_node->next = next_node->next;
        delete next_node;
    }

    // set current to it's previous node
    void prev() {
        current_node = getPrevNode(current_node);
    }

    // set current to it's next node
    void next() {
        current_node = getNextNode(current_node);
    }


    // return pointer to node with given title and artist
    Node* getNode(string title, string artist) {
        if (!head) return nullptr;
        
        Node* curr = head;
        while (curr) {
            if (curr->_title == title && curr->_artist == artist)
                return curr;
            curr = curr->next;
        }
        cout << "cannot find song!" << endl;
        return nullptr;
    }

    // find and log the given song with required title and artist
    void find(string title, string artist) {
        Node* node = getNode(title, artist);
        if (!node) return;
        logSong(node);
    }

    // set current to found node with given title and artist
    void changeTo(string title, string artist) {
        Node* node = getNode(title, artist);
        if (!node) return;
        current_node = node;   
    }

    // adds a song before another existing song
    void addBefore(string title, string artist, string new_title, string new_artist) {
        Node* node = getNode(title, artist);
        if (!node) return;
        Node* new_node = new Node(new_title, new_artist);
        if (node == head) {
            new_node->next = head;
            head = new_node;
            return;
        }
        Node* prev_node = getPrevNode(node);
        prev_node->next = new_node;
        new_node->next = node;
    }

    // adds a song after another existing song
    void addAfter(string title, string artist, string new_title, string new_artist) {
        Node* node = getNode(title, artist);
        if (!node) return;
        Node* new_node = new Node(new_title, new_artist);
        new_node->next = node->next;
        node->next = new_node; 
    }

    // make random song the current song
    void random() {
        int len_songs = numberSongs();
        int randon_i = (rand() % len_songs) + 1;
        Node* curr = head;
        for (int i = 0; i < randon_i; i++)
            curr = curr->next;
        current_node = curr;
    }

    // displays the playlist (in order) 
    void print() {
        Node* curr = head;
        cout << "the playlist is:" << endl;
        int count = 0;
        while (curr) {
            cout << "\t" << ++count << ". " << curr->strNode() << endl;
            curr = curr->next;
        }
    }

};

int main(int argc, char const *argv[])
{
    // TODO: process input
    SimplePlayList* p = new SimplePlayList();
    // push Mundian To Bach Ke [Panjabi MC]
    p->push("Mundian To Bach Ke", "Panjabi MC");
    // push My Immortal [Evanescence]
    p->push("My Immortal", "Evanescence");
    // queue California Love [Tupac]
    p->queue("California Love", "Tupac");
    p->print();
    // next
    p->next();
    // current
    p->current();
    // addBefore Mundian To Bach Ke [Panjabi MC] Canta Per Me [Yuki Kajiura]
    p->addBefore("Mundian To Bach Ke", "Panjabi MC", "Canta Per Me", "Yuki Kajiura");
    // addAfter Mundian To Bach Ke [Panjabi MC] Shape Of My Heart [Sting]
    p->addAfter("Mundian To Bach Ke", "Panjabi MC", "Shape Of My Heart", "Sting");
    // current
    p->current();
    // prev
    p->prev();
    // prev
    p->prev();
    // delete
    p->delete_curr();
    // changeTo California Love [Tupac]
    p->changeTo("California Love", "Tupac");
    // current
    p->current();
    // find Mundian To Bach Ke [Panjabi MC]
    p->find("Mundian To Bach Ke", "Panjabi MC");
    // print
    p->print();
}
