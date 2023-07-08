//--------HANGMAN--------//
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <random>

using namespace std;

vector<string> hangmanArt = {
    "         +---+\n",
    "             |\n",
    "             |\n",
    "           \  |\n",
    "           \  |\n",
    "             |\n",
    "       =======\n",
};
//--------Overlay class used for printing general game overlay--------//
class Overlay{
private:
    int PrintedCounter;
    string Word;
    char choice;
public:
    Overlay(): PrintedCounter(0), choice(0){}
    void operator *() {
        cout << "  _    _                                          " << endl;
        cout << " | |  | |                                         " << endl;
        cout << " | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __   " << endl;
        cout << " |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\  " << endl;
        cout << " | |  | | (_| | | | | (_| | | | | | | (_| | | | | " << endl;
        cout << " |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_| " << endl;
        cout << "                      __/ |                       " << endl;
        cout << "                     |___/                        " << endl;
        cout << endl;
        cout << setw(31) << "Press ENTER to continue "; cin.get();
        system("cls");
        cout << setw(45) << endl << "This is how HANGMAN should NOT look like" << endl;
        cout << setw(28) << endl << "  +---+\n";
        cout << setw(28) << "  |   |\n";
        cout << setw(28) << "  O   |\n";
        cout << setw(28) << " /|\\  |\n";
        cout << setw(28) << " / \\  |\n";
        cout << setw(28) << "      |\n";
        cout << setw(28) << "=======\n";
        cout << setw(29) << "Press ENTER to continue "; cin.get();
        system("cls");
        cout << setw(30) << "Choose level" << endl;
        cout << endl << setw(10) << "Level 1" << setw(18) << "Level 2" << setw(18) << "Level 3" << endl;
    }
    bool PrintWord(const string& word, char letter, int wrongCounter) {
        bool guessed;

        for (const char& character : word) {
            guessed = false;
            if (character == letter) {
                Word += character;
                guessed = true;
                PrintedCounter++;
            }
            if (guessed || Word.find(character) != string::npos) {
                cout << character;
            }
            else {
                cout << "_";
            }
        }
        cout << endl;

        if (PrintedCounter < word.length() && wrongCounter < 7) return true;
        else return false;
    }
    void RefreshGuessedHuman(const string& word, char letter, char level, int wrongCounter) {
        system("cls");
        cout << endl << setw(11) << "Level " << level << endl;
        cout << setw(15) << endl << "Your HANGMAN" << endl;
        cout << endl;
        for (const auto& line : hangmanArt) {
            cout << line;
        }
        cout << endl << setw(8);
    }
    void RefreshWrongHuman(const string& word, char letter, int wrongCounter, char level) {
        system("cls");
        cout << endl << setw(11) << "Level " << level << endl;
        cout << setw(15) << endl << "Your HANGMAN" << endl;
        cout << endl;
        if (wrongCounter == 1) {
            hangmanArt[1] = "           | |\n";
        }
        else if (wrongCounter == 2) {
            hangmanArt[2] = "           O |\n";
        }
        else if (wrongCounter == 3) {
            hangmanArt[3] = "          /  |\n";
        }
        else if (wrongCounter == 4) {
            hangmanArt[3] = "          /|\ |\n";
        }
        else if (wrongCounter == 5) {
            hangmanArt[3] = "          /|\\|\n";
        }
        else if (wrongCounter == 6) {
            hangmanArt[4] = "          /  |\n";
        }
        else if (wrongCounter == 7) {
            hangmanArt[4] = "          / \\|\n";
        }
        for (const auto& line : hangmanArt) {
            cout << line;
        }
        cout << endl << setw(8);
    }
    bool Exit(const string& word, int wrongCounter) {
        if (PrintedCounter == word.length()) {
            cout << endl << setw(42) << "CONGRATULATIONS YOU HAVE WON THE GAME!\n";
            cout << setw(13) << "ACCURACY: " << fixed << setprecision(0) << (double)(word.length()) / (word.length() + wrongCounter) * 100 << "%\n";
            cout << endl;
            cout << setw(48) << "Do you wish to (R)estart the Game or (E)xit? "; cin >> choice;

            if (choice == 'r' || choice == 'R') {
                PrintedCounter = 0;
                Word = "";
                choice = 0;
                return true;
            }
            else {
                exit(1);
                return false;
            }
        }
        else {
            cout << endl << setw(22) << "GAME OVER: YOU LOST\n";
            cout << setw(17) << "The word was - " << word << endl;
            cout << setw(47) << endl << "Do you wish to (R)estart the Game or (E)xit? "; cin >> choice;

            if (choice == 'r' || choice == 'R') {
                PrintedCounter = 0;
                Word = "";
                choice = 0;
                return true;
            }
            else {
                exit(1);
                return false;
            }
        }
    }
};

//--------Game class pure abstract class used for reading level number, generating random index for word, and assinging words to map--------//
class Game{
protected:
    char level;
    int index;
    map<int, string> level1; map<int, string> level2; map<int, string> level3;
    map<char, map<int, string>> levels;
public:
    Game(): level(0), index(0){}
    virtual ~Game(){}
    
    void Level() {
        cout << endl << setw(17) << "Level number: "; cin >> level;
        //Level 1 words 4 letters
        level1[0] = "book"; level1[1] = "exit"; level1[2] = "fish"; level1[3] = "gift"; level1[4] = "hill"; level1[5] = "idea"; level1[6] = "lamp";
        level1[7] = "moon"; level1[8] = "quiz"; level1[9] = "tree";
        //Level 2 words 6 letters
        level2[0] = "animal"; level2[1] = "banner"; level2[2] = "castle"; level2[3] = "danger"; level2[4] = "expert"; level2[5] = "family"; level2[6] = "garden";
        level2[7] = "island"; level2[8] = "laptop"; level2[9] = "planet";
        //Level 3 words 8 letters
        level3[0] = "balloon"; level3[1] = "cabinet"; level3[2] = "diamond"; level3[3] = "elephant"; level3[4] = "festival"; level3[5] = "keyboard"; level3[6] = "question";
        level3[7] = "umbrella"; level3[8] = "hospital"; level3[9] = "mountain";
        levels['1'] = level1;
        levels['2'] = level2;
        levels['3'] = level3;
    }
    void IndexGenerator() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 9);
        index = dis(gen);
    }
    void LevelPrint() {
        system("cls");
        if (level != '1' && level != '2' && level != '3') {
            throw invalid_argument(" wrong input!");
        }
        try {
            if (level == '1')
                cout << endl << setw(11) << "Level 1" << endl;

            else if (level == '2')
                cout << endl << setw(11) << "Level 2" << endl;

            else if (level == '3')
                cout << endl << setw(11) << "Level 3" << endl;
            cout << setw(15) << endl << "Your HANGMAN" << endl;
            cout << endl;
            for (const auto& line : hangmanArt) {
                cout << line;
            }
            if (level == '1')
                cout << endl << setw(11) << "____";
            else if (level == '2')
                cout << endl << setw(13) << "______";
            else if (level == '3')
                cout << endl << setw(15) << "________";
        }
        catch (invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    virtual void LetterCheck() = 0;
    virtual void Play() = 0;
    virtual void Restart() = 0;
};

//--------Human class used for game logic for Human Player(checking for letters in the words)--------//
class Player : public Game {
private:
    char letter;
    int wrongCounter;
    set<char> letterLibrary;
    bool letterFound, restartPlay;
    Game* game;
public:
    Player(): letter(0), wrongCounter(0), letterFound(0), restartPlay(0), game(0){}

    void LetterCheck() override{
        cout << endl;
        do {
            cout << endl << setw(18) << "Enter a letter: "; cin >> letter;
            letterFound = (letterLibrary.count(letter) > 0);

            if(letterFound) cout << setw(26) << "Letter was already used\n" << setw(28) << "Please enter a new letter\n";
        } while (letterFound);

        letterLibrary.insert(letter);
    }

    void Play() override {
        Overlay overlay;
        bool continuePlay = true;

        while(continuePlay){
            LetterCheck();
            auto it = levels.find(level);
            if (it != levels.end()) {
                auto letterIt = it->second.find(index);
                if (letterIt != it->second.end()) {
                    const string& word = letterIt->second;
                    if (find(word.begin(), word.end(), letter) != word.end()) {
                        overlay.RefreshGuessedHuman(word, letter, level, wrongCounter);
                    }
                    else {
                        wrongCounter++;
                        overlay.RefreshWrongHuman(word, letter, wrongCounter, level);
                    }
                    continuePlay = overlay.PrintWord(word, letter, wrongCounter);
                    if (!continuePlay) {
                        restartPlay = overlay.Exit(word, wrongCounter);
                    }
                }
            }
        }
    }

    void Restart() override {
        if (restartPlay) {
            delete game;
            game = new Player();
            hangmanArt = {
    "         +---+\n",
    "             |\n",
    "             |\n",
    "           \  |\n",
    "           \  |\n",
    "             |\n",
    "       =======\n",
            };
            Overlay overlay;
            *overlay;
            game->Level();
            game->IndexGenerator();
            game->LevelPrint();
            game->Play();
            game->Restart();
        }
    }
};


int main() {
    //Introduction to the game
    Overlay overlay;
    *overlay;

    //Human Player essentials
    Player human;
    human.Level();
    human.IndexGenerator();
    human.LevelPrint();
    human.Play();
    human.Restart();
    
    return 0;
}