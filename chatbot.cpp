#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

// Valid tech categories
const set<string> validCategories = {"Smartphones", "Laptops", "Tablets", "Gaming Consoles", "Wearables"};

// Models organized as: category -> brand -> models
map<string, map<string, vector<string>>> techData = {
    {"Smartphones", {
        {"Samsung", {"Galaxy A55", "Galaxy S24", "Galaxy M14"}},
        {"Apple", {"iPhone 13 Mini", "iPhone 14", "iPhone SE 2022"}},
        {"Google", {"Pixel 6", "Pixel 7a", "Pixel 8 Pro"}},
        {"Xiaomi", {"Redmi Note 13", "Mi 11 Lite", "Poco X6"}},
        {"OnePlus", {"Nord CE 3", "OnePlus 12", "OnePlus 11R"}},
        {"Oppo", {"Reno10", "F21 Pro", "A78"}},
        {"Vivo", {"V27", "T2x", "Y100"}},
        {"Motorola", {"Edge 40", "Moto G84", "Razr 2023"}},
        {"Realme", {"Narzo 60", "Realme 11 Pro", "Realme C67"}},
        {"Asus", {"ROG Phone 7", "Zenfone 10", "ROG Phone 6"}}
    }},
    {"Laptops", {
        {"Dell", {"XPS 13", "Inspiron 15", "Alienware M18"}},
        {"HP", {"Pavilion", "Spectre x360", "OMEN 16"}},
        {"Apple", {"MacBook Air M2", "MacBook Pro M3"}},
        {"Lenovo", {"ThinkPad X1", "Legion 5i", "IdeaPad Slim 5"}},
        {"Asus", {"ZenBook 14", "ROG Zephyrus G14", "Vivobook 16X"}},
        {"Acer", {"Swift 3", "Aspire 7", "Predator Helios 300"}},
        {"MSI", {"Modern 14", "GF63 Thin", "Stealth 16"}},
        {"Samsung", {"Galaxy Book3", "Galaxy Book2 Pro"}},
        {"Razer", {"Blade 16", "Blade Stealth"}},
        {"Microsoft", {"Surface Laptop 5", "Surface Book 3"}}
    }},
    {"Tablets", {
        {"Apple", {"iPad Air 5", "iPad Mini 6", "iPad Pro 12.9"}},
        {"Samsung", {"Galaxy Tab S9", "Galaxy Tab A9", "Tab S6 Lite"}},
        {"Lenovo", {"Tab P11", "Yoga Tab 13", "Tab M10"}},
        {"Microsoft", {"Surface Go 3", "Surface Pro 9"}},
        {"Xiaomi", {"Pad 6", "Pad 5", "Mi Pad 4"}},
        {"Huawei", {"MatePad Pro", "MediaPad M5", "MatePad 11"}},
        {"Amazon", {"Fire HD 10", "Fire HD 8", "Fire Max 11"}},
        {"Realme", {"Pad X", "Pad Mini"}},
        {"Oppo", {"Pad Air", "Pad Neo"}},
        {"Nokia", {"T21", "T10", "T20"}}
    }},
    {"Gaming Consoles", {
        {"Sony", {"PlayStation 5", "PlayStation 4 Pro"}},
        {"Microsoft", {"Xbox Series X", "Xbox Series S"}},
        {"Nintendo", {"Switch OLED", "Switch Lite"}},
        {"Valve", {"Steam Deck"}},
        {"ASUS", {"ROG Ally"}},
        {"Logitech", {"G Cloud Gaming Console"}},
        {"AYANEO", {"AYANEO 2", "AYANEO AIR"}},
        {"Anbernic", {"RG351MP", "RG503"}},
        {"Retroid", {"Retroid Pocket 3+"}},
        {"GPD", {"Win 4", "Win Max 2"}}
    }},
    {"Wearables", {
        {"Apple", {"Watch Series 9", "Watch SE", "Watch Ultra 2"}},
        {"Samsung", {"Galaxy Watch 6", "Galaxy Fit 3"}},
        {"Fitbit", {"Charge 6", "Versa 4", "Inspire 3"}},
        {"Garmin", {"Venu 2", "Fenix 7", "Forerunner 265"}},
        {"Huawei", {"Watch GT 4", "Band 8"}},
        {"Amazfit", {"GTR 4", "Bip 5", "T-Rex Ultra"}},
        {"Noise", {"ColorFit Pro 4", "Evolve 3"}},
        {"boAt", {"Wave Sigma", "Lunar Connect"}},
        {"Realme", {"Watch 3 Pro", "Band 2"}},
        {"OnePlus", {"Watch 2", "Band"}}
    }}
};

// Favorites and top picks
unordered_map<string, set<string>> favorites;
map<string, map<int, string>> topPicks;

// Recent selections using a queue
queue<string> recentSelections;

// History using stack
stack<string> history;

// User name
string username;

// Helper
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void greetUser() {
    cout << "Hello! I'm TechBot. May I know your name?\n> ";
    getline(cin, username);
    cout << "Nice to meet you, " << username << "! I'm here to help you find your ideal tech product.\n";
}

void showCategories() {
    cout << "\nAvailable Tech Categories:\n";
    for (const auto& cat : validCategories) cout << "- " << cat << endl;
}

string selectCategory() {
    string cat;
    // Display categories before asking for input
    showCategories();

    while (true) {
        cout << "\nWhich tech category are you interested in?\n> ";
        getline(cin, cat);
        if (validCategories.count(cat)) return cat;
        cout << "Invalid category. Please choose from the list below:\n";
        showCategories();
    }
}


string askBrand(const string& category) {
    cout << "\nAvailable brands for " << category << ":\n";
    for (auto& [brand, _] : techData[category])
        cout << "- " << brand << endl;
    cout << "Which brand do you prefer?\n> ";
    string brand;
    getline(cin, brand);
    return brand;
}

void suggestModels(const string& category, const string& brand) {
    const auto& models = techData[category][brand];
    if (models.empty()) {
        cout << "No models found for this brand.\n";
        return;
    }

    cout << "\nMatching models from " << brand << ":\n";
    for (size_t i = 0; i < models.size(); ++i)
        cout << "[" << (i + 1) << "] " << models[i] << endl;

    cout << "\nEnter model number to view details (or 0 to skip): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice > 0 && choice <= models.size()) {
        string model = models[choice - 1];
        cout << "\nModel Details - " << model << ":\n";
        cout << "- Release: 2024\n- Specs: 8GB RAM, 128GB Storage\n- Price: $699\n";
        cout << "- Pros: Reliable, Great battery\n- Cons: Pricey\n";

        history.push(model);
        if (recentSelections.size() >= 5) recentSelections.pop();
        recentSelections.push(model);

        cout << "\nAdd this model to your Favorites? (Yes/No): ";
        string ans;
        getline(cin, ans);
        if (toLower(ans) == "yes") {
            favorites[category].insert(model);
            cout << model << " added to Favorites.\n";
        }
    }
}

void showFavorites() {
    cout << "\nYour Favorites:\n";
    for (auto& [cat, favs] : favorites) {
        cout << "- " << cat << ":\n";
        for (const auto& model : favs)
            cout << "  " << model << endl;
    }
}

void showTopPicks() {
    cout << "\nTop Picks by Category:\n";
    for (auto& [cat, picks] : topPicks) {
        cout << "- " << cat << ":\n";
        for (auto& [rank, model] : picks)
            cout << "  #" << rank << ": " << model << endl;
    }
}

void manageTopPicks(const string& category) {
    cout << "Enter rank (1-10): ";
    int rank;
    cin >> rank;
    cin.ignore();
    if (rank < 1 || rank > 10) {
        cout << "Invalid rank.\n";
        return;
    }
    cout << "Enter model name to set as Top " << rank << ": ";
    string model;
    getline(cin, model);
    topPicks[category][rank] = model;
    cout << model << " added as Top " << rank << " in " << category << ".\n";
}

void showHistory() {
    stack<string> temp = history;
    cout << "\nModel View History (most recent on top):\n";
    while (!temp.empty()) {
        cout << "- " << temp.top() << endl;
        temp.pop();
    }
}

void showRecent() {
    queue<string> temp = recentSelections;
    cout << "\nRecently Viewed Models:\n";
    while (!temp.empty()) {
        cout << "- " << temp.front() << endl;
        temp.pop();
    }
}

bool confirmExit() {
    cout << "Are you sure you want to exit? (Yes/No): ";
    string res;
    getline(cin, res);
    return toLower(res) == "yes";
}

void mainMenu() {
    while (true) {
        string category = selectCategory();
        string brand = askBrand(category);
        suggestModels(category, brand);

        while (true) {
            cout << "\nOptions:\n"
                 << "1. View Favorites\n"
                 << "2. Add Top Pick\n"
                 << "3. View History\n"
                 << "4. View Recent Models\n"
                 << "5. Show Top Picks\n"
                 << "6. Back to Category\n"
                 << "7. Exit\n> ";
            int opt;
            cin >> opt;
            cin.ignore();

            if (opt == 1) showFavorites();
            else if (opt == 2) manageTopPicks(category);
            else if (opt == 3) showHistory();
            else if (opt == 4) showRecent();
            else if (opt == 5) showTopPicks();
            else if (opt == 6) break;
            else if (opt == 7 && confirmExit()) return;
        }
    }
    cout << "Thank you for using TechBot, " << username << "! Goodbye.\n";
}

int main() {
    greetUser();
    mainMenu();
    return 0;
}


/**
Data Structure Used on this program
map	= Organizing categories, brands, and top picks
set	= Storing unique categories and favorites
vector	= Managing list of models per brand
stack	= Model view history (LIFO)
queue	= Recently viewed models (FIFO)
*/
