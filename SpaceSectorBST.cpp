#include "SpaceSectorBST.h"

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
    // TODO: Delete the sector given by its sector_code from the BST.
}

void SpaceSectorBST::displaySectorsInOrder() {
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPostOrder() {
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
}