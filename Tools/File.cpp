//
// Created by Rob on 9/9/2023.
//

#include <fstream>
#include <stdexcept>
#include "File.h"
#include "../game/ItemManager.h"

File::File(std::string fileName) {
    this->fileName = fileName;
}

void File::Append(const std::string &contents) {
    std::ofstream ofstream;

    ofstream.open(fileName, std::ios_base::app);
    ofstream << contents;

    if (!silenceOutput)
        std::cout << contents;


    ofstream.close();
}

void File::Append(const std::vector<std::string> contents) {
    std::ofstream ofstream;

    ofstream.open(fileName, std::ios_base::app);
    for (int i = 0; i < contents.size(); i++){
        ofstream << contents[i];

        if (!silenceOutput)
            std::cout << contents[i];
    }
    ofstream.close();
}

void File::Silence(bool silence) {
    silenceOutput = silence;
}

bool File::WriteSaveFile(SaveState data) {
    std::ofstream ofstream(fileName, std::ios::binary | std::ios::out);

    if (!ofstream.is_open()){
        return false;
    }

    // Write the window width and height to ensure spacing
    ofstream.write(reinterpret_cast<const char*>(&data.WindowWidth), sizeof(int));
    ofstream.write(reinterpret_cast<const char*>(&data.WindowHeight), sizeof(int));

    // Writing the player position in the world
    ofstream.write(reinterpret_cast<const char*>(&data.PlayerXPosition), sizeof(int));
    ofstream.write(reinterpret_cast<const char*>(&data.PlayerYPosition), sizeof(int));

    // Get the required space for each vector
    size_t v1 = data.caveState.size();
    size_t v2 = (v1 > 0) ? data.caveState[0].size() : 0;
    size_t v3 = (v1 > 0) ? data.caveState[0][0].size() : 0;
    size_t v4 = (v1 > 0) ? data.caveState[0][0][0].size() : 0;

    // Write the size so we can later reference for sizing
    ofstream.write(reinterpret_cast<const char*>(&v1), sizeof(size_t));
    ofstream.write(reinterpret_cast<const char*>(&v2), sizeof(size_t));
    ofstream.write(reinterpret_cast<const char*>(&v3), sizeof(size_t));
    ofstream.write(reinterpret_cast<const char*>(&v4), sizeof(size_t));

    // Now to write the data
    for (int a = 0; a < v1; a++){
        for (int b = 0; b < v2; b++){
            for (int c = 0; c < v3; c++){
                for (int d = 0; d < v4; d++){
                    ofstream.write(reinterpret_cast<const char*>(&data.caveState[a][b][c][d]), sizeof(int));
                }
            }
        }
    }

    // Now we just have to do this exact thing for all the others!

    size_t w1 = data.worldState.size();
    size_t w2 = (w1 > 0) ? data.worldState[0].size() : 0;

    ofstream.write(reinterpret_cast<const char*>(&w1), sizeof(size_t));
    ofstream.write(reinterpret_cast<const char*>(&w2), sizeof(size_t));

    for (int a = 0; a < w1; a++){
        for (int b = 0; b < w2; b++){
            ofstream.write(reinterpret_cast<const char*>(&data.worldState[a][b]), sizeof(int));
        }
    }

    size_t itemSize = data.items.size();

    std::vector<int> ids;
    std::vector<int> count;

    for (int i = 0; i < itemSize; i++){
        ids.push_back(data.items[i]->GetType());
        count.push_back(data.items[i]->GetCount());
    }

    ofstream.write(reinterpret_cast<const char*>(&itemSize), sizeof(size_t));

    for (int i = 0; i < itemSize; i++){
        ofstream.write(reinterpret_cast<const char*>(&ids[i]), sizeof(int));
    }

    for (int i = 0; i < itemSize; i++){
        ofstream.write(reinterpret_cast<const char*>(&count[i]), sizeof(int));
    }

    ofstream.close();

    return true;

}

SaveState File::ReadSaveFile() {
    SaveState state;
    std::ifstream infile(fileName, std::ios::binary | std::ios::in);

    std::cout << "\tReading Window Data\n";

    infile.read(reinterpret_cast<char*>(&state.WindowWidth), sizeof(int));
    infile.read(reinterpret_cast<char*>(&state.WindowHeight), sizeof(int));

    std::cout << "\tReading Player Position\n";

    infile.read(reinterpret_cast<char*>(&state.PlayerXPosition), sizeof(int));
    infile.read(reinterpret_cast<char*>(&state.PlayerYPosition), sizeof(int));

    std::cout << "\tReading Cave Vector Size\n";

    size_t v1, v2, v3, v4;
    infile.read(reinterpret_cast<char*>(&v1), sizeof(size_t));
    infile.read(reinterpret_cast<char*>(&v2), sizeof(size_t));
    infile.read(reinterpret_cast<char*>(&v3), sizeof(size_t));
    infile.read(reinterpret_cast<char*>(&v4), sizeof(size_t));

    std::cout << "\tResizing Cave Vectors\n";

    state.caveState.resize(v1, std::vector<std::vector<std::vector<int>>>(v2, std::vector<std::vector<int>>(v3, std::vector<int>(v4, 0))));

    std::cout << "\tSaving Cave Values\n";

    for (int a = 0; a < v1; a++){
        for (int b = 0; b < v2; b++){
            for (int c = 0; c < v3; c++){
                for (int d = 0; d < v4; d++){
                    infile.read(reinterpret_cast<char*>(&state.caveState[a][b][c][d]), sizeof(int));
                }
            }
        }
    }

    std::cout << "\tReading World Vector\n";

    size_t w1 = state.worldState.size();
    size_t w2 = (w1 > 0) ? state.worldState[0].size() : 0;

    infile.read(reinterpret_cast<char*>(&w1), sizeof(size_t));
    infile.read(reinterpret_cast<char*>(&w2), sizeof(size_t));

    state.worldState.resize(w1, std::vector<int>(w2, 0));

    for (int a = 0; a < w1; a++){
        for (int b = 0; b < w2; b++){
            infile.read(reinterpret_cast<char*>(&state.worldState[a][b]), sizeof(int));
        }
    }

    std::cout << "\tReading Item Vector\n";

    size_t itemSize;
    infile.read(reinterpret_cast<char*>(&itemSize), sizeof(size_t));

    std::vector<int> ids;
    std::vector<int> count;

    ids.resize(itemSize);
    count.resize(itemSize);

    for (size_t i = 0; i < itemSize; i++) {
        infile.read(reinterpret_cast<char*>(&ids[i]), sizeof(int));
    }

    for (size_t i = 0; i < itemSize; i++) {
        infile.read(reinterpret_cast<char*>(&count[i]), sizeof(int));
    }

    infile.close();

    for (int i = 0; i < ids.size(); i++){
        item* item = ItemManager::GetItem(static_cast<itemType>(ids[i]));
        for (int j = 0; j < count[i]; j++){
            item->AddItem();
        }
    }

    std::cout << "\tRead Saved State\n";

    return state;

}

