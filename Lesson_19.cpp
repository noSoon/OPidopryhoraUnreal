#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Character{
    string name;
    float health;
    pair<int,int> location;
    bool wasDamaged = false;

    Character(string Name, float Health, int x, int y):
    name(Name), health(Health), location{x,y} {}
};

struct Meteor{
    pair<int,int> location;
    float damage;
    float strength;

    Meteor(int x, int y, float Damage, float Strength):
    location{x,y}, damage(Damage), strength(Strength) {}
};

void addCharacters(vector<Character> &characterList, int characterNumber);

Meteor createMeteor();

float calculateDistance(const Meteor &meteor, const Character &character);

void dealDamage(const Meteor &meteor, vector<Character> &characterList);

vector<Character> findDead(const vector<Character>& characterList);

void showDamagedCharacters(const vector<Character>& characterList);

int main(){

    int num;

    vector<Character> characterList;

    cout << "How many characters you want to add?: ";
    cin >> num;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    addCharacters(characterList, num);

    Meteor meteor = createMeteor();

    dealDamage(meteor, characterList);

    cout << "Damaged characters: " << "\n";
    showDamagedCharacters(characterList);

    vector<Character> deadList = findDead(characterList);
    cout << "Dead characters: " << "\n";
    for (const auto& ch : deadList){
        cout << ch.name << "\n";
    }

    return 0;
}

void addCharacters(vector<Character> &characterList, int characterNumber){
    string name;
    float health;
    int x,y;
    for (int i = 0; i<characterNumber; ++i){

        cout << "Adding character #" << i+1 << "\n";
        cout << "Name: ";
        getline(cin, name);
        cout << "Health: ";
        cin >> health;
        cout << "Location: " << "\n";
        cout << "X: ";
        cin >> x;
        cout << "Y: ";
        cin >> y;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        characterList.push_back(Character(name,health,x,y));
    }
}

Meteor createMeteor(){
    int x,y;
    float damage;
    float strength;

    cout << "Meteor location:" << "\n";
    cout << "X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;
    cout << "Meteor damage: ";
    cin >> damage;
    cout << "Meteor strength: ";
    cin >> strength;

    return Meteor(x,y,damage,strength);
}

float calculateDistance(const Meteor &meteor, const Character &character){
    return sqrt(pow(character.location.first-meteor.location.first,2)+pow(character.location.second-meteor.location.second,2));
}

void dealDamage(const Meteor &meteor, vector<Character> &characterList){
    float area = meteor.strength * 3;

    for (int i = 0; i < characterList.size(); ++i){
        if(area >= calculateDistance(meteor,characterList[i])){
            characterList[i].health -= meteor.damage;
            characterList[i].wasDamaged = true;
        }
    }
}

vector<Character> findDead(const vector<Character>& characterList){

    vector<Character> result;

    for (int i = 0; i < characterList.size(); i++){
        if (characterList[i].health < 0){
            result.push_back(characterList[i]);
        }
    }
    
    return result;

}

void showDamagedCharacters(const vector<Character>& characterList){
    for (auto ch : characterList){
        if (ch.wasDamaged && ch.health > 0){
            cout << ch.name << " was damaged, health now is: " << ch.health << "\n";
        }
    }
}