#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

class Superheroes {
protected:
    std::string name;
    int age;

public:
    Superheroes(const std::string& name, int age) : name(name), age(age) {}
};

class Iron_Man_Suit {
private:
    std::string name;

public:
    Iron_Man_Suit(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }
};

int randomIntFromInterval(int min, int max) {
    static std::mt19937 generator(std::time(0));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

class Iron_Man : public Superheroes {
private:
    std::vector<std::string> unlockedSuits;
    std::vector<std::pair<std::string, std::string>> allSuits;

public:
    Iron_Man(const std::string& name, int age) : Superheroes(name, age) {
        allSuits = {
            {"Mark L (50)", "2017-2018"},
            {"Mark LXXXV (85)", "2018-2023"},
            {"Mark XLIV (44)", "2014-2015"},
            {"Mark VII (7)", "2012"},
            {"Mark XLII (42)", "2014-2015"},
            {"Mark XLVI (46)", "2015-2016"},
            {"Mark III (3)", "2008"},
            {"Mark IV (4)", "2008-2010"},
            {"Mark VI (6)", "2010"}
        };
    }

    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void getArmor() {
        if (unlockedSuits.size() >= allSuits.size()) {
            std::cout << "You've unlocked all the suits! Congratulations!" << std::endl;
            return;
        }

        std::pair<std::string, std::string> suit;
        do {
            int x = randomIntFromInterval(0, allSuits.size() - 1);
            suit = allSuits[x];
        } while (std::find(unlockedSuits.begin(), unlockedSuits.end(), suit.first) != unlockedSuits.end());

        std::cout << "CONGRATULATIONS, YOU GOT THE " << suit.first << " WHICH WAS USED / MADE IN " << suit.second << std::endl;
        unlockedSuits.push_back(suit.first);
    }

    void showIndex() const {
        int totalSuits = allSuits.size();
        int unlockedCount = unlockedSuits.size();
        int missingCount = totalSuits - unlockedCount;

        std::cout << "You have unlocked " << unlockedCount << " out of " << totalSuits << " suits." << std::endl;
        std::cout << "You are missing " << missingCount << " suits." << std::endl;
    }
};

int main() {
    Iron_Man ironman("Tony Stark", 8);

    std::string answer;
    bool validResponse = false;

    while (!validResponse) {
        std::cout << "Welcome! Would you like to gamble for some Iron Man suits? (HELL YEAH or no) ";
        std::getline(std::cin, answer);
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        if (answer == "hell yeah") {
            std::cout << "Hope you get one you like!" << std::endl;
            ironman.getArmor();
            validResponse = true;
        }
        else if (answer == "no") {
            std::cout << "Then why did you even come here?????" << std::endl;
            validResponse = true;
        }
        else {
            std::cout << "Please answer with HELL YEAH or no." << std::endl;
        }
    }

    bool continueRolling = true;

    while (continueRolling && answer == "hell yeah") {
        std::string answer1;
        std::cout << "Do you want to roll for another suit, or check your index? (roll/index/no) ";
        std::getline(std::cin, answer1);
        std::transform(answer1.begin(), answer1.end(), answer1.begin(), ::tolower);

        if (answer1 == "roll") {
            std::cout << "Great! Attaboy!" << std::endl;
            ironman.getArmor();
        }
        else if (answer1 == "index") {
            ironman.showIndex();
        }
        else if (answer1 == "no") {
            std::cout << "What if you hit big??? Fine, goodbye... exiting..." << std::endl;
            continueRolling = false;
        }
        else {
            std::cout << "Please answer with 'roll', 'index', or 'no'." << std::endl;
        }
    }

    return 0;
}