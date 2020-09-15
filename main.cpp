#include <iostream>
#include <map>
#include<cstdlib>
#include <queue>

using namespace std;

struct node {
    int density;
    char owner;
};

node grid[10][10];
int filledBoxes;
map < char, int > score;
bool valid(int i, int j) {
    return i>=0 && j>=0 && i<10 && j<10;
}

void setup() {
    filledBoxes = 0;
    score['@'] = 0;
    score['#'] = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j].density = 0;
            grid[i][j].owner = ' ';
        }
    }
}

void printgrid() {
    system("CLS");
    score['@'] = score['#'] = filledBoxes = 0;
    cout << "\n\n";
    for (size_t i = 0; i < 53; i++) {
        cout << "# ";
    }
    cout << endl;
    cout << "#  ";
    for (int i = 0; i < 10; i++) {
        cout << " ---" << i + 1 << "---- ";
    }
    cout << " #" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "#";
        if (i != 9) {
            cout << ' ';
        }
        std::cout << i + 1 << ' ';
        for (int j = 0; j < 10; j++) {
            score[grid[i][j].owner]++;
            cout << "( " << grid[i][j].owner << ", ";
            if (grid[i][j].density != 0) {
                filledBoxes++;
                cout << grid[i][j].density << " )  ";
            } else cout << "  )  ";
        }
        cout << " #" << endl;
    }
    for (size_t i = 0; i < 53; i++) {
        cout << "# ";
    }
    cout << "\n\n";
    cout << "Score @ : " << score['@'] << "\t\t" << "Score #: " << score['#'] << "\n\n";

}

bool canExplode(int row, int col) {
    if ((row == 0 and col == 0) ||
        (row == 9 and col == 0) ||
        (row == 0 and col == 9) ||
        (row == 9 and col == 9)) {
        if (grid[row][col].density == 1) {
            return true;
        }
    } else if (row == 0 || row == 9 || col == 0 || col == 9) {
        if (grid[row][col].density == 2) {
            return true;
        }
    } else if (grid[row][col].density == 3) {
        return true;
    }
    return false;
}

void bfs(int row, int col, char own) {
    queue <pair<int, int> > q;

    q.push({row, col});
    while(!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        if(canExplode(cur.first, cur.second)) {
            grid[cur.first][cur.second].density = 0;
            grid[cur.first][cur.second].owner = ' ';
            int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

            for(int i = 0; i < 4; i++) {
                int x = cur.first + dx[i], y = cur.second + dy[i];
                if(!valid(x, y)) continue;
                    q.push({x, y});
            }

        } else {
            grid[cur.first][cur.second].density++;
            grid[cur.first][cur.second].owner = own;
        }
    }
}

pair < int, int > input(char player) {
    int m, n;
    cout << "Player: " << player << " Enter the index ";
    char secplayer = (player == '@' ? '#' : '@');
    while (true) {
        cin >> m >> n;
        if (grid[m-1][n-1].owner == secplayer || !valid(m - 1, n - 1)) {
            std::cout << "Enter a valid index: ";
        } else break;
    }
    return make_pair(m - 1, n - 1);
}

int main() {
    setup();
    char player = '@';
    while (filledBoxes != 100) {
        printgrid();
        pair < int, int > p = input(player);
        bfs(p.first, p.second, player);
        player = (player == '@' ? '#' : '@');
    }
    if (score['@'] > score['#']) {
        cout << "Player @ won." << endl;
    } else if (score['@'] < score['#']) {
        cout << "Player # won." << endl;
    } else std::cout << "We got a tie." << endl;
}
