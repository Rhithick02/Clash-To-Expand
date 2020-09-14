#include <iostream>
#include <map>
using namespace std;

struct node{
    int density;
    char owner;
};

node grid[10][10];
int filledBoxes;
map<char,int> score;
void setup(){
    filledBoxes = 0;
    score['@'] = 0;
    score['#'] = 0;
    for (int i = 0 ; i < 10; i++) {
        for (int j = 0 ; j < 10; j++) {
            grid[i][j].density = 0;
            grid[i][j].owner = ' ';
        }
    }
}

void printgrid(){
    system("clear");
    for (size_t i = 0 ; i < 53; i++) {
        cout<<"# ";
    }
    cout<<endl;
    cout<<"#  ";
    for (int i = 0 ; i < 10; i++) {
        cout<<" ---"<<i+1<<"---- ";
    }
    cout<<" #"<<endl;
    for (int i = 0 ; i < 10; i++) {
        cout<<"#";
        if (i!=9) {
            cout<<' ';
        }
        std::cout <<i+1<<' ';
        for (int j = 0 ; j < 10; j++) {
            cout<<"( "<<grid[i][j].owner<<", ";
            if (grid[i][j].density != 0) {
                cout<<grid[i][j].density<<" )  ";
            }
            else cout<<"  )  ";
        }
        cout<<" #"<<endl;
    }
    for (size_t i = 0 ; i < 53; i++) {
        cout<<"# ";
    }
    cout<<endl;
}

bool isexplode(int row,int col){
    if ((row == 0 and col == 0) ||
        (row == 9 and col == 0) ||
        (row == 0 and col == 9) ||
        (row == 9 and col == 9)) {
        if (grid[row][col].density == 1) {
            return true;
        }
    }
    else if (row == 0 || row == 9 || col == 0 || col == 9) {
        if (grid[row][col].density == 2) {
            return true;
        }
    }
    else if (grid[row][col].density == 3) {
        return true;
    }
    return false;
}

void explode(int row,int col,char own){
    if (isexplode(row, col)) {
        // logic
        int dx[] = {0,1,0,-1};
        int dy[] = {1,0,-1,0};
        grid[row][col].owner = ' ';
        grid[row][col].density = 0;
        filledBoxes--;
        score[own]--;
        for (int i = 0 ; i < 4; i++) {
            int rr = row + dx[i];
            int cl = col + dy[i];
            if (rr < 0 || rr > 9 || cl < 0 || cl > 9) {
                continue;
            }
            explode(rr, cl, own);
        }
    } else {
        if (grid[row][col].density == 0) {
            filledBoxes++;
            score[own]++;
        }
        grid[row][col].density ++;
        grid[row][col].owner = own;
    }
}

pair<int, int> input(char player){
    int m,n;
    cout<<"player: "<<player<<" enter the index ";
    char secplayer = (player == '@' ? '#' : '@');
    while (true) {
        cin>>m>>n;
        if (grid[m][n].owner == secplayer) {
            std::cout << "enter a valid index: ";
        } else break;
    }
    return make_pair(m, n);
}

int main(){
    setup();
    char player = '@';
    while (filledBoxes != 100) {
        printgrid();
        pair<int, int> p = input(player);
        explode(p.first,p.second,player);
        player = (player == '@' ? '#' : '@');
    }
    if (score['@'] > score['#']) {
        cout<<"player @ won."<<endl;
    } else if (score['@'] < score['#']) {
        cout<<"player # won."<<endl;
    } else std::cout << "we got a tie." << endl;
}

