import shutil
import os

# Get the current directory of the Python script
current_dir = os.path.dirname(os.path.abspath(__file__))

# Define the directory where you want to copy the files
target_directory = os.path.join(current_dir, "PA4_tests")

# Make the directory if it doesn't exist
if not os.path.exists(target_directory):
    os.makedirs(target_directory)

# List of files to copy
files_to_copy = [
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

# Copy files to the target directory
for file_name in files_to_copy:
    source_path = os.path.join(current_dir, file_name)
    if os.path.exists(source_path):
        shutil.copy(source_path, target_directory)
    else:
        print(f"File {file_name} does not exist in the current directory.")


# Change directory to the target directory
os.chdir(target_directory)

# Run make command
return_code = os.system("make")

if return_code == 0:
    return_code = os.system("./Test")
    if return_code == 1:
        print("Test not runned.")
else:
    print("Make command failed.")

