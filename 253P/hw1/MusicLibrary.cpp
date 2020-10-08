#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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

/**
 * remove an item from the music list with O(n) complexity
 * @param index to be crunced from
 * */
void crunch_up_from_index(int index) {
    for (int i = index; i+1 < current_number_of_songs; i++)
    {
        music_library[i] = music_library[i+1];
    }
}


/**
 * make space to add an item into music list with O(n) complexity
 * @param index to be crunched from
 * */
void crunch_down_from_index(int index) {
    for (int i = current_number_of_songs; i > index; i--)
    {
        music_library[i] = music_library[i-1];
    }
}

/**
 * performs binary search of a song from current music library's list
 * @param: song_title: the song to be looked up
 * @return the index in the library list of the location of the song if exists or best expected loacation if not exists
 * */
int find_index_of_song_with_name(string song_title) {
    // NOTE: transforming to lower case to ignore the letter case
    transform(song_title.begin(), song_title.end(), song_title.begin(), ::tolower);

    int left_i = 0;
    int right_i = current_number_of_songs-1;

    int mid_i;
    string mid_v;
    // NOTE: this binary search
    while (left_i <= right_i) {
        mid_i = left_i + (right_i - left_i) / 2;
        mid_v = music_library[mid_i].title;
        // NOTE: transforming to lower case to ignore the letter case
        transform(mid_v.begin(), mid_v.end(), mid_v.begin(), ::tolower);
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

/**
 * removes a song with the specified name
 * @param: song_title is the song to be removed
 * */
void remove_song_from_MusicLibrary_by_name(string song_title) {
    int i = find_index_of_song_with_name(song_title);
    transform(song_title.begin(), song_title.end(), song_title.begin(), ::tolower);

    if (i < 0 || i >= current_number_of_songs) {
        cout << "song with title: " << song_title << " not found" << endl;
        return;
    }

    string found = music_library[i].title;
    transform(found.begin(), found.end(), found.begin(), ::tolower);

    if (found != song_title) {
        cout << "song with title: " << song_title << " not found" << endl;
        return;
    }

    crunch_up_from_index(i);
    current_number_of_songs -= 1;
    // cout << "Succesfully deleted song with title: " << song_title << endl;
}


/**
 * takes a song and puts it in the MusicLibrary in memory in the proper location.
 * @param: new_song is the Song struct to be added
 * */
void add_song_to_MusicLibrary(Song new_song) {
    int i = find_index_of_song_with_name(new_song.title);
    string song_title = new_song.title;
    transform(song_title.begin(), song_title.end(), song_title.begin(), ::tolower);

    if (i >= 0 && i < current_number_of_songs) {
        
        string found = music_library[i].title;
        transform(found.begin(), found.end(), found.begin(), ::tolower);
        if (found == song_title) {
            cout << "input song with given title already exists, may be in with difference letter case" << endl;
            return;
        }
    }

    crunch_down_from_index(i);
    music_library[i] = new_song;
    current_number_of_songs += 1;
}

/**
 * handles the input and output processing for writing a song
 * */
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

/**
 * handles the input and output processing for reading a song
 * */
void read_song() {

    string song_title;
    cout << "Title: ";

    getline(cin, song_title);

    int i = find_index_of_song_with_name(song_title);
    transform(song_title.begin(), song_title.end(), song_title.begin(), ::tolower);

    if (i < 0 || i >= current_number_of_songs) {
        cout << "song with title: " << song_title << " not found" << endl;
        return;
    }

    string found = music_library[i].title;
    transform(found.begin(), found.end(), found.begin(), ::tolower);

    if (found != song_title) {
        cout << "song with title: " << song_title << " not found" << endl;
        return;
    }

    cout << " Title: " << music_library[i].title << ", Artist: " << music_library[i].artist << " , Year Published: " << music_library[i].year_published << endl;
}

/**
 * handles the input processing for deleting a song
 * */
void del_song() {
    string song_title;
    cout << "Title: ";

    // cin.ignore();
    getline(cin, song_title);

    remove_song_from_MusicLibrary_by_name(song_title);
}


/**
 * load a music library into memory for processing from file storage
 * @param music_library_name the name of music library to be managed
 * */
void load_MusicLibrary(string music_library_name) {

    fstream music_library_file;

    music_library_file.open("./" + music_library_name, fstream::in | std::fstream::out | std::fstream::app);

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

/**
 * store a music library into file storage from memory
 * @param music_library_name the name of music library to be managed
 * */
void store_MusicLibrary(string music_library_name)  {
    ofstream music_library_file;
    music_library_file.open("./" + music_library_name, ofstream::out | ofstream::trunc);

    if (music_library_file.is_open()) {
        for (int i = 0; i < current_number_of_songs; i++)
        {
            music_library_file << music_library[i].title << endl << music_library[i].artist << endl << music_library[i].year_published << endl << separator << endl;
        }
    }
    music_library_file.close();
}

/**
 * print the current state of the  music library
 * */
void print_MusicLibrary() {
    cout << endl;
    for (int i = 0; i < current_number_of_songs; i++)
    {
        Song curr_song = music_library[i];
        cout << i+1 << " Title: " << curr_song.title << ", Artist: " << curr_song.artist << " , Year Published: " << curr_song.year_published << endl;
    }
}

/**
 * determine the operations to perform on library based on incomming command
 * @param command: the command to process
 * @param music_library_name the name of music library to be managed
 * */
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


/**
 * reach character(s) from input to be processed by eval_command
 * @param music_library_name the name of music library to be managed
 * */
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