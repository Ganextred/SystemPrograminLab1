#include <iostream>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

vector<string> wordsList;



int distance(const string& word1, const string& word2) {
    int dist = 0;
    for (size_t i = 0; i < min(word1.length(), word2.length()); ++i) {
        if (word1[i] != word2[i]) {
            ++dist;
        }
    }
    dist += abs(int(word1.length()) - int(word2.length()));
    return dist;
}

bool is_clique(vector<int> currClique, int candidate, int** adjacency)
{
    for (int itr = 0; itr < currClique.size(); itr++) {
        if (adjacency[currClique[itr]][candidate] == 0 )
            return false;
    }
    return true;
}

// Function to find all the sizes
// of maximal cliques
void maxCliques(int i, vector<int>& clique, int** adjacency, int n)
{

    // Check if any vertices from i+1
    // can be inserted
    bool f = false;
    for (int j = 0; j < n; j++) {
        // Try to add the vertex to clique
        if (is_clique(clique, j, adjacency)) {
            f = true;
            if (j>=i) {
                clique.push_back(j);
                maxCliques(j, clique, adjacency, n);
                clique.pop_back();
            }
        }
    }
    //if flag is false we were not able to add more vertexes and clique has a max size
    if (f == false and clique.size() > 1) {
        for (int it = 0; it < clique.size(); it++)
            cout << wordsList[clique[it]] << ' ';
        cout<<endl;
    }

}


int main() {
    set<string> words;
    ifstream file("input.txt");

    string line;
    while (getline(file, line)) {
        string token;
        for(char c : line){
            if(c != ' ' and c != ',' and c != '.')
                token+=c;
            else
            {
                if(!token.empty())
                    words.insert(token);
                token.clear();
            }
        }
        if(!token.empty())
            words.insert(token);
    }


    //find M
    int M;
    for(const string& w1 : words)
        for(const string& w2 : words)
        {
            int currDistance = distance(w1, w2);
            if (currDistance > M)
                M = currDistance;
        }
    cout<<"Maximum distance: "<<M<<endl;

    //build Adjacency matrix
    cout<<"Words with maximum distance:"<<endl;
    wordsList = *new vector<string>(words.begin(), words.end());;
    int wsize;
    wsize = wordsList.size();
    int** matrix = new int*[wsize];;
    for (int i = 0; i<wsize; i++) {
        matrix[i] = new int[wsize];
        for (int j = 0; j < wsize; j++) {
            int currDistance = distance(wordsList[i], wordsList[j]);
            if (currDistance == M) {
                matrix[i][j] = 1;
                cout << wordsList[i] << "  " << wordsList[j] << endl;
            } else matrix[i][j] = 0;
        }
    }
    cout<<endl;
    cout<<"Adjacency matrix:"<<endl;
    for (int i = 0; i<wsize; i++) {
        for (int j = 0; j < wsize; j++) {
            cout << matrix[i][j]<<" ";
        }
        cout << wordsList[i] << " ";
        cout<<endl;
    }

    cout<<endl;
    cout<<"Answer:"<<endl;
    //at this point task is equal to finding maximum cliques in graph and Bron–Kerbosch algorithm would be more optimal
    vector<int> clique;
    maxCliques(0, clique,matrix, wsize);


    return 0;
}