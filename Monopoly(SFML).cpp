#include<iostream>
#include<string.h>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<map>
#include<conio.h>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <chrono>
#include <thread>

using namespace sf;
using namespace std;

class Player;
class Property;
class Tile;
class Asset;
class Rule;
class GameController {
public:
    static Tile* currentTile;
    static Player* currentPlayer;
    static vector <Rule*> rules;
    static vector<Player*> players;
    static vector <Tile*> board;
    static vector<string> get_rule_txt();
    static void show_diceroll(int roll1, int roll2, int index);
    static void next_turn(int playerIdx, int r1, int r2);
    static void apply_rule(string player, vector<Rule*>Rules);
    static void show_rules(vector<string> ruleTxts);
    static void end_game();
    static int showBoard();
    ~GameController() {}
};

class Rule {
public:
    virtual void apply_rule() {}
    virtual string getTitle() = 0;
    ~Rule() {}
};
class Skip :public Rule {
public:
    void apply_rule() {}
    string getTitle();
    ~Skip() {};
};
class Buy :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~Buy() {}
};
class Rent :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~Rent() {}
};

class GeneralRule :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~GeneralRule() {}
};

class community1 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~community1() {}
};

class community2 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~community2() {}
};


class community3 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~community3() {}
};

class community4 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~community4() {}
};

class community5 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~community5() {}
};

class chance1 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~chance1() {}
};

class chance2 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~chance2() {}
};

class chance3 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~chance3() {}
};

class chance4 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~chance4() {}
};

class chance5 :public Rule {
public:
    void apply_rule();
    string getTitle();
    ~chance5() {}
};

class JailRule :public Rule {
private:
    static int turns;
    static int no_of_players;
    vector<Player*>players;
public:
    void apply_rule();
    bool check_jail();
    string getTitle();
    ~JailRule() {}
};

class Player {
private:
    string name;
    int balance;
    vector<Tile*>owned;
    int index;
public:
    Player(string name) {
        this->name = name;
        balance = 1500;
        index = 0;
    }
    void change_balance(int sum);
    void edit_index(int i);
    int change_index(int i);
    string get_name();
    int get_index();
    ~Player() {}
};

class Tile {
public:
    virtual vector<Rule*> get_rules() = 0;
    ~Tile() {}
};
class Asset : public Tile {
public:
    virtual int get_price() = 0;
    virtual int get_rent() = 0;
    ~Asset() {}
};

class Eve : public Tile {
};
class CommunityChest :public Eve {
private:
    string name;
    int price;
public:
    CommunityChest(string name) {
        this->name = name;
    }
    vector<Rule*> get_rules();
    ~CommunityChest() {}
};

class Chance :public Eve {
private:
    string name;
    int price;
public:
    Chance(string name) {
        this->name = name;
    }
    vector<Rule*> get_rules();
    ~Chance() {}
};

class JailEvent : public Eve {
private:
    string name;
public:
    JailEvent(string name) {
        this->name = name;
    }
    vector<Rule*> get_rules();
    ~JailEvent() {}
};

class TaxEvent : public Eve {
private:
    string name;
    int tax;
public:
    TaxEvent(string name, int tax) {
        this->tax = tax;
        this->name = name;
    }
    int get_tax();
    vector<Rule*> get_rules();
    ~TaxEvent() {}
};

class Property : public Asset {
private:
    int price;
    int rent;
    string name;
    bool owned;
    Buy buy;
    Player* owner = NULL;
public:
    Property(string name, int price, int rent) {
        this->price = price;
        this->rent = rent;
        this->name = name;
        owned = false;
    }
    vector<Rule*> get_rules();
    int get_rent();
    void assignOwner(Player* player);
    int get_price();
    ~Property() {}
};

class Commodity : public Asset {
private:
    int price;
    string name;
    bool owned;
    Player* owner = NULL;
    int rent;
public:
    Commodity(string name, int price) {
        this->price = price;
        this->name = name;
    }
    vector<Rule*> get_rules();
    int get_price();
    void assignOwner(Player* player);
    int get_rent();
    ~Commodity() {}
};

string Skip::getTitle() {
    return "skip";
}

void Buy::apply_rule() {
    Player* player = GameController::currentPlayer;
    Asset* currentAsset = (Asset*)GameController::currentTile;
    int price = currentAsset->get_price();
    player->change_balance(-price);
}
string Buy::getTitle() {
    return "buy property";
}

void Rent::apply_rule() {
    Player* player = GameController::currentPlayer;
    Asset* currentAsset = (Asset*)GameController::currentTile;
    int rent = currentAsset->get_rent();
    player->change_balance(rent);
}
string Rent::getTitle() {
    return "";
}

void GeneralRule::apply_rule() {
    Player* player = GameController::currentPlayer;
    TaxEvent* currentAsset = (TaxEvent*)GameController::currentTile;
    int tax = currentAsset->get_tax();
    player->change_balance(tax);
}
string GeneralRule::getTitle() {
    return "";
}
void community1::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->edit_index(0);
    player->change_balance(200);
}
string community1::getTitle() {
    return " Advance to Go. (Collect $200) ";
}
void community2::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->change_balance(200);
}
string community2::getTitle() {
    return " Bank error in your favor. (Collect $200) ";
}
void community3::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->change_balance(-50);
}
string community3::getTitle() {
    return " Doctor's fees. {fee} Pay $50 ";
}
void community4::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->change_balance(50);
}
string community4::getTitle() {
    return " From sale of stock you get $50. ";
}

void community5::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->change_balance(100);
}
string community5::getTitle() {
    return " Life insurance matures , Collect $100  ";
}
void chance1::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->edit_index(10);
    player->change_balance(0);
}
string chance1::getTitle() {
    return" Go to Jail. Go directly to Jail. Do not pass GO, do not collect $200. ";
}
void chance2::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->change_balance(-15);
}
string chance2::getTitle() {
    return " Pay Poor Tax of $15 ";
}
void chance3::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->change_balance(-20);
}
string chance3::getTitle() {
    return " �Drunk in charge� fine $20 ";
}
void chance4::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->change_balance(-150);
}
string chance4::getTitle() {
    return " Pay school tax of $150 ";
}
void chance5::apply_rule() {
    Player* player = GameController::currentPlayer;
    player->change_balance(100);
}
string chance5::getTitle() {
    return " our Xmas fund matures. Collect $100 ";
}
void JailRule::apply_rule() {
}
string JailRule::getTitle() {
    return "";
}
bool JailRule::check_jail() {
    return true;
}
int JailRule::turns = 0;
void Player::change_balance(int sum) {
    balance += sum;
}
void Player::edit_index(int i) {
    index = i;
}
int Player::change_index(int i) {
    index += i;
    return index;
}
string Player::get_name() {
    return name;
}
int Player::get_index() {
    return index;
}
vector<Rule*> CommunityChest::get_rules() {
    srand(time(0));
    int random = 3 + rand() % 5;
    vector<Rule*> rules = { GameController::rules[random] };
    return rules;
}

vector<Rule*> Chance::get_rules() {
    srand(time(0));
    int random = 8 + rand() % 5;
    vector<Rule*> rules = { GameController::rules[random] };
    return rules;
}
vector<Rule*>JailEvent::get_rules() {
    vector<Rule*> rules = { GameController::rules[13] };
    return rules;
}
int TaxEvent::get_tax() {
    return tax;
}
vector<Rule*>  TaxEvent::get_rules() {
    vector<Rule*> rules = { GameController::rules[13] };
    return rules;
}
vector<Rule*> Property::get_rules() {
    Player* player = GameController::currentPlayer;
    if (owned) {
        if (player->get_name() == owner->get_name()) {
            vector<Rule*> rules = { GameController::rules[0] };
            return rules;
        }
        else {
            player->change_balance(rent);
            vector<Rule*> rules = { GameController::rules[2] };
            return rules;
        }
    }
    else {
        vector<Rule*>Rules = { GameController::rules[0],GameController::rules[1] };
        return Rules;
    }
}
int Property::get_rent() {
    return rent;
}
void Property::assignOwner(Player* player) {
    owner = player;
    owned = true;
}
int Property::get_price() {
    return price;
}
vector<Rule*> Commodity::get_rules() {
    Player* player = GameController::currentPlayer;
    if (owned) {
        if (player->get_name() == owner->get_name()) {
            vector<Rule*>Rules = { GameController::rules[0] };
            return Rules;
        }
        else {
            srand(time(0));
            int roll1 = 1 + rand() % 6;
            int roll2 = 1 + rand() % 6;
            rent = roll1 + roll2;
            player->change_balance(roll1 + roll2);
            vector<Rule*>rules = { GameController::rules[2] };
            return rules;
        }
    }
    else {
        vector<Rule*>rules;
        rules.push_back(GameController::rules[0]);
        rules.push_back(GameController::rules[1]);
        return rules;
    }
}
int Commodity::get_price() {
    return price;
}
void Commodity::assignOwner(Player* player) {
    owner = player;
    owned = true;
}
int Commodity::get_rent() {
    return rent;
}

Player* GameController::currentPlayer = new Player("green");
Tile* GameController::currentTile = new TaxEvent("GO", 0);

vector<Rule*> GameController::rules = {
    new Skip,
    new Buy,
    new Rent,
    new chance1,
    new chance2,
    new chance3,
    new chance4,
    new chance5,
    new community1,
    new community2,
    new community3,
    new community4,
    new community5,
    new JailRule,
    new GeneralRule
};
vector<Player*> GameController::players = {
    new Player("cyan"),
    new Player("green"),
    new Player("yellow"),
    new Player("red")
};

vector <Tile*> GameController::board = {
    new TaxEvent("GO",150),
    new Property("Mediterranean Avenue", 60, -2),
    new CommunityChest("Community Chest"),
    new Property("Baltic Avenue", 60, -4),
    new TaxEvent("Income Tax", -200),
    new Commodity("Reading Railroad", 200),
    new Property("Oriental Avenue", 100, -6),
    new Chance("Chance"),
    new Property("Vermont Avenue", 100, -6),
    new Property("Connecticut Avenue", 120, -8),
    new JailEvent("Jail (Just Visiting)"),
    new Property("St. Charles Place", 140, -10),
    new Commodity("Electric Company", 150),
    new Property("States Avenue", 140, -10),
    new Property("Virginia Avenue", 160, -12),
    new Commodity("Pennsylvania Railroad", 200),
    new Property("St. James Place", 180, -14),
    new CommunityChest("Community Chest"),
    new Property("Tennessee Avenue", 180, -14),
    new Property("New York Avenue", 200, -16),
    new TaxEvent("Free Parking",0),
    new Property("Kentucky Avenue",220, -18),
    new Chance("Chance"),
    new Property("Indiana Avenue", 220, -18),
    new Property("Illinois Avenue",240, -20),
    new Commodity("B&O Railroad", 200),
    new Property("Atlantic Avenue", 260, -22),
    new Property("Ventnor Avenue", 260, -22),
    new Commodity("Water Works", 150),
    new Property("Marvin Gardens", 280, -24),
    new JailEvent("Go to Jail"),
    new Property("Pacific Avenue", 300, -26),
    new Property("North Carolina Avenue", 300, -26),
    new CommunityChest("Community Chest"),
    new Property("Pennsylvania Avenue", 320, -28),
    new Commodity("Short Line Railroad", 200),
    new Chance("Chance"),
    new Property("Park Place", 350, -35),
    new TaxEvent("Luxury Tax", -100),
    new Property("Boardwalk", 400, -50)
};

vector<string> GameController::get_rule_txt() {
    vector<string> ruleTxts;
    vector<Rule*>rules = currentTile->get_rules();
    for (Rule* rule : rules) {
        ruleTxts.push_back(rule->getTitle());
    }
    return ruleTxts;
}

void GameController::show_diceroll(int roll1, int roll2, int index) {
    cout << "roll 1 : " << roll1 << endl;
    cout << "roll 2 : " << roll2 << endl;
    cout << "current player index : " << index << endl;
}

void GameController::next_turn(int playerIdx, int r1, int r2) {
    srand(time(0));
    currentPlayer = players.at(playerIdx);
    show_diceroll(r1, r2, currentPlayer->change_index(r1+r2));
    currentTile = board[currentPlayer->get_index()];
    vector<string> strArr = get_rule_txt();
    show_rules(strArr);
}

void GameController::apply_rule(string player, vector<Rule*>Rules) {

}

void GameController::show_rules(vector<string> ruleTxts) {
    cout << "rule : " << ruleTxts[0] << "\n";
}

void GameController::end_game() {

}

RectangleShape createTileBox(float x, float y, float w, float h, Color color = Color::Transparent) {
    RectangleShape box({ w, h });
    box.setPosition({ x, y });
    box.setFillColor(color);
    box.setOutlineColor(Color::Red);
    box.setOutlineThickness(2.f);
    return box;
}

int GameController::showBoard() {
    cout << "board has been initialised" << endl;

    // Initialize game state variables
    bool isRolling = false;
    int finalRoll1 = 1, finalRoll2 = 1;
    Clock diceAnimationClock;
    const Time frameDuration = milliseconds(100);
    int windowSize = 1600;
    int tileCountPerSide = 11;
    float tileSize = windowSize / 11;

    RenderWindow window(VideoMode({ 2560, 1600 }), "Monopoly");
    window.setFramerateLimit(60);
    ContextSettings settings;
    settings.antiAliasingLevel = 8;

    // Load textures
    Texture boardTexture, diceTextures[6], playerTextures[4], playerUiTex[4], uirect;
    if (!uirect.loadFromFile("Assets/uirect.png")) {
        cerr << "Failed to load board texture!" << endl;
        return -1;
    }
    
    if (!boardTexture.loadFromFile("Assets/Board.jpg")) {
        cerr << "Failed to load board texture!" << endl;
        return -1;
    }

    for (int i = 0; i < 6; i++) {
        if (!diceTextures[i].loadFromFile("Assets/dice_" + to_string(i + 1) + ".png")) {
            cerr << "Failed to load dice texture " << i + 1 << endl;
            return -1;
        }
        diceTextures[i].setSmooth(true);
    }
    for (int i = 0; i < 4; i++) {
        if (!playerTextures[i].loadFromFile("Assets/p" + to_string(i + 1) + ".png")) {
            cerr << "Failed to load player texture " << i + 1 << endl;
            return -1;
        }
        playerTextures[i].setSmooth(true);
    }
    for (int i = 0; i < 4; i++) {
        if (!playerUiTex[i].loadFromFile("Assets/pfp_" + to_string(i + 1) + ".jpg")) {
            cerr << "Failed to load player texture " << i + 1 << endl;
            return -1;
        }
        playerUiTex[i].setSmooth(true);
    }
    vector<RectangleShape> boxes;
    boxes.push_back(createTileBox(0, 0, 208, 208));
    boxes.push_back(createTileBox(215, 0, 127, 208));
    boxes.push_back(createTileBox(345, 0, 127, 208));
    boxes.push_back(createTileBox(475, 0, 127, 208));
    boxes.push_back(createTileBox(605, 0, 127, 208));
    boxes.push_back(createTileBox(735, 0, 127, 208));
    boxes.push_back(createTileBox(865, 0, 127, 208));
    boxes.push_back(createTileBox(995, 0, 127, 208));
    boxes.push_back(createTileBox(1130, 0, 127, 208));
    boxes.push_back(createTileBox(1260, 0, 127, 208));
    boxes.push_back(createTileBox(1390, 0, 208, 208));

    boxes.push_back(createTileBox(1390, 213, 208, 127));
    boxes.push_back(createTileBox(1390, 345, 208, 127));
    boxes.push_back(createTileBox(1390, 476, 208, 127));
    boxes.push_back(createTileBox(1390, 608, 208, 127));
    boxes.push_back(createTileBox(1390, 740, 208, 127));
    boxes.push_back(createTileBox(1390, 872, 208, 127));
    boxes.push_back(createTileBox(1390, 1004, 208, 127));
    boxes.push_back(createTileBox(1390, 1134, 208, 127));
    boxes.push_back(createTileBox(1390, 1264, 208, 127));
    boxes.push_back(createTileBox(1390, 1395, 208, 208));

    boxes.push_back(createTileBox(0, 1395, 208, 208));
    boxes.push_back(createTileBox(215, 1395, 127, 208));
    boxes.push_back(createTileBox(345, 1395, 127, 208));
    boxes.push_back(createTileBox(475, 1395, 127, 208));
    boxes.push_back(createTileBox(605, 1395, 127, 208));
    boxes.push_back(createTileBox(735, 1395, 127, 208));
    boxes.push_back(createTileBox(865, 1395, 127, 208));
    boxes.push_back(createTileBox(995, 1395, 127, 208));
    boxes.push_back(createTileBox(1130, 1395, 127, 208));
    boxes.push_back(createTileBox(1260, 1395, 127, 208));
    boxes.push_back(createTileBox(1390, 1395, 208, 208));

    boxes.push_back(createTileBox(0, 213, 208, 127));
    boxes.push_back(createTileBox(0, 345, 208, 127));
    boxes.push_back(createTileBox(0, 476, 208, 127));
    boxes.push_back(createTileBox(0, 608, 208, 127));
    boxes.push_back(createTileBox(0, 740, 208, 127));
    boxes.push_back(createTileBox(0, 872, 208, 127));
    boxes.push_back(createTileBox(0, 1004, 208, 127));
    boxes.push_back(createTileBox(0, 1134, 208, 127));
    boxes.push_back(createTileBox(0, 1264, 208, 127));
    boxes.push_back(createTileBox(0, 1395, 208, 208));

    Font uiFont;
    if (!uiFont.openFromFile("Assets/agencyfb.ttf")) {
        cout << "Failed to load UI font!" << endl;
        return -1;
    }

    

    Text red(uiFont);
    Text blue(uiFont);
    Text green(uiFont);
    Text yellow(uiFont);

    red.setString("PLAYER RED");
    blue.setString("PLAYER BLUE");
    green.setString("PLAYER GREEN");
    yellow.setString("PLAYER YELLOW");

    red.setCharacterSize(30);
    blue.setCharacterSize(30);
    green.setCharacterSize(30);
    yellow.setCharacterSize(30);

    red.setFillColor(Color::Color(255, 150, 155, 255));
    blue.setFillColor(Color::Color(170, 211, 210, 255));
    green.setFillColor(Color::Color(186, 222, 160, 255));
    yellow.setFillColor(Color::Color(249, 205, 136, 255));

    red.setStyle(Text::Bold);
    blue.setStyle(Text::Bold);
    green.setStyle(Text::Bold);
    yellow.setStyle(Text::Bold);

    blue.setPosition({ 1740, 370 });
    green.setPosition({ 1740, 470 });
    yellow.setPosition({ 1740, 570 });
    red.setPosition({ 1740, 670 });


    // Initialize sprites
    Sprite boardSprite(boardTexture);
    Sprite diceSprites[2] = { Sprite(diceTextures[0]), Sprite(diceTextures[0]) };
    Sprite playerSprites[4] = { Sprite(playerTextures[0]), Sprite(playerTextures[1]) , Sprite(playerTextures[2]) , Sprite(playerTextures[3]) };
    Sprite pfpSprites[4] = { Sprite(playerUiTex[0]), Sprite(playerUiTex[1]) , Sprite(playerUiTex[2]) , Sprite(playerUiTex[3]) };
    Sprite uibox(uirect);


    diceSprites[0].setTexture(diceTextures[0]);
    diceSprites[1].setTexture(diceTextures[0]);
    diceSprites[0].setPosition({ 1825, 50 });
    diceSprites[1].setPosition({ 2050, 50 });
    diceSprites[0].scale({ 0.5f, 0.5f });
    diceSprites[1].scale({ 0.5f, 0.5f });

    uibox.setPosition({ 1625, 325 });
    uibox.scale({ 1.12f, 1.0f });

    playerSprites[0].scale({ 0.18f, 0.18f });
    playerSprites[0].setPosition({ 1475,1550 });

    playerSprites[1].scale({ 0.18f, 0.18f });
    playerSprites[1].setPosition({ 1465,1480 });

    playerSprites[2].scale({ 0.18f, 0.18f });
    playerSprites[2].setPosition({ 1545,1480 });

    playerSprites[3].scale({ 0.18f, 0.18f });
    playerSprites[3].setPosition({ 1545,1550 });

    pfpSprites[0].scale({ 0.2f, 0.2f }); 
    pfpSprites[0].setPosition({1650, 350});

    pfpSprites[1].scale({ 0.2f, 0.2f });
    pfpSprites[1].setPosition({1650, 450});

    pfpSprites[2].scale({ 0.2f, 0.2f });
    pfpSprites[2].setPosition({1650, 550});

    pfpSprites[3].scale({ 0.2f, 0.2f });
    pfpSprites[3].setPosition({1650, 650});

    // Game initialization
    FloatRect bounds = playerSprites[0].getGlobalBounds();
    RectangleShape bbox;
    bbox.setPosition({ 1550,1550 });
    bbox.setSize({ 30,45 });
    bbox.setFillColor(sf::Color::Transparent); // No fill
    bbox.setOutlineColor(sf::Color::Red);      // Red outline
    bbox.setOutlineThickness(2.f);

    FloatRect bounds1 = playerSprites[0].getGlobalBounds();
    RectangleShape bbox1;
    bbox1.setPosition({ 1550,1480 });
    bbox1.setSize({ 30,45 });
    bbox1.setFillColor(sf::Color::Transparent); // No fill
    bbox1.setOutlineColor(sf::Color::Red);      // Red outline
    bbox1.setOutlineThickness(2.f);

    FloatRect bounds2 = playerSprites[0].getGlobalBounds();
    RectangleShape bbox2;
    bbox2.setPosition({ 1470,1480 });
    bbox2.setSize({ 30,45 });
    bbox2.setFillColor(sf::Color::Transparent); // No fill
    bbox2.setOutlineColor(sf::Color::Red);      // Red outline
    bbox2.setOutlineThickness(2.f);

    FloatRect bounds3 = playerSprites[0].getGlobalBounds();
    RectangleShape bbox3;
    bbox3.setPosition({ 1480,1550 });
    bbox3.setSize({ 30,45 });
    bbox3.setFillColor(sf::Color::Transparent); // No fill
    bbox3.setOutlineColor(sf::Color::Red);      // Red outline
    bbox3.setOutlineThickness(2.f);

    // Main game loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                isRolling = true;
                diceAnimationClock.restart();
                finalRoll1 = rand() % 6 + 1;
                finalRoll2 = rand() % 6 + 1;
            }
        }

        // Update game state
        if (isRolling) {
            Time elapsed = diceAnimationClock.getElapsedTime();
            if (elapsed >= seconds(1.5f)) {
                isRolling = false;
                GameController::next_turn(0, finalRoll1, finalRoll2);
            }
            //update the bal
        }

        // Animation update
        if (isRolling) {
            int frame = (diceAnimationClock.getElapsedTime().asMilliseconds() / 100) % 6;
            diceSprites[0].setTexture(diceTextures[frame]);
            diceSprites[1].setTexture(diceTextures[(frame + 3) % 6]);
        }
        else {
            diceSprites[0].setTexture(diceTextures[finalRoll1 - 1]);
            diceSprites[1].setTexture(diceTextures[finalRoll2 - 1]);
        }
        
        window.clear(Color::Color(23, 14, 28, 255));

        window.draw(boardSprite);
        for (const auto& box : boxes)
            window.draw(box);

        // Draw game elements
        window.draw(diceSprites[0]);
        window.draw(diceSprites[1]);
        window.draw(playerSprites[0]);
        window.draw(playerSprites[1]);
        window.draw(playerSprites[2]);
        window.draw(playerSprites[3]);
        window.draw(uibox);
        window.draw(pfpSprites[0]);
        window.draw(pfpSprites[1]);
        window.draw(pfpSprites[2]);
        window.draw(pfpSprites[3]);
        window.draw(bbox);
        window.draw(bbox1);
        window.draw(bbox2);
        window.draw(bbox3);
        window.draw(red);
        window.draw(blue);
        window.draw(green);
        window.draw(yellow);

        window.display();
    }
}

int main()
{
    GameController::showBoard();
    return 0;
}