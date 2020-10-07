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

void load_MusicLibrary(string music_library_name) {

    fstream music_library_file;

    music_library_file.open("/mnt/c/ms@uci/253P/hw1/" + music_library_name, fstream::in | std::fstream::out | std::fstream::app);

    string line;
    if (music_library_file.is_open())
    {
        int i = 0;
        while (getline(music_library_file, line))
        {

            if (i >= SONGMAX) break;

            istringstream iss(line);
            vector<string> song_info;
            for(string each; iss >> each;)
                song_info.push_back(each);

            music_library[i].title = song_info[0];
            music_library[i].artist = song_info[1];
            music_library[i].year_published = stoi(song_info[2]);

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
            music_library_file << music_library[i].title << " " << music_library[i].artist << " " << music_library[i].year_published << "\n";
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

void evaluate_command(char command) {
    switch (command)
    {
    case 'i':
        cout << "insert";
        break;
    case 'p':
        print_MusicLibrary();
    case 'l':
        break;
    case 'd':
        break;
    case 'q':
        break;
    default:
        break;
    }
}

void read_command(string music_library_name) {
    cout << music_library_name + "Commands:";
    char command;
    cin >> command;
    evaluate_command(tolower(command));
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

    store_MusicLibrary(music_library_name);


    return 0;
}
