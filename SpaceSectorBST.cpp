#include "SpaceSectorBST.h"
#include <stack>
using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    if (root == nullptr) {
        return;
    }

    Sector *current = root;
    Sector *parent = nullptr;
    // Delete all nodes using depth-first traversal
    while (current != nullptr) {
        // dfs to the left child
        if (current->left != nullptr) {
            current = current->left;
        } 
        // dfs to the right child
        else if (current->right != nullptr) {
            current = current->right;
        } else {
            // If current node is root node, delete it and return
            if(current->parent == nullptr) {
                delete current;
                current = nullptr;
                return;
            }
            parent = current->parent;
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete current;
            current = parent;
        }
    }
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
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

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    Sector *new_sector = new Sector(x, y, z);
    if (root == nullptr) {
        root = new_sector;
        return;
    }

    Sector *current = root;
    Sector *parent = nullptr;
    // while (current != nullptr)
    while (true) {
        parent = current;
        if (*new_sector < *current) {
            if (current->left == nullptr) {
                current->left = new_sector;
                new_sector->parent = current;
                return;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = new_sector;
                new_sector->parent = current;
                return;
            }
            current = current->right;
        }
    }
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    Sector *current = findSector(sector_code);
    deleteSectorRecursive(current);
}

void SpaceSectorBST::deleteSectorRecursive(Sector *current) {
    if (current == nullptr) {
        return;
    }

    // if the node is a leaf node, delete it
    if (current->left == nullptr && current->right == nullptr) {
        if (current->parent == nullptr) {
            root = nullptr;
            delete current;
            return;
        }
        Sector *parent = current->parent;
        if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
        return;
    }

    // if the node has only one child, replace it with its child
    if (current->left == nullptr || current->right == nullptr) {
        Sector *child = current->left == nullptr ? current->right : current->left;
        if (current->parent == nullptr) {
            root = child;
            child->parent = nullptr;
            delete current;
            return;
        }
        Sector *parent = current->parent;
        if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        child->parent = parent;
        delete current;
        return;
    }

    // if the node has two children, replace it with its successor
    Sector *successor = current->right;
    while (successor->left != nullptr) {
        successor = successor->left;
    }
    current->x = successor->x;
    current->y = successor->y;
    current->z = successor->z;
    current->distance_from_earth = successor->distance_from_earth;
    current->sector_code = successor->sector_code;

    deleteSectorRecursive(successor);
}

void SpaceSectorBST::displaySectorsInOrder() {
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
        cout << current->sector_code << "\n";
        current = current->right;
    }
    cout << endl;
}

void SpaceSectorBST::displaySectorsPreOrder() {
    cout << "Space sectors preorder traversal: " << endl;

    if (root == nullptr) {
        return;
    }

    stack <Sector*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Sector *current = nodes.top();
        nodes.pop();
        cout << current->sector_code << "\n";
        if (current->right != nullptr) {
            nodes.push(current->right);
        }
        if (current->left != nullptr) {
            nodes.push(current->left);
        }
    }
}

void SpaceSectorBST::displaySectorsPostOrder() {
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
            cout << current->sector_code << "\n";
            nodes.pop();
            last_visited = current;
            current = nullptr;
        } else {
            current = current->right;
        }
    }
    cout << endl;
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
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

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
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

Sector* SpaceSectorBST::findSector(const std::string& sector_code) {
    Sector *current = root;

    // if the node is not found, return
    if (current == nullptr) {
        return nullptr;
    }

    // create stack
    stack<Sector*> nodes;
    nodes.push(current);

    while (!nodes.empty()) {
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
    return nullptr;
}
