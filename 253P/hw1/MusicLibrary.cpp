#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define SONGMAX 1024

using namespace std;

struct Song {
    string title;
    string artist;
    int year_published;
};

struct Song music_library[SONGMAX];
int current_number_of_songs = 0;
string separator = "-----------------------------------";

void crunch_up_from_index(int index) {
    for (size_t i = index; i+1 < current_number_of_songs; i++)
    {
        music_library[i] = music_library[i+1]; 
    }
}

void crunch_down_from_index(int index) {
    for (size_t i = current_number_of_songs; i > index; i--)
    {
        music_library[i] = music_library[i-1];
    }
}

int find_index_of_song_with_name(string song_title) {
    int left_i = 0;
    int right_i = current_number_of_songs-1;

    int mid_i;
    string mid_v;
    // NOTE: this binary search
    while (left_i <= right_i) {
        mid_i = left_i + (right_i - left_i) / 2;
        mid_v = music_library[mid_i].title;
        if (mid_v == song_title) {
            return mid_i;
        } else if (mid_v < song_title) {
            left_i = mid_i + 1;
        } else {
            right_i = mid_i - 1;
        }
    }

    return left_i;
}

void remove_song_from_MusicLibrary_by_name(string song_title) {
    int i = find_index_of_song_with_name(song_title);

    if (i < 0 || i >= current_number_of_songs || music_library[i].title != song_title) {
        cout << "song with title: " << song_title << " not found" << endl;
        return;
    }

    crunch_up_from_index(i);
    current_number_of_songs -= 1;
    cout << "Succesfully deleted song with title: " << song_title << " 😀" << endl;
}

void add_song_to_MusicLibrary(Song new_song) {
    int i = find_index_of_song_with_name(new_song.title);


    if (i >= 0 && i < current_number_of_songs && music_library[i].title == new_song.title && music_library[i].artist == new_song.artist && music_library[i].year_published == new_song.year_published) {
        cout << "input song with given parameters already exists" << endl;
        return;
    }

    crunch_down_from_index(i);
    music_library[i] = new_song;
    current_number_of_songs += 1;
}

void write_song() {
    Song new_song;
    cout << "Title:";
    
    // cin.ignore();
    getline (cin, new_song.title);
    cout << "Artist:";
    getline (cin, new_song.artist);
    cout << "Year Published:";
    cin >> new_song.year_published;
    cin.ignore();
    add_song_to_MusicLibrary(new_song);
}

void read_song() {

    string song_title;
    cout << "Title: ";

    getline(cin, song_title);

    int i = find_index_of_song_with_name(song_title);
    
    if (i < 0 || i >= current_number_of_songs || music_library[i].title != song_title) {
        cout << "song with title: " << song_title << " not found" << endl;
        return;
    }

    cout << " Title: " << music_library[i].title << ", Artist: " << music_library[i].artist << " , Year Published: " << music_library[i].year_published << endl; 

}

void del_song() {
    string song_title;
    cout << "Title: ";

    // cin.ignore();
    getline(cin, song_title);

    remove_song_from_MusicLibrary_by_name(song_title);
}

void load_MusicLibrary(string music_library_name) {

    fstream music_library_file;

    music_library_file.open("/mnt/c/ms@uci/253P/hw1/" + music_library_name, fstream::in | std::fstream::out | std::fstream::app);

    string line;
    int i = 0;
    if (music_library_file.is_open())
    {
        Song loaded_song;
        string year_published;
        string file_separator;
        while (getline(music_library_file, loaded_song.title))
        {

            getline(music_library_file, loaded_song.artist);
            getline(music_library_file, year_published);
            getline(music_library_file, file_separator);
            loaded_song.year_published = stoi(year_published);

            if (i >= SONGMAX) break;


            music_library[i] = loaded_song;
            i += 1;
        }
        current_number_of_songs = i;
        music_library_file.close();
    }
} 

void store_MusicLibrary(string music_library_name)  {
    ofstream music_library_file;
    music_library_file.open("/mnt/c/ms@uci/253P/hw1/" + music_library_name, ofstream::out | ofstream::trunc);

    if (music_library_file.is_open()) {
        for (size_t i = 0; i < current_number_of_songs; i++)
        {
            music_library_file << music_library[i].title << endl << music_library[i].artist << endl << music_library[i].year_published << endl << separator << endl;
        }   
    }
    music_library_file.close();
}

void print_MusicLibrary() {
    cout << endl;
    for (size_t i = 0; i < current_number_of_songs; i++)
    {
        Song curr_song = music_library[i];
        cout << i+1 << " Title: " << curr_song.title << ", Artist: " << curr_song.artist << " , Year Published: " << curr_song.year_published << endl; 
    }
}

void evaluate_command(char command, string music_library_name) {
    switch (command)
    {
    case 'i':
        write_song();
        break;
    case 'p':
        print_MusicLibrary();
        break;
    case 'l':
        read_song();
        break;
    case 'd':
        del_song();
        break;
    case 'q':
        store_MusicLibrary(music_library_name);
        exit(0);
    default:
        cout << "try again, usage => i: insert, p: print, l: lookup, d: delete, q: quit" << endl;
        break;
    }
}

void read_command(string music_library_name) {
    string command;

    while (true)
    {
        cout << music_library_name + " Commands:";

        getline(cin, command);

        if (command.size() > 1) {
            cout << "try again, usage => i: insert, p: print, l: lookup, d: delete, q: quit" << endl;
            continue;
        }

        evaluate_command(tolower(command[0]), music_library_name);
    }
}

int main(int argc, char const *argv[])
{
    string music_library_name = "myMusic";
    string line;
    if (argc == 2) {
        music_library_name = argv[1];
    } else if (argc > 2) {
        cout << "usage: ./MusicLibrary 'music library to manage'";
    }

    load_MusicLibrary(music_library_name);

    read_command(music_library_name);

    return 0;
}
