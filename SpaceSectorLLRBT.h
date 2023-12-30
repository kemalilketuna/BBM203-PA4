#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
private:
    Sector *findSector(const std::string& sector_code);
    bool isRed(Sector *node);
    Sector *rotateLeft(Sector *node);
    Sector *rotateRight(Sector *node);
    void flipColors(Sector *node);
    Sector *insert(Sector *sector, Sector *node);
    std::vector<Sector*> getStellarPathMinor(const std::string& sector_code);
};

#endif // SPACESECTORLLRBT_H
