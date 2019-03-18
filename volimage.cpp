#include "volimage.hpp"
#include <sstream>
#include <math.h>

namespace AMWPHI001
{
using namespace std;
// default constructor - define in .cpp
VolImage::VolImage()
{
    width = 0;
    height = 0;
    numberImages = 0;
}
// destructor - define in .cpp file
VolImage::~VolImage()
{
    for (int x = 0; x < slices.size(); x++)
    {
        for (int i = 0; i < height; i++)
        {
            delete[] slices[x][i]; // Deallocate each row pointer
        }
        delete[] slices[x]; // Deallocate pointer for each .raw file
    }
}
// populate the object with images in stack and
// set member variables define in .cpp
bool VolImage::readImages(std::string baseName)
{
    std::string fileName;
    fileName = baseName + "/" + baseName + ".data";
    std::ifstream inputFStream(fileName.c_str());

    if (!inputFStream)
    {
        puts("File not found!");
        return true;
    }

    std::string data;
    getline(inputFStream, data);

    std::istringstream inputSStream(data);
    std::string currentString;

    int counter = 1;

    while (getline(inputSStream, currentString, ' '))
    {
        int current;
        std::istringstream stringStream(currentString);
        stringStream >> current;
        if (counter == 1)
        {
            width = current;
            counter++;
        }
        else if (counter == 2)
        {
            height = current;
            counter++;
        }
        else if (counter == 3)
        {
            numberImages = current;
            counter++;
        }
    }
    inputFStream.close();
    for (int i = 0; i < numberImages; i++)
    {
        std::string fileIndex;
        std::stringstream stringStream;
        stringStream << i;
        fileIndex = stringStream.str();
        fileName = baseName + "/" + baseName + fileIndex + ".raw";
        std::ifstream binaryFile(fileName.c_str(), std::ios::binary);

        if (!binaryFile)
        {
            std::string errorMessage = "File " + fileName + " not found.";
            puts(errorMessage.c_str());
            return true;
        }

        u_char **border = new u_char *[height];

        for (int i = 0; i < height; i++)
        {
            border[i] = new u_char[width];
        }

        char *charBlock;
        std::streampos size;
        if (binaryFile.is_open())
        {
            size = binaryFile.tellg();
            charBlock = new char[size];
            binaryFile.seekg(0, std::ios::beg);
            binaryFile.read(charBlock, size);
            binaryFile.close();
        }

        int counter = 0;
        for (int i = 0; i < height; i++) // every row
        {
            for (int j = 0; j < width; j++) // every char
            {
                border[i][j] = charBlock[counter];
                counter++;
            }
        }

        slices.push_back(border);
        delete[] charBlock;
    }
    return true;
}

// compute difference map and write out;  define in .cpp
void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix)
{
    std::string header_filename = output_prefix + ".dat";
    std::ofstream outputFile(header_filename.c_str());
    std::string outputS;
    std::ostringstream outSStream;
    outSStream << width;
    std::ostringstream os;
    os << height;
    outputS = outSStream.str() + " " + os.str() + " 1";
    outputFile << outputS;
    std::string output_filename = output_prefix + ".raw";
    std::ofstream outFStream(output_filename.c_str(), std::ios::out | std::ios::binary);

    int size = height * width;
    std::ostringstream outDataStream;
    outDataStream << size;
    char output[size];
    int counter;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            output[counter] = (u_char)(fabs((float)slices[sliceI][x][y] - (float)slices[sliceJ][x][y]) / 2);
            counter++;
        }
    }

    outFStream.write(output, size);
    outFStream.close();
}

// extract slice sliceId and write to output - define in .cpp
void VolImage::extract(int sliceId, std::string output_prefix)
{
    std::string headFile = output_prefix + ".dat";
    std::ofstream outputFile(headFile.c_str());
    std::string out;
    std::ostringstream outputSStream;
    outputSStream << width;
    std::ostringstream outStream;
    outStream << height;
    out = outputSStream.str() + " " + outStream.str() + " 1";
    outputFile << out;
    std::string outFileName = output_prefix + ".raw";
    std::ofstream outFStream(outFileName.c_str(), std::ios::out | std::ios::binary);

    int size = height * width;
    std::ostringstream outDStream;
    outDStream << size;
    char output[size];
    int counter = 0;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            output[counter] = slices[sliceId][x][y];
            counter++;
        }
    }

    outFStream.write(output, size);
    outFStream.close();
}
// number of bytes uses to store image data bytes
//and pointers (ignore vector<> container, dims etc)
int VolImage::volImageSize(void)
{
    int x = height * width * slices.size();
    return x;
}
int VolImage::volImageNumber(void)
{
    return numberImages;
}
} // namespace AMWPHI001
