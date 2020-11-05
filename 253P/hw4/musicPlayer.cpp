#include <iostream>
#include <regex>

using namespace std;

string ltrim(const string& s) {
	return regex_replace(s, regex("^\\s+"), string(""));
}

std::string rtrim(const std::string& s) {
	return regex_replace(s, regex("\\s+$"), string(""));
}

std::string trim(const std::string& s) {
	return ltrim(rtrim(s));
}

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

    // process input for song queries and entries
    Node* getSong() {
        string title;
        string artist;
        cout << "Enter song title:";
        getline(cin, title);
        title = trim(title);
        cout << "Enter song artist:";;
        getline(cin, artist);
        artist = trim(artist);
        cout << endl;
        return new Node(title, artist);
    }

    // add song to front
    void push() {
        Node* new_node = getSong();
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
    void queue() {
        Node* new_node = getSong();
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
    void logSong(Node* node, Node* prev_node) {
        // for calls when prev_node needs to be calculated like current
        if (!prev_node)
            prev_node = getPrevNode(node);
        if (!node) {
            cout << "empty playlist" << endl;
        } else {
            Node* next_node = getNextNode(node);
            cout << "the current_node song is: " << node->strNode() << endl;
            if (prev_node) cout << "\tthe previous song is: " << prev_node->strNode() << endl;
            if (next_node) cout << "\tthe next song is: " << next_node->strNode() << endl;
        }
    }

    // log current song, previous song and next song to current song
    void current() {
        logSong(current_node, nullptr);
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


    // return pointer previous to node with given title and artist
    Node* getNode(string title, string artist) {
        if (!head) return nullptr;
        
        Node* curr = head;
        Node* prev = curr;
        while (curr) {
            if (curr->_title == title && curr->_artist == artist)
                return prev;
            prev = curr;
            curr = curr->next;
        }
        cout << "cannot find song!" << endl;
        return nullptr;
    }

    // find and log the given song with required title and artist
    void find() {
        Node* input_node = getSong();
        Node* node = getNode(input_node->_title, input_node->_artist);
        delete input_node;
        if (!node) return;
        logSong(node->next, node);
    }

    // set current to found node with given title and artist
    void changeTo() {
        Node* input_node = getSong();
        Node* node = getNode(input_node->_title, input_node->_artist);
        delete input_node;
        if (!node) return;
        current_node = node->next;   
    }

    // adds a song before another existing song
    void addBefore() {
        Node* input_node = getSong();
        Node* node = getNode(input_node->_title, input_node->_artist);
        delete input_node;
        if (!node) return;
        node = node->next;
        Node* new_node = getSong();
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
    void addAfter() {
        Node* input_node = getSong();
        Node* node = getNode(input_node->_title, input_node->_artist);
        delete input_node;
        if (!node) return;
        node = node->next;
        Node* new_node = getSong();
        new_node->next = node->next;
        node->next = new_node; 
    }

    // make random song the current song
    void random() {
        int len_songs = numberSongs();
        if (!len_songs) {
            cout << "empty playlist" << endl;
            return;
        }
        int randon_i = (rand() % len_songs) + 1;
        Node* curr = head;
        for (int i = 0; i < randon_i-1; i++)
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

    void freeNodes() {
        Node* next;
        Node* curr = head;
        while (curr) {
            next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

void musicPlayer() {
    string command;
    SimplePlayList* p = new SimplePlayList();
    while (true) {
        cout << "command:";
        cin >> command;
        cin.clear(); cin.ignore();
        if (command == "push")
            p->push();
        else if (command == "queue")
            p->queue();
        else if (command == "current")
            p->current();
        else if (command == "delete")
            p->delete_curr();
        else if (command == "prev")
            p->prev();
        else if (command == "next")
            p->next();
        else if (command == "restart")
            p->restart();
        else if (command == "find")
            p->find();
        else if (command == "changeTo")
            p->changeTo();
        else if (command == "addBefore")
            p->addBefore();
        else if (command == "addAfter")
            p->addAfter();
        else if (command == "random")
            p->random();
        else if (command == "print")
            p->print();
        else if (command == "exit")
            break;
        else
            cout << "invalid command" << endl;
    }
    p->freeNodes();
    delete p;
}

int main()
{
    musicPlayer();
    // TODO: process input
    // push Mundian To Bach Ke [Panjabi MC]
    // p->push();
    // // push My Immortal [Evanescence]
    // p->push();
    // // queue California Love [Tupac]
    // p->queue();
    // // next
    // p->next();
    // // current
    // p->current();
    // // addBefore Mundian To Bach Ke [Panjabi MC] Canta Per Me [Yuki Kajiura]
    // p->addBefore();
    // // addAfter Mundian To Bach Ke [Panjabi MC] Shape Of My Heart [Sting]
    // p->addAfter();
    // // current
    // p->current();
    // // prev
    // p->prev();
    // // prev
    // p->prev();
    // // delete
    // p->delete_curr();
    // // changeTo California Love [Tupac]
    // p->changeTo();
    // // current
    // p->current();
    // // find Mundian To Bach Ke [Panjabi MC]
    // p->find();
    // // print
    // p->print();
}
