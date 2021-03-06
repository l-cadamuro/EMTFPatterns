#include <string>
#include <fstream>

namespace IOUtils
{
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -
    // open input txt file and append all the files it contains to TChain
    int appendFromFileList (TChain* chain, std::string filename)
    {
        //cout << "=== inizio parser ===" << endl;
        std::ifstream infile(filename.c_str());
        std::string line;
        int nfiles = 0;
        while (std::getline(infile, line))
        {
            line = line.substr(0, line.find("#", 0)); // remove comments introduced by #
            while (line.find(" ") != std::string::npos) line = line.erase(line.find(" "), 1); // remove white spaces
            while (line.find("\n") != std::string::npos) line = line.erase(line.find("\n"), 1); // remove new line characters
            while (line.find("\r") != std::string::npos) line = line.erase(line.find("\r"), 1); // remove carriage return characters
            if (!line.empty()) // skip empty lines
            {
                chain->Add(line.c_str());
                ++nfiles;
            }
         }
        return nfiles;
    }
}
