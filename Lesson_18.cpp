#include <iostream>
#include <map>

using namespace std;

// 1.

void addTroops(std::map<int,int> &troops, int num);

std::pair<int, int> findMax(const std::map<int,int> &troops);

std::pair<int, int> findMin(const std::map<int,int> &troops);

void displayStats(const std::map<int,int> &troops);

// 2.

void movePlayer(std::pair<int,int> &p, int num);

int main(){

    // 1.
    
    std::map<int, int> troops;
    int num;

    cout << "Enter how many types of troops you want:" << "\n";

    cin >> num;

    addTroops(troops, num);

    cout << "Your troops:" << "\n";
    
    for (auto &p : troops){
        cout << p.first << '-' << p.second << "\n";
    }

    displayStats(troops);

    cout << "-------------------------------------------------" << "\n";

    // 2.

    std::pair<int, int> coordinates = std::make_pair(0,0);

    cout << "Enter how many moves you want to make:" << "\n";

    cin >> num;

    movePlayer(coordinates, num);

    cout << "New coordinates:" << "\n";

    cout << "X: " << coordinates.first << "\n";

    cout << "Y: " << coordinates.second << "\n";

    return 0;
}


void addTroops(std::map<int,int> &troops, int num){

    int type;
    int amount;

    for (int i = 0; i < num; ++i){
        cout << "Type: ";
        cin >> type;
        cout << "Amount: ";
        cin >> amount;
        troops.emplace(type,amount);
    }

}

std::pair<int, int> findMax(const std::map<int,int> &troops){

    std::pair<int, int> res = std::make_pair(0,0);

    for (auto currentPair = troops.begin(); currentPair != troops.end(); ++currentPair){
       if (currentPair->second > res.second){
            res = std::make_pair(
                currentPair->first,
                currentPair->second
            );
       }
    }

    return res;
}

std::pair<int, int> findMin(const std::map<int,int> &troops){

    std::pair<int, int> res = std::make_pair(troops.begin()->first,troops.begin()->second);

    for (auto currentPair = troops.begin(); currentPair != troops.end(); ++currentPair){
       if (currentPair->second < res.second){
            res = std::make_pair(
                currentPair->first,
                currentPair->second
            );
       }
    }

    return res;
}

void displayStats(const std::map<int,int> &troops){

    std::pair<int, int> maxPair = findMax(troops);

    cout << "Maximal unit:" << "\n";

    cout << "Type: " << maxPair.first << "\n";

    cout << "Amount: " << maxPair.second << "\n";

    cout << "------------------------------------" << "\n";

    std::pair<int, int> minPair = findMin(troops);

    cout << "Minimal unit:" << "\n";

    cout << "Type: " << minPair.first << "\n";

    cout << "Amount: " << minPair.second << "\n";

}

void movePlayer(std::pair<int,int> &p, int num){

    std::map<string, std::pair<int,int>> moves = {
        {"left", {-1,0}},
        {"right", {1,0}},
        {"up", {0,1}},
        {"down", {0,-1}},
    };
    string move;

    for (int i = 0; i < num; ++i){
        cout << "Enter your move: ";
        cin >> move;
        if (moves.find(move) != moves.end()){
            p.first += moves[move].first;
            p.second += moves[move].second;
        }
    }

}