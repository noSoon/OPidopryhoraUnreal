#include <iostream>
#include <vector>

using namespace std;

void cinValidation();

int main(){

    string name;
    float health;
    vector<string> heroClasses = {"Mage","Warrior","Archer"};
    int heroClassOption;

    cout << "What is your name: ";
    getline(cin, name);
    cout << "Your health: ";
    while (!(cin >> health) || health <= 0 || health > 100) {
        cinValidation();
    }
    cout << "Available hero classes: " << "\n";
    int heroNumber = 1;
    for (string& heroClass : heroClasses){
        cout << heroNumber << ". " << heroClass << "\n";
        ++heroNumber;
    }
    cout << "Choose your class: ";
    while (!(cin >> heroClassOption) || heroClassOption != 1 && heroClassOption != 2 && heroClassOption != 3) {
        cinValidation();
    }

    cout << "Your character info:" << "\n";
    cout << "Name: " << name << "\n";
    cout << "Health: " << health << "\n";
    cout << "Hero class: " << heroClasses[heroClassOption-1];

    return 0;
}

void cinValidation(){
    cout << "Invalid number. Please try again: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}