#include <iostream>
#include <map>

using namespace std;

class Character{
    public:
    Character(string Name, int x, int y, int Speed) :
    name(Name), location{x,y}, speed(Speed) {}

    void move(int x, int y){
        location.first += x * speed;
        location.second += y * speed;
    }

    void printInfo() const{
        cout << "Character - " << name << " new location:" << "\n";
        cout << "X:" << location.first << " Y:" << location.second;
    }

    string getName() const {
        return name;
    }

    pair<int,int> getLocation() const {
        return location;
    }

    private:
        string name;
        pair<int,int> location;
        int speed;
};

void createCharacterMap(map<int,Character> &characters, int num);

void moveCharacter(map<int,Character> &characters);

int main(){

    map<int, Character> characters;

    int num;

    cout << "How many characters do you want to create? - ";
    cin >> num;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    createCharacterMap(characters, num);

    moveCharacter(characters);



    return 0;
}

void createCharacterMap(map<int,Character> &characters, int num){
    string name;
    int x,y;
    int speed;

    for(int i=0; i<num; ++i){
        cout << "Adding character #" << i+1 << "\n";
        cout << "Name: ";
        getline(cin, name);
        cout << "Location: " << "\n";
        cout << "X: ";
        cin >> x;
        cout << "Y: ";
        cin >> y;
        cout << "Speed: ";
        cin >> speed;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        characters.emplace(i+1,Character(name, x, y, speed));
    }
}

void moveCharacter(map<int,Character> &characters){
    int characterNum, actionNum;
    int x,y;
    cout << "List of characters:" << "\n";
    for (const auto &ch : characters){
        cout << '#' << ch.first << '-' << ch.second.getName() << "\n";
        cout << "Location: " << "\n";
        cout << "X:" << ch.second.getLocation().first 
             << " Y:" << ch.second.getLocation().second;
        cout << endl;
    }
    cout << "Choose the character (write its number): ";
    cin >> characterNum;
    cout << "How many moves do you want to do?" << "\n";
    cin >> actionNum;

    auto it = characters.find(characterNum);
    if (it!=characters.end()){
        for (int i = 0; i < actionNum; ++i){
            cout << "Please insert vector of movement: " << "\n";
            cout << "X: ", cin >> x;
            cout << "Y: ", cin >> y;
            it->second.move(x,y);
        }
        it->second.printInfo();
    }
    else {
        cout << "Character wasn't found";
    }

}