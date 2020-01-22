/*Gauge Zidlick,lib_info.cpp
 * Project 1: Write a program that takes a text file 
 * containing information about a music library
 * and organize it according to musician, album, and track numbers. */
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;

struct Song { 
	    string title;
	    int time;  // could also be a string
	    int track;
};

struct Album {
	    map <int, Song *> songs;
	    string name;
	    int time;
	    int nsongs;  // optional variable but makes it easier
};

struct Artist {
	    map <string, Album *> albums;
		string name;
		int time;
		int nsongs;
};
void clearunderscore(string &string){
	for(unsigned int i = 0;i<string.size();i++){	//looks at each char in a string, replacing '_' with a space
		if(string[i] == '_'){
			string[i] = ' ';
		}
	}
}
int convertTime(string &instring){
	stringstream temp(instring);
	string mm,ss;
	int m,s;
	getline(temp,mm,':');	//puts the numbers before the colon into separate string
	getline(temp,ss);		//puts the numners after the colon into different string
	m = atoi(mm.c_str());	//converts string into integers
	s = atoi(ss.c_str());
	return (m*60)+s;		//returns integer of total seconds
}
void PrintAll(map<string,Artist *> &inList){
	map<string,Artist *>::iterator Lit;
	map<string,Album *>::iterator Ait;
	map<int,Song *>::iterator Sit;

	for(Lit=inList.begin();Lit!=inList.end();Lit++){
		printf("%s: %d, %d:%02d\n",Lit->second->name.c_str(),Lit->second->nsongs,Lit->second->time/60,Lit->second->time%60);
		for(Ait=Lit->second->albums.begin();Ait!=Lit->second->albums.end();Ait++){
			printf("        %s: %d, %d:%02d\n",Ait->second->name.c_str(),Ait->second->nsongs,Ait->second->time/60,Ait->second->time%60);
			for(Sit=Ait->second->songs.begin();Sit!=Ait->second->songs.end();Sit++){
				printf("                %d. %s: %d:%02d\n",Sit->first,Sit->second->title.c_str(),Sit->second->time/60,Sit->second->time%60);
			}
		}
	}
}
void destructor(map<string,Artist *> &inList){
	map<string,Artist *>::iterator Lit,delLit;
	map<string,Album *>::iterator Ait,delAit;
	map<int,Song *>::iterator Sit,delSit;

	for(Lit=inList.begin();Lit!=inList.end();Lit++){
		delLit = Lit;
		for(Ait=Lit->second->albums.begin();Ait!=Lit->second->albums.end();Ait++){
			delAit = Ait;
			for(Sit=Ait->second->songs.begin();Sit!=Ait->second->songs.end();Sit++){
				delSit = Sit;
				delete Sit->second;
			}
			delete Ait->second;
		}
		delete Lit->second;
	}
}

int main(int argc, char** argv){
	string input, inTitle, inTime, inArtist, inAlbum, inGenre;
	int inTrack = 0;
	map<string,Artist *> listArt;	//this map will be used to keep track of the Artist structs
	map<string,Artist *>::iterator it;
	map<string,Album *>::iterator Albumit;

	ifstream file(argv[1]);	//opens first argument of command line in file stream
	istringstream ss;

	//while loop will iterate as long as string stream is getting input from getline
	//main body of loop will take string stream input and separate into different variables
	//use variables to test for duplicates and create new structs containing this information
	while(getline(file,input)){
		ss.clear();	
		ss.str(input);
		ss >> inTitle >> inTime >> inArtist >> inAlbum >> inGenre >> inTrack;		//takes string stream and separates info into different variables

		clearunderscore(inTitle);
		clearunderscore(inArtist);
		clearunderscore(inAlbum);

		Song *newSong = new Song;	//creates new instance of struct Song and initialize appropriate info
		newSong->title = inTitle;	//using this-> to dereference pointer and access variables inside the struct
		newSong->time = convertTime(inTime);	//time will be in total seconds, converts to mm:ss when printing
		newSong->track = inTrack;

		it = listArt.find(inArtist);	//.find() returns place in map or end of map if not found

		if(it == listArt.end()){	//if it equals the end of the map then artist does not exist
			Artist *newArtist = new Artist;		//create new instance of Artist
			newArtist->name = inArtist;			//initialize newArtist with variable from input
			newArtist->time = 0;
			newArtist->nsongs = 0;
			listArt.insert(make_pair(inArtist,newArtist));	//inserts newArtist into map within main

			//if it is a new artist then it will be a new album and new song
			Album *newAlbum = new Album;		//create new instance of Album
			newAlbum->name = inAlbum;			//initialize newAlbum with variable from input
			newAlbum->time = 0;
			newAlbum->nsongs = 0;
			newArtist->albums.insert(make_pair(inAlbum,newAlbum));	//insert newAlbum into corresponding Artist map
			newAlbum->songs.insert(make_pair(inTrack,newSong));		//insert newSong into corresponding Album map

			newAlbum->time += newSong->time;	//adds time of new song to total time of album
			newAlbum->nsongs++;					//increases count for number of songs in album
			newArtist->time += newSong->time;	//adds time of new song to total time for artist
			newArtist->nsongs++;				//increases count for number of songs for artist
		}
		//if artist is found, 'it' will contain its postion in map so it->second will dereference *Artist
		//in order to access the Artist struct member variables correctly
		else{	
			Albumit = it->second->albums.find(inAlbum); //works the same way as 'it' but instead searches albums map inside Artist struct
			if(Albumit == it->second->albums.end()){	//if Albumit equals the end of map then album does not exist
				Album *newAlbum = new Album;			//creates new instance of album and initializes with input
				newAlbum->name = inAlbum;
				newAlbum->time = 0;
				newAlbum->nsongs = 0;
				it->second->albums.insert(make_pair(inAlbum,newAlbum));		//insert newAlbum into Artist.albums

				newAlbum->songs.insert(make_pair(inTrack,newSong));			//insert newSong into Albums.songs
				newAlbum->time += newSong->time;							//increases total album time
				newAlbum->nsongs++;											//increase total album song count

				it->second->time += newSong->time;							//increase total time of Artist
				it->second->nsongs++;										//increase total songs of Artist
			}
			//Album and Artist exist just added song to corresponding Album map
			else{
				Albumit->second->songs.insert(make_pair(inTrack,newSong));
				Albumit->second->time += newSong->time;
				Albumit->second->nsongs++;

				it->second->time += newSong->time;
				it->second->nsongs++;
			}
		}
	}
	PrintAll(listArt);		//prints all of the artists, albums, and songs
	destructor(listArt);	//deallocates all the memory
	file.close();			//closes file stream
}
