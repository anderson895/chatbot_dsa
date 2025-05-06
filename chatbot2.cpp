#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct Model {
    string name;
    string specs;
    string pros;
    string cons;
    double price;
    double reviews;
};

struct CompareRank {
    bool operator()(pair<int, Model> a, pair<int, Model> b) {
        return a.first > b.first;
    }
};

map<string, map<string, vector<Model>>> techData;
set<string> favorites;
priority_queue<pair<int, Model>, vector<pair<int, Model>>, CompareRank> topPicks;
stack<string> navHistory;

string userName;

void loadSampleData() {
    // Sample data for Smartphones
    techData["Smartphones"]["Samsung"] = {
        {"Samsung Galaxy A55", "8GB RAM, AMOLED 120Hz, ₱23,990", "Sleek, vibrant", "No wireless charging", 23990, 4.4},
        {"Samsung Galaxy S21 FE", "8GB RAM, AMOLED 120Hz, ₱27,990", "Flagship feel", "Average battery", 27990, 4.5},
        {"Samsung Galaxy M54 5G", "8GB RAM, 6000mAh, ₱24,990", "Battery king", "Bulky", 24990, 4.3}
    };

    techData["Smartphones"]["Apple"] = {
        {"iPhone 13", "4GB RAM, OLED, ₱56,990", "Smooth performance", "Expensive", 56990, 4.8},
        {"iPhone 14", "6GB RAM, OLED, ₱69,990", "Flagship quality", "Battery drains faster", 69990, 4.7}
    };

    // Sample data for Laptops
    techData["Laptops"]["Dell"] = {
        {"Dell XPS 13", "16GB RAM, 512GB SSD, ₱79,990", "Premium build", "Expensive", 79990, 4.6},
        {"Dell Inspiron 15", "8GB RAM, 512GB SSD, ₱39,990", "Budget-friendly", "Average display", 39990, 4.2}
    };

    techData["Laptops"]["HP"] = {
        {"HP Spectre x360", "16GB RAM, 512GB SSD, ₱89,990", "Stylish design", "Short battery life", 89990, 4.7},
        {"HP Pavilion 14", "8GB RAM, 256GB SSD, ₱42,990", "Affordable", "Slower performance", 42990, 4.3}
    };

    // Sample data for Tablets
    techData["Tablets"]["Apple"] = {
        {"iPad Pro 12.9", "128GB, Liquid Retina display, ₱89,990", "Best for creatives", "Expensive", 89990, 4.9},
        {"iPad Air", "64GB, Retina display, ₱33,990", "Great value", "Not enough storage", 33990, 4.6}
    };

    techData["Tablets"]["Samsung"] = {
        {"Samsung Galaxy Tab S8", "128GB, AMOLED display, ₱49,990", "Premium tablet", "Expensive", 49990, 4.7},
        {"Samsung Galaxy Tab A7", "64GB, TFT display, ₱15,990", "Budget-friendly", "Lower resolution", 15990, 4.3}
    };

    // Sample data for Gaming Consoles
    techData["Gaming Consoles"]["Sony"] = {
        {"PS5", "825GB SSD, 4K resolution, ₱39,990", "Fast load times", "Limited availability", 39990, 4.9},
        {"PS4 Pro", "1TB HDD, 4K resolution, ₱24,990", "Good game library", "Old hardware", 24990, 4.4}
    };

    techData["Gaming Consoles"]["Microsoft"] = {
        {"Xbox Series X", "1TB SSD, 4K resolution, ₱39,990", "Great performance", "Expensive", 39990, 4.8},
        {"Xbox Series S", "512GB SSD, 1440p resolution, ₱19,990", "Affordable", "No disc drive", 19990, 4.5}
    };

    // Sample data for Wearables
    techData["Wearables"]["Apple"] = {
        {"Apple Watch Series 7", "32GB storage, GPS, ₱21,990", "Premium build", "Expensive", 21990, 4.8},
        {"Apple Watch SE", "32GB storage, GPS, ₱14,990", "Great value", "No ECG feature", 14990, 4.6}
    };

    techData["Wearables"]["Samsung"] = {
        {"Samsung Galaxy Watch 4", "16GB storage, GPS, ₱14,990", "Sleek design", "Battery drains fast", 14990, 4.5},
        {"Samsung Galaxy Watch 5", "16GB storage, GPS, ₱18,990", "Great features", "Expensive", 18990, 4.6}
    };
}

void greetUser() {
    cout << "----------------WELCOME TO TECH ADVISOR! ---------------\n\n";
    cout << "[TechBot]: Hello! I'm TechBot, your personal technology advisor.\nMay I know your name?\n\n[User]: ";
    getline(cin, userName);
    cout << "\n[TechBot]: Nice to meet you, " << userName << "! Let's find the perfect tech device for you.\n\n";
}

string toLowerCase(const string& input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string extractValidCategory(const string& userInput) {
    map<string, vector<string>> synonyms = {
        {"Smartphones", {"smartphone", "phone", "cellphone"}},
        {"Laptops", {"laptop", "notebook"}},
        {"Tablets", {"tablet", "ipad"}},
        {"Gaming Consoles", {"console", "gaming", "ps5", "xbox", "switch"}},
        {"Wearables", {"wearable", "watch", "smartwatch", "fitness"}}
    };

    string lower = toLowerCase(userInput);
    for (const auto& [category, keywords] : synonyms) {
        for (const auto& keyword : keywords) {
            if (lower.find(keyword) != string::npos) {
                return category;
            }
        }
    }
    return "";
}

string askCategory() {
    string userInput;
    while (true) {
        cout << "To begin, what type of technology are you currently looking for?\n";
        cout << "Options: Smartphones, Laptops, Tablets, Gaming Consoles, Wearables\n\n[User]: ";
        getline(cin, userInput);

        string category = extractValidCategory(userInput);
        if (!category.empty()) {
            navHistory.push("main_menu");
            return category;
        }

        cout << "\n[TechBot]: Invalid category. Please choose again.\n";
    }
}

void askPreferences(map<string, string>& prefs) {
    cout << "\n[TechBot]: Great! Let me gather more details:\n";

    cout << "What is your budget range?\n[User]: ";
    getline(cin, prefs["budget"]);

    cout << "Do you have a preferred brand or brands?\n[User]: ";
    getline(cin, prefs["brand"]);

    cout << "What amount of RAM do you need for your device? \n[User]: ";
    getline(cin, prefs["ram"]);

    cout << "What type of display would you prefer? (e.g., AMOLED, LCD, high refresh rate, etc.) \n[User]: ";
    getline(cin, prefs["display"]);

    cout << "How important is camera quality to you?\n[User]: ";
    getline(cin, prefs["camera"]);

    cout << "How long do you expect the battery to last? (e.g., more than a day, fast charging, etc.) \n[User]: ";
    getline(cin, prefs["battery"]);

    cout << "Do you prefer a phone with a sleek design or a more rugged build? \n[User]: ";
    getline(cin, prefs["design"]);

    cout << " Is gaming performance important to you? \n[User]: ";
    getline(cin, prefs["gaming"]);

    cout << "Do you need 5G connectivity? \n[User]: ";
    getline(cin, prefs["5g"]);

    cout << "Are there any special features you want? (e.g., wireless charging, expandable storage, waterproof) \n[User]: ";
    getline(cin, prefs["features"]);
}

void showRecommendations(const string& category, const string& brand) {
    if (techData[category].find(brand) == techData[category].end()) {
        cout << "\n[TechBot]: Sorry, we don't have models for " << brand << " in " << category << ".\n";
        return;
    }

    cout << "\n[TechBot]: Based on your answers, here are the models:\n\n";

    int i = 1;
    for (auto& model : techData[category][brand]) {
        cout << "[" << i++ << "] " << model.name << endl;
    }

    int choice;
    cout << "\nWhich model would you like to view first? (Type number): ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > techData[category][brand].size()) return;

    Model selected = techData[category][brand][choice - 1];

    cout << "\n-------- Model Details: -------------\n";
    cout << "Model Name: " << selected.name << endl;
    cout << "Specs: " << selected.specs << endl;
    cout << "Pros: " << selected.pros << endl;
    cout << "Cons: " << selected.cons << endl;
    cout << "Price: ₱" << selected.price << endl;
    cout << "Reviews: " << selected.reviews << endl;

    string interest;
    cout << "\n[TechBot]: Are you interested in this model? (Yes/No)\n[User]: ";
    getline(cin, interest);

    if (toLowerCase(interest) == "yes") {
        favorites.insert(selected.name);
        cout << "\n[TechBot]: " << selected.name << " has been added to your Favorites.\n";
    }
}

void viewFavorites() {
    cout << "\n--------- Favorites List ---------\n";
    if (favorites.empty()) {
        cout << "No favorites yet.\n";
    } else {
        for (const auto& f : favorites) {
            cout << "- " << f << endl;
        }
    }
}

void manageTopPicks() {
    cout << "\nLet's rank your Top Picks.\n";
    vector<string> favList(favorites.begin(), favorites.end());

    if (favList.empty()) {
        cout << "No favorites to rank.\n";
        return;
    }

    for (size_t i = 0; i < favList.size(); ++i)
        cout << "[" << i + 1 << "] " << favList[i] << endl;

    int idx, rank;
    while (true) {
        cout << "\nSelect a model to rank (or 0 to finish): ";
        cin >> idx;
        if (idx == 0) break;
        if (idx < 1 || idx > favList.size()) continue;

        cout << "Assign a rank (1–10): ";
        cin >> rank;

        Model m = { favList[idx - 1], "", "", "", 0, 0 };
        topPicks.push({ rank, m });
    }
    cin.ignore();
    cout << "\nTop Picks Ranking Complete.\n";
}

void showTopPicks() {
    priority_queue<pair<int, Model>, vector<pair<int, Model>>, CompareRank> temp = topPicks;

    cout << "\nYour Top Picks:\n";
    while (!temp.empty()) {
        auto [rank, model] = temp.top();
        temp.pop();
        cout << "Rank #" << rank << ": " << model.name << endl;
    }
}

int main() {
    loadSampleData();
    greetUser();

    while (true) {
        string category = askCategory();

        if (techData.find(category) == techData.end()) {
            cout << "\n[TechBot]: Invalid category. Please choose again.\n";
            continue;
        }

        map<string, string> preferences;
        askPreferences(preferences);
        showRecommendations(category, preferences["brand"]);

        string option;
        while (true) {
            cout << "\n[TechBot]: What would you like to do next?\n[A] View another model\n[B] Main Menu\n[C] View Favorites\n[D] Top Picks\n[X] Exit\n\n[User]: ";
            getline(cin, option);

            if (option == "A" || option == "a") {
                showRecommendations(category, preferences["brand"]);
            } else if (option == "B" || option == "b") {
                break;
            } else if (option == "C" || option == "c") {
                viewFavorites();
            } else if (option == "D" || option == "d") {
                manageTopPicks();
                showTopPicks();
            } else if (option == "X" || option == "x") {
                string confirm;
                cout << "\n[TechBot]: Are you sure you want to exit, " << userName << "? (Yes/No)\n[User]: ";
                getline(cin, confirm);
                if (toLowerCase(confirm) == "yes") {
                    cout << "\n[TechBot]: Thank you, " << userName << "! Hope to assist you again soon!\n";
                    return 0;
                }
            }
        }
    }

    return 0;
}
