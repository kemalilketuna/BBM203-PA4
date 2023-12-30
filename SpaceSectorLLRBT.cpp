#include "SpaceSectorLLRBT.h"
#include <stack>
using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.
}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
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
    cout << "Space sectors inorder traversal: " << endl;

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
    cout << "Space sectors preorder traversal: " << endl;

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
    cout << "Space sectors postorder traversal: " << endl;

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

    if (root == nullptr) {
        return path;
    }

    Sector *current = root;
    Sector *target = findSector(sector_code);
    if (target == nullptr) {
        return path;
    }
    
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