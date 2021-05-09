#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "MeshOrient.h"
using namespace std;

/**
 * @brief Seperate string origin by given a set of patterns.
 * 
 * @param origin 
 * @param patterns If it meets one of the patterns, delete the charactor and split it from this index.
 * @return std::vector<std::string> 
 */
std::vector<std::string> seperate_string(std::string origin, std::vector<std::string> patterns = {" ", "\t"}) {
    std::vector<std::string> result;
    if (origin.length() == 0) {
        return result;
    }
    origin += patterns[0];
    size_t startPos = origin.npos;
    for (auto pt = patterns.begin(); pt != patterns.end(); pt++) {
        startPos = (origin.find(*pt) < startPos) ? origin.find(*pt) : startPos;
    }
    size_t pos = startPos;
    while (pos != origin.npos) {
        std::string temp = origin.substr(0, pos);
        if (temp.length())
            result.push_back(temp);
        origin = origin.substr(pos + 1, origin.size());
        pos = origin.npos;
        for (auto pt = patterns.begin(); pt != patterns.end(); pt++) {
            pos = (origin.find(*pt) < pos) ? origin.find(*pt) : pos;
        }
    }
    return result;
}

int read_VTK(std::string filename, vector<vector<double>> &V, vector<vector<int>> &T) {
    int nPoints = 0;
    int nFacets = 0;
    std::ifstream vtk_file;
    vtk_file.open(filename);
    if(!vtk_file.is_open()) {
        cout << "No such file." << endl;
        return -1;
    }
    std::string vtk_type_str = "POLYDATA ";
    char buffer[256];
    while(!vtk_file.eof()) {
        vtk_file.getline(buffer, 256);
        std::string line = (std::string)buffer;
        if(line.length() < 2 || buffer[0] == '#')
            continue;
        if(line.find("DATASET") != std::string::npos) {
            std::vector<std::string> words = seperate_string(line);
            if(words[1] == "POLYDATA") 
                vtk_type_str = "POLYGONS ";
            else if(words[1] == "UNSTRUCTURED_GRID")
                vtk_type_str = "CELLS ";
            else {
                cout << "WARN : The format of VTK file is illegal, No clear DATASET name." << endl;
            }
        }
        if(line.find("POINTS ") != std::string::npos) {
            std::vector<std::string> words = seperate_string(line);
            nPoints = stoi(words[1]);
            for(int i = 0; i < nPoints; i++) {
                vtk_file.getline(buffer, 256);
                words = seperate_string(std::string(buffer));
                V.push_back( {stod(words[0]), stod(words[1]), stod(words[2])} );
            }
        }
        if(line.find(vtk_type_str) != std::string::npos) {
            std::vector<std::string> words = seperate_string(line);
            nFacets = stoi(words[1]);
            for(int i = 0; i < nFacets; i++) {
                vtk_file.getline(buffer, 256);
                words = seperate_string(std::string(buffer));
                T.push_back( {stoi(words[1]), stoi(words[2]), stoi(words[3])} );
            }
        }
    }
    vtk_file.close();
    return 1;
}

int write_VTK(std::string filename, const vector<vector<double>> &V, const vector<vector<int>> &T, const vector<int> blockMark = vector<int>()) {
    std::ofstream f(filename);
    if(!f.is_open()) {
        cout << "Write VTK file failed. " << endl; 
        return 0;
    }
    f.precision(std::numeric_limits<double>::digits10 + 1);
    f << "# vtk DataFile Version 2.0" << std::endl;
    f << "TetWild Mesh" << std::endl;
    f << "ASCII" << std::endl;
    f << "DATASET UNSTRUCTURED_GRID" << std::endl;
    f << "POINTS " << V.size() << " double" << std::endl;
    for(int i = 0; i < V.size(); i++)
        f << V[i][0] << " " << V[i][1] << " " << V[i][2] << std::endl;
    f << "CELLS " << T.size() << " " << T.size() * 4 << std::endl;
    for(int i = 0; i < T.size(); i++) {
        f << T[i].size() << " ";
        for(int j = 0; j < T[i].size(); j++)
            f << T[i][j] << " ";
        f << std::endl;
    }
    f << "CELL_TYPES " << T.size() << std::endl;
    int cellType = 5;
    for(int i = 0; i < T.size(); i++)
        f << cellType << std::endl;
    if(blockMark.size() == T.size()) {
        f << "CELL_DATA " << T.size() << std::endl;
        f << "SCALARS cell2bodyid int 1" << std::endl;
        f << "LOOKUP_TABLE default" << std::endl;
        for(int i = 0; i < blockMark.size(); i++) 
            f << blockMark[i] << std::endl;
    }
    f.close();
    return 1;
}

int main(int argc, char** argv) {
    if(argc < 2) {
        cout << "No file input." << endl;
        return -1;
    }
    string input_filename = argv[1];
    string output_filename = input_filename.substr(0, input_filename.find_last_of('.')) + ".o.vtk";
    vector<vector<double>> plist;
    vector<vector<int>> flist;
    int status = 1;
    status = read_VTK(input_filename, plist, flist);
    if(status == 0) return -1;
    cout << "VTK file read succeed." << " - " << input_filename << endl;
    cout << "  " << plist.size() << " points" << endl;
    cout << "  " << flist.size() << " facets" << endl;
    vector<int> bMark;
    status = TIGER::resetOrientation(plist, flist, bMark);
    if(status == 0) return -1;
    cout << "Reset orientation finished." << endl;
    int blockNum = 0;
    for(auto &b : bMark)
        blockNum = max(b, blockNum);
    cout << "  " << ++blockNum << " blocks" << endl;
    cout << "Output file will be written to " << output_filename << endl;
    status = write_VTK(output_filename, plist, flist, bMark);
    return 0;
}