#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <string>
#include <bits/stdc++.h>
#include <functional>
#include <utility>
#include <queue>
#include <fstream>

using namespace std;

map<vector<vector<int> >, bool> visited;
map<vector<vector<int> >, vector<vector<int> > > parent;
vector<vector<int> > goal(3, vector<int>(3));

bool visit(vector<vector<int> > a) {
    if (visited[a] == true)
        return true;

    return false;
}

int manhattan(vector<vector<int> > a) {
    int dist = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] != 0) {
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if (a[i][j] == goal[k][l])
                            dist += abs(i - k) + abs(j - l);
                    }
                }
            }
        }
    }
    return dist;
}

bool isGoal(vector<vector<int> > a) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] != goal[i][j])
                return 0;
        }
    }

    return 1;
}

bool safe(int i, int j) {
    if (i >= 0 && i <= 2 && j >= 0 && j <= 2)
        return true;

    return false;
}

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

vector<vector<vector<int> > > neighbours(vector<vector<int> > a) {
    pair<int, int> pos;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] == 0) {
                pos.first = i;
                pos.second = j;
                break;
            }
        }
    }

    vector<vector<vector<int> > > ans;
    for (int k = 0; k < 4; k++) {
        int cx = pos.first;
        int cy = pos.second;
        vector<vector<int> > n = a;
        if (safe(cx + dx[k], cy + dy[k])) {
            swap(n[cx + dx[k]][cy + dy[k]], n[cx][cy]);
            ans.push_back(n);
        }
    }

    return ans;
}

typedef pair<vector<vector<int> >, int> state; // Modified type to remove "moves"

struct cmp {
    bool operator()(state& a, state& b) {
        int am = manhattan(a.first);
        int bm = manhattan(b.first);
        return am < bm;
    }
};

void print_path(vector<vector<int> > s) {
    if (parent.count(s))
        print_path(parent[s]);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", s[i][j]);
        }
        cout << endl;
    }
    cout << endl;

    return;
}

void print(vector<vector<int> > s) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", s[i][j]);
        }
        cout << endl;
    }
}

void solve(vector<vector<int> > a) {
    priority_queue<state, vector<state>, cmp> Q;
    Q.push(state(a, 0)); // Removed "moves" parameter
    while (!Q.empty()) {
        vector<vector<int> > s = Q.top().first;
        Q.pop();
        visited[s] = true;
        if (s == goal) {
            print_path(s);
            break;
        }
        vector<vector<vector<int> > > ns = neighbours(s);
        vector<vector<vector<int> > >::iterator it;
        for (it = ns.begin(); it != ns.end(); it++) {
            vector<vector<int> > temp = *it;
            if (!visit(temp)) {
                parent.insert(pair<vector<vector<int> >, vector<vector<int> > >(temp, s));
                Q.push(state(temp, 0)); // Removed "moves" parameter
            }
        }
    }
    return;
}

int main() {
    string line;
    ifstream myFile("prog1_input.txt");
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            // cout << line << '\n';
        }
        myFile.close();
    }

    cout << "Please enter your 8 Puzzle as a string! \n";
    cout << "\nFor example => 0 1 3 4 2 5 7 8 6\n";
    vector<vector<int> > a(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }
    cout << "\nPlease wait while the puzzle is solving...\n";
    goal[0][0] = 0;
    goal[0][1] = 1;
    goal[0][2] = 2;
    goal[1][0] = 3;
    goal[1][1] = 4;
    goal[1][2] = 5;
    goal[2][0] = 6;
    goal[2][1] = 7;
    goal[2][2] = 8;
    solve(a);

    ofstream outFile;
    outFile.open("prog1_output.txt");
}

