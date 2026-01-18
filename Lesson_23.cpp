#include <iostream>
#include <vector>
#include <memory>

class CharacterCharacteristics{
    private:
        int strength;
        int intelligence;
        int agility;
        int speed;
    public:
        CharacterCharacteristics(int Strength, int Intelligence, int Agility, int Speed) :
        strength(Strength), intelligence(Intelligence), agility(Agility), speed(Speed) {}

        void modifyStrength(int delta){
            this->strength += delta;
        }

        void modifyIntelligence(int delta){
            this->intelligence += delta;
        }
        
        void modifyAgility(int delta){
            this->agility += delta;
        }

        void modifySpeed(int delta){
            this->speed += delta;
        }
        
        void setSpeed(int s){
            speed = s;
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

        int getSpeed(){
            return speed;
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
    PassiveObject(const int Modifiers[3], const Icon &ObjectIcon)
        : icon(ObjectIcon)
    {
        for (int i = 0; i < 3; i++)
            modifiers[i] = Modifiers[i];
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

class SpeedObject{
    private:
        int speedModifier;
        Icon icon;
    public:
        SpeedObject(int Modifier, Icon ObjectIcon) : 
        speedModifier(Modifier), icon(ObjectIcon) {}

        void applySpeedModifier(CharacterCharacteristics &speedCharacteristic){
            speedCharacteristic.modifySpeed(speedModifier);
        }

        int getModifier(){
            return speedModifier;
        }

        void printObjectInfo(){
            std::cout << "Speed Object Name: " << icon.getName() << std::endl;
            std::cout << "Speed Modifier: +" << getModifier() << std::endl;
        }
};

class Character {
    private:
        int health;
        int baseSpeed;
        CharacterCharacteristics characteristics;
        Weapon weapon;
        std::vector<std::unique_ptr<PassiveObject>> objects;
        std::vector<std::unique_ptr<SpeedObject>> speedObjects;
    public:
        Character(int Health, CharacterCharacteristics Characteristics, Weapon CharacterWeapon)
        : health(Health), characteristics(Characteristics), weapon(CharacterWeapon) 
        {
            baseSpeed = characteristics.getSpeed();
        }

        void calculateSpeed(){
            int totalSpeed = baseSpeed;
            for(auto &obj : speedObjects){
                totalSpeed += obj->getModifier();
            }
            characteristics.setSpeed(totalSpeed);
        }

        void addItem(std::unique_ptr<PassiveObject> object){
            object->applyModifier(characteristics);
            objects.push_back(std::move(object));
        }

        void addSpeedItem(std::unique_ptr<SpeedObject> speedObj){
            speedObjects.push_back(std::move(speedObj));
            calculateSpeed();
        }
        
        void removeSpeedItem(int index){
            if(index >=0 && index < speedObjects.size()){
                speedObjects.erase(speedObjects.begin() + index);
                calculateSpeed();
            }
        }

        void printInfo(){
            std::cout << "Character Health: " << health << std::endl;
            std::cout << "Character Strength: " << characteristics.getStrength() << std::endl;
            std::cout << "Character Intelligence: " << characteristics.getIntelligence() << std::endl;
            std::cout << "Character Agility: " << characteristics.getAgility() << std::endl;
            std::cout << "Character Base Speed: " << baseSpeed << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "Weapon Info: " << std::endl;
            weapon.printInfo();
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "Passive Objects Info: " << std::endl;
            std::cout << "Number of Passive Objects: " << objects.size() << std::endl;
            for (int i = 0; i < objects.size(); i++) {
                objects[i]->printInfo();
            }
            std::cout << "Total Speed: " << characteristics.getSpeed() << std::endl;
            std::cout << "Speed Objects Info: " << std::endl;
            std::cout << "Number of Speed Objects: " << speedObjects.size() << std::endl;
            for (int i = 0; i < speedObjects.size(); i++) {
                speedObjects[i]->printObjectInfo();
            }
        }
};


int main() {
    CharacterCharacteristics charStats(20,5,15,10);
    Weapon sword(WeaponCharacteristics(35.0f,1.5f), Icon("Sword"));
    Character hero(100, charStats, sword);
    int coatMods[3] = {0,0,5};
    hero.addItem(std::make_unique<PassiveObject>(coatMods, Icon("Coat")));
    int helmetMods[3] = {3,1,-2};
    hero.addItem(std::make_unique<PassiveObject>(helmetMods, Icon("Helmet")));
    int amuletMods[3] = {1,5,-1};
    hero.addItem(std::make_unique<PassiveObject>(amuletMods, Icon("Amulet")));
    hero.addSpeedItem(std::make_unique<SpeedObject>(5, Icon("Speed Boots")));
    hero.addSpeedItem(std::make_unique<SpeedObject>(3, Icon("Speed Potion")));
    hero.printInfo();
    std::cout << "\n--Removing first speed object--\n" << std::endl;
    hero.removeSpeedItem(0);
    hero.printInfo();
    return 0;
}

