import zipfile

# List of files to be zipped
files = [
    "KDT_Node.h",
    "KD_Tree.cpp",
    "KD_Tree.h",
    "kNN.cpp",
    "kNN.h",
    "kNN_Data.h",
    "kNN_DAT_Parser.h",
    "Sector.cpp",
    "Sector.h",
    "SpaceSectorBST.cpp",
    "SpaceSectorBST.h",
    "SpaceSectorLLRBT.cpp",
    "SpaceSectorLLRBT.h"    
]

# Create a new zip file (or overwrite if it exists)
with zipfile.ZipFile("b2220356127.zip", "w") as z:
    for file in files:
        z.write(file)

print("Files zipped successfully into output.zip")