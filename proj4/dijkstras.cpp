//	Gauge Zidlick	dijsktras.cpp
//	Project 4 - Implement Dijsktras algorithm to find the shortest path between two nodes on a given map.
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <set>
#include <utility>
using namespace std;


class Node{
	public:
		int x;				//x coordinate
		int y;				//y coordinate
		int weight;			//cost to move thorugh node
		int distance;		//Current optimal distance to node
		char type;			//terrain type

		bool visited;
		Node *backedge = NULL;
		vector<Node *> adj;
		multimap<int,Node *>::iterator spot_in_mm; //location where node is within mm
};
//helper function used to debug
int find_weight(set<pair<char,int> > &tiles,char tile){
	set<pair<char,int> >::iterator it;
	for(it = tiles.begin();it!=tiles.end();it++){
		if(it->first == tile){
			return it->second;
		}
	}
	return -1;
}
//helper function used to debug
void print_grid(vector<vector<Node *> > &grid){
	for(unsigned int i = 0;i<grid.size();i++){
		for(unsigned int j = 0;j<grid[i].size();j++){
			cout << grid[i][j]->type << " ";
		}
		cout << endl;
	}
}
//helper function used to debug
void print_adj(vector<vector<Node *> > &grid){
	for(unsigned int i = 0;i<grid.size();i++){
		for(unsigned int j = 0;j<grid[i].size();j++){
			cout << grid[i][j]->type << "(" << i << "," << j << "): ";
			for(unsigned int k = 0;k<grid[i][j]->adj.size();k++){
				cout << grid[i][j]->adj[k]->type << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}
//helper function used to debug
void print_map(multimap<int,Node *> &queue){
	multimap<int,Node *>::iterator it;
	for(it = queue.begin();it!=queue.end();it++){
		cout << "Distance: " << it->first << " Tile: " << it->second->type << "(" << it->second->x << "," << it->second->y << ")" << endl;
	}
}
//prints the path to destination node recursively
void backtrace(Node *target){
	if(target->backedge == NULL){
		cout << target->x << " " << target->y << endl;
		return;
	}
	backtrace(target->backedge);
	cout << target->x << " " << target->y << endl;
}
//free used memory by deleting nodes in vector
void destructor(vector<vector<Node *> > &grid){
	Node *temp;
	for(unsigned int i = 0;i<grid.size();i++){
		for(unsigned int j = 0;j<grid[i].size();j++){
			temp = grid[i][j];
			delete temp;
		}
	}
}

// Main Execution
int main(int argc, char *argv[]) {
	vector<vector<Node *> > grid;
	multimap<int,Node *> queue;
	set<pair<char,int> >tiles;
	istringstream ss;
	char tile;
	string tile_name,input;
	int distance,Ntiles,tile_value,rows,cols,startrow,startcol,endrow,endcol;
	Node *target,*start,*n;

	while(getline(cin,input)){
		grid.clear();
		queue.clear();
		tiles.clear();


		//build grid
		ss.str(input);
		ss>>Ntiles;
		for(int i = 0;i<Ntiles;i++){
			ss.clear();
			input.clear();
			getline(cin,input);
			ss.str(input);
			ss>>tile>>tile_value;
			tiles.insert(make_pair(tile,tile_value));	
		}
		ss.clear();
		getline(cin,input);
		ss.str(input);
		ss>>rows>>cols;
		for(int i = 0;i<rows;i++){
			ss.clear();
			getline(cin,input);
			ss.str(input);
			grid.push_back(vector<Node *> ());	//creates new row
			for(int j = 0;j<cols;j++){
				ss >> tile;
				Node *tilenode = new Node;
				tilenode->x = i;
				tilenode->y = j;
				tilenode->weight = find_weight(tiles,tile);
				tilenode->distance = -1;
				tilenode->type = tile;
				tilenode->visited = false;
				tilenode->spot_in_mm = queue.end();
				grid[i].push_back(tilenode);
			}
		}
		ss.clear();
		getline(cin,input);
		ss.str(input);
		ss>>startrow>>startcol;
		ss.clear();
		getline(cin,input);
		ss.str(input);
		ss>>endrow>>endcol;

		//Build adjacency lists
		for(unsigned int i = 0;i<grid.size();i++){
			for(unsigned int j = 0;j<grid[i].size();j++){
				//check boundaries on top node
				if(i > 0 && i < grid.size()){
					grid[i][j]->adj.push_back(grid[i-1][j]);
				}
				//check boundaries on left node
				if(j > 0 && j < grid[i].size()){
					grid[i][j]->adj.push_back(grid[i][j-1]);
				}
				//check boundaries on right node
				if(j >= 0 && j < grid[i].size()-1){
					grid[i][j]->adj.push_back(grid[i][j+1]);
				}
				//check boundaries on right node
				if(i >= 0 && i < grid.size()-1){
					grid[i][j]->adj.push_back(grid[i+1][j]);
				}
			}
		}

		//set the starting and ending conditions
		target = grid[endrow][endcol];
		start = grid[startrow][startcol];
		start->distance = 0;
		start->spot_in_mm = queue.insert(make_pair(start->distance,start));

		while(target->visited == false){
			n = queue.begin()->second;
			n->visited = true;
			queue.erase(n->spot_in_mm);	
			for(unsigned int i = 0;i<n->adj.size();i++){
				distance = n->distance;
				if(n->adj[i]->visited == false){
					distance += n->weight;
					if(n->adj[i]->distance == -1 || distance < n->adj[i]->distance){
						if(n->adj[i]->spot_in_mm != queue.end()){
							queue.erase(n->adj[i]->spot_in_mm);
						}
						n->adj[i]->distance = distance;
						n->adj[i]->backedge = n;
						n->adj[i]->spot_in_mm = queue.insert(make_pair(n->adj[i]->distance,n->adj[i]));
					}
				}
			}
		}
		cout << target->distance << endl;
		backtrace(target);
		destructor(grid);
	}
	return 0;
}

