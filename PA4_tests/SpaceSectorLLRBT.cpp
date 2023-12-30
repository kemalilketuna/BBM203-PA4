#include "SpaceSectorLLRBT.h"
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    if (root == nullptr) {
        return;
    }

    Sector *current = root;
    Sector *parent = nullptr;
    queue<Sector*> nodes;
    nodes.push(current);
    while (!nodes.empty()) {
        current = nodes.front();
        nodes.pop();
        if (current->left != nullptr) {
            nodes.push(current->left);
        }
        if (current->right != nullptr) {
            nodes.push(current->right);
        }
        delete current;
    }
}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        return;
    }

    string line;
    getline(infile, line); // Skip the first line
    while (getline(infile, line)) {
        stringstream ss(line);
        // take in the line and parse it
        string x, y, z;
        getline(ss, x, ',');
        getline(ss, y, ',');
        getline(ss, z, ',');
        insertSectorByCoordinates(stoi(x), stoi(y), stoi(z));
    }
}

bool SpaceSectorLLRBT::isRed(Sector* sector) {
    if (sector == nullptr) return false;
    return sector->color;
}

Sector* SpaceSectorLLRBT::rotateLeft(Sector* sector) {
    Sector* temp = sector->right;
    sector->right = temp->left;
    temp->left = sector;
    temp->color = sector->color;
    sector->color = true;
    return temp;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector* sector) {
    Sector* temp = sector->left;
    sector->left = temp->right;
    temp->right = sector;
    temp->color = sector->color;
    sector->color = true;
    return temp;
}

void SpaceSectorLLRBT::flipColors(Sector* sector) {
    sector->color = true;
    sector->left->color = false;
    sector->right->color = false;
}

Sector* SpaceSectorLLRBT::insert(Sector *sector, Sector *node) {
    if (sector == nullptr) {
        return node;
    }

    if (*node < *sector) {
        sector->left = insert(sector->left, node);
    } else if (*node > *sector) {
        sector->right = insert(sector->right, node);
    } else {
        return sector;
    }

    if (isRed(sector->right) && !isRed(sector->left)) {
        sector = rotateLeft(sector);
    }
    if (isRed(sector->left) && isRed(sector->left->left)) {
        sector = rotateRight(sector);
    }
    if (isRed(sector->left) && isRed(sector->right)) {
        flipColors(sector);
    }
    return sector;
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    Sector *new_sector = new Sector(x, y, z);
    root = insert(root, new_sector);
    root->color = false;
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    cout << "Space sectors inorder traversal:" << endl;

    if (root == nullptr) {
        return;
    }

    stack <Sector*> nodes;
    Sector *current = root;

    while (current != nullptr || !nodes.empty()) {
        while (current != nullptr) {
            nodes.push(current);
            current = current->left;
        }
        current = nodes.top();
        nodes.pop();
        cout << (current->color? "RED" : "BLACK") << " sector: " << current->sector_code << "\n";
        current = current->right;
    }
    cout << endl;
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    cout << "Space sectors preorder traversal:" << endl;

    if (root == nullptr) {
        return;
    }

    stack <Sector*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Sector *current = nodes.top();
        nodes.pop();
        cout << (current->color? "RED" : "BLACK") << " sector: " << current->sector_code << "\n";
        if (current->right != nullptr) {
            nodes.push(current->right);
        }
        if (current->left != nullptr) {
            nodes.push(current->left);
        }
    }
    cout << endl;
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    cout << "Space sectors postorder traversal:" << endl;

    if (root == nullptr) {
        return;
    }

    stack <Sector*> nodes;
    Sector *current = root;
    Sector *last_visited = nullptr;

    while (current != nullptr || !nodes.empty()) {
        while (current != nullptr) {
            nodes.push(current);
            current = current->left;
        }
        current = nodes.top();
        if (current->right == nullptr || current->right == last_visited) {
            cout << (current->color? "RED" : "BLACK") << " sector: " << current->sector_code << "\n";
            nodes.pop();
            last_visited = current;
            current = nullptr;
        } else {
            current = current->right;
        }
    }
    cout << endl;
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;

    vector<Sector*> target_path = getStellarPathMinor(sector_code);
    vector<Sector*> earth_path = getStellarPathMinor("0SSS");

    if (target_path.empty() || earth_path.empty()) {
        return path;
    }

    // Find same sector count in both paths
    int same_sector_count = 0;
    while (same_sector_count < target_path.size() && same_sector_count < earth_path.size()) {
        if (target_path[same_sector_count]->sector_code != earth_path[same_sector_count]->sector_code) {
            break;
        }
        same_sector_count++;
    }

    // Remove the common sectors from earth path
    for (int i = 0; i < same_sector_count; i++) {
        earth_path.erase(earth_path.begin());
    }

    // Reverse the earth path
    reverse(earth_path.begin(), earth_path.end());

    // Remove the common sectors from target path and minus 1 from the count
    for (int i = 0; i < same_sector_count - 1; i++) {
        target_path.erase(target_path.begin());
    }

    // Combine the two paths
    path.insert(path.end(), earth_path.begin(), earth_path.end());
    path.insert(path.end(), target_path.begin(), target_path.end());

    return path;
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPathMinor(const std::string& sector_code) {
    std::vector<Sector*> path;

    Sector *current = root;
    if (current == nullptr) {
        return path;
    }

    // Find the target sector
    Sector *target = findSector(sector_code);
    if (target == nullptr) {
        return path;
    }

    // Traverse the tree until we find the target sector or we reach a null node.
    stack<Sector*> nodes;
    nodes.push(current);

    while (current != nullptr) {
        path.push_back(current);
        if (current->sector_code == sector_code) {
            break;
        }
        if (*target < *current) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    if (path.empty()) {
        cout << "A path to Dr. Elara could not be found." << endl;
        return;
    }

    // TODO: check this later
    cout << "The stellar path to Dr. Elara: ";

    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->sector_code;
        if (i != path.size() - 1) {
            cout << "->";
        }
    }
    cout << endl;
}

Sector* SpaceSectorLLRBT::findSector(const std::string& sector_code) {
    Sector *current = root;

    // If current is null, then the sector code does not exist in the tree.
    if (current == nullptr) {
        return nullptr;
    }

    // Traverse the tree until we find the sector code or we reach a null node.
    stack<Sector*> nodes;
    nodes.push(current);

    while (!nodes.empty()){
        current = nodes.top();
        nodes.pop();

        if (current->sector_code == sector_code) {
            return current;
        }
        if (current->right != nullptr) {
            nodes.push(current->right);
        }
        if (current->left != nullptr) {
            nodes.push(current->left);
        }
    }

    // If we reach this point, then the sector code does not exist in the tree.
    return nullptr;
}