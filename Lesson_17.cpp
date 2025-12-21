#include <iostream>
#include <vector>

using namespace std;

struct Player{

    string name;
    float health;

};

std::vector<Player> addPlayers();

void takeDamage(std::vector<Player> &playerList);

std::vector<Player> findMax(const std::vector<Player> playerList);

std::vector<Player> findMin(const std::vector<Player> playerList);

std::vector<Player> findDead(const std::vector<Player> playerList);

void menuInterface(const std::vector<Player> list);

void menuRender();

int main() {

    std::vector<Player> list = addPlayers();

    takeDamage(list);

    menuInterface(list);

    return 0;
}

std::vector<Player> addPlayers(){

    int num;

    std::vector<Player> playersList;


    cout << "Add number of players: ";
    cin >> num;

    for (int i = 0; i < num; ++i){
        Player player;
        cout << "Enter name of the character #" << i+1 << "\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, player.name);
        cout << "Enter character #" << i+1 << " health value" << "\n";
        cin >> player.health;
        playersList.push_back(player);
    }

    return playersList;

}

void takeDamage(std::vector<Player> &playerList){

    float damageValue;

    cout << "How much damage do you want to apply?" << "\n";
    cin >> damageValue;

    for (int i = 0; i < playerList.size(); ++i){
        playerList[i].health -= damageValue;
    }

}

std::vector<Player> findMax(const std::vector<Player> playerList){

    std::vector<Player> result;
    float maxHealth = playerList[0].health;

    for (int i = 0; i < playerList.size(); ++i){
        if (playerList[i].health > maxHealth){
            maxHealth = playerList[i].health;
            result.clear();
            result.push_back(playerList[i]);
        } else if (playerList[i].health == maxHealth){
            result.push_back(playerList[i]);
        }
    }
    return result;

}

std::vector<Player> findMin(const std::vector<Player> playerList){

    std::vector<Player> result;
    float minHealth = playerList[0].health;

    for (int i = 0; i < playerList.size(); ++i){
        if (playerList[i].health < minHealth && playerList[i].health > 0){
            minHealth = playerList[i].health;
            result.clear();
            result.push_back(playerList[i]);
        } else if (playerList[i].health == minHealth){
            result.push_back(playerList[i]);
        }
    }
    return result;

}

std::vector<Player> findDead(const std::vector<Player> playerList){

    std::vector<Player> result;

    for (int i = 0; i < playerList.size(); i++){
        if (playerList[i].health < 0){
            result.push_back(playerList[i]);
        }
        
    }
    
    return result;

}

void menuInterface(const std::vector<Player> list){
    cout << "What statistics do you want to see?" << "\n";
    menuRender();

    int choice;

    do{
        cin >> choice;

        switch (choice){
            case 1:{
                std::vector<Player> maxHealthList = findMax(list);
                for (auto &player : maxHealthList){
                    cout << player.name << " - " << player.health << "\n";
                }
                menuRender();
                break;
            }
            case 2: {
                std::vector<Player> minHealthList = findMin(list);
                for (auto &player : minHealthList){
                    cout << player.name << " - " << player.health << "\n";
                }
                menuRender();
                break;
            }
            case 3: {
                std::vector<Player> deadPlayersList = findDead(list);
                for (auto &player : deadPlayersList){
                    cout << player.name << "\n";
                }
                menuRender();
                break;
            }
            case 9:
                cout << "Goodbye!";
                break;
            default:
                menuRender();
                break;
        }
    } while(choice != 9);
}

void menuRender(){
    cout << "----------------------------------" << "\n";
    cout << "1. What player(s) has most Health?" << "\n";
    cout << "2. What player(s) has least Health?" << "\n";
    cout << "3. What player(s) are dead?" << "\n";
    cout << "9. Exit" << "\n";
}