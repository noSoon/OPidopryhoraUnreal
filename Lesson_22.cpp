#include <iostream>
#include <vector>

class CharacterCharacteristics{
    private:
        int strength;
        int intelligence;
        int agility;
    public:
        CharacterCharacteristics(int Strength, int Intelligence, int Agility) :
        strength(Strength), intelligence(Intelligence), agility(Agility) {}

        void modifyStrength(int delta){
            this->strength += delta;
        }

        void modifyIntelligence(int delta){
            this->intelligence += delta;
        }
        
        void modifyAgility(int delta){
            this->agility += delta;
        }

        int getStrength() {
            return strength;
        }

        int getIntelligence() {
            return intelligence;
        }

        int getAgility() {
            return agility;
        }
};

class WeaponCharacteristics{
    private:
        float damage;
        float cooldown;
    public:
        WeaponCharacteristics(float Damage, float Cooldown) :
        damage(Damage), cooldown(Cooldown) {}

        float getDamage() {
            return damage;
        }

        float getCooldown(){
            return cooldown;
        }
};

class Icon{
    private:
        std::string name;
    public:
        Icon(std::string Name) :
        name(Name) {}

        std::string getName(){
            return name;
        }
};

class Weapon {
    private:
        WeaponCharacteristics characteristics;
        Icon icon;
    public:
        Weapon(WeaponCharacteristics Characteristics, Icon WeaponIcon) :
        characteristics(Characteristics), icon(WeaponIcon) {}

        void printInfo(){
            std::cout << "Weapon Name: " << icon.getName() << std::endl;
            std::cout << "Weapon Damage: " << characteristics.getDamage() << std::endl;
            std::cout << "Weapon Cooldown: " << characteristics.getCooldown() << std::endl;
        }
    
};

class PassiveObject{
    private:
        int modifiers[3];
        Icon icon;
    public:
        PassiveObject(int Modifiers[3], Icon ObjectIcon) :
        icon(ObjectIcon) {
            for (int i = 0; i < 3; i++){
                modifiers[i] = Modifiers[i];
            }
        }

        void applyModifier(CharacterCharacteristics &appliedCharacteristics){
            appliedCharacteristics.modifyStrength(modifiers[0]);
            appliedCharacteristics.modifyIntelligence(modifiers[1]);
            appliedCharacteristics.modifyAgility(modifiers[2]);
        }

        void printInfo(){
            std::cout << "Passive Object Name: " << icon.getName() << std::endl;
            std::cout << "Passive Object Modifiers - Strength: " << modifiers[0] << std::endl;
            std::cout << "Passive Object Modifiers - Intelligence: " << modifiers[1] << std::endl;
            std::cout << "Passive Object Modifiers - Agility: " << modifiers[2] << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
};

class Character {
    private:
        int health;
        CharacterCharacteristics characteristics;
        Weapon weapon;
        std::vector<PassiveObject> objects;
    public:
        Character(int Health, CharacterCharacteristics Characteristics, Weapon CharacterWeapon, std::vector<PassiveObject> Objects) :
        health(Health), characteristics(Characteristics), weapon(CharacterWeapon), objects(Objects) 
        {
            for (auto &object : objects) {
                object.applyModifier(characteristics);
            }
        }

        void printInfo(){
            std::cout << "Character Health: " << health << std::endl;
            std::cout << "Character Strength: " << characteristics.getStrength() << std::endl;
            std::cout << "Character Intelligence: " << characteristics.getIntelligence() << std::endl;
            std::cout << "Character Agility: " << characteristics.getAgility() << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "Weapon Info: " << std::endl;
            weapon.printInfo();
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "Passive Objects Info: " << std::endl;
            std::cout << "Number of Passive Objects: " << objects.size() << std::endl;
            for (int i = 0; i < objects.size(); i++) {
                objects[i].printInfo();
            }
        }
};


int main(){

    CharacterCharacteristics characterCharacteristics(20, 5, 15);
    WeaponCharacteristics weaponCharacteristics(35.0f, 1.5f);
    Icon weaponIcon("Sword");
    Weapon sword(weaponCharacteristics, weaponIcon);
    int modifiers_boots[3] = {0, 0, 5};
    Icon bootsIcon("Boots");
    PassiveObject boots(modifiers_boots, bootsIcon);
    int modifiers_helmet[3] = {3, 1, -2};
    Icon helmetIcon("Helmet");
    PassiveObject helmet(modifiers_helmet, helmetIcon);
    int modifiers_amulet[3] = {1, 5, -1};
    Icon amuletIcon("Amulet");
    PassiveObject amulet(modifiers_amulet, amuletIcon);
    std::vector<PassiveObject> passiveObjects = {boots, helmet, amulet};
    Character hero(100, characterCharacteristics, sword, passiveObjects);
    hero.printInfo();

    return 0;
}
