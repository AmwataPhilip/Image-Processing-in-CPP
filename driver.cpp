#include "volimage.hpp"
#include <iostream>
#include <cstdio>
#include <string>

using namespace AMWPHI001;

int main(int argc, char *argv[])
{
    int byteSize;
    VolImage volimage;

    if (argc > 2)
    {
        volimage.readImages(std::string(argv[1]));
        if (std::string(argv[2]) == "-x") // extraction case
        {
            int inter = std::stoi(argv[3]);
            volimage.extract(inter, std::string(argv[4]));
            byteSize = volimage.volImageSize();
            std::cout << "Number of images: " << volimage.volImageNumber() << std::endl;
            std::cout << "Number of bytes required: " << byteSize << std::endl;
            std::cout << "Successfully Extracted Slice number: " << argv[3] << std::endl;
            std::cout << "Stored Slice in file: " << argv[4] << ".raw" << std::endl;
            return 0;
        }
        else if (std::string(argv[2]) == "-d") // difference map case
        {
            volimage.diffmap(std::stoi(argv[3]), std::stoi(argv[4]), std::string(argv[5]));
            byteSize = volimage.volImageSize();
            std::cout << "Number of images: " << volimage.volImageNumber() << std::endl;
            std::cout << "Number of bytes required: " << byteSize << std::endl;
            std::cout << "Successfully Computed Difference Map between: " << argv[3] << " and " << argv[4] << std::endl;
            std::cout << "Stored Difference Map in file: " << argv[5] << ".raw" << std::endl;
            return 0;
        }
        else
        {
            puts("Error - ensure you have typed int correct input (Check README.txt)");
        }
    }
    else if (argc == 2)
    {
        volimage.readImages(std::string(argv[1]));
        byteSize = volimage.volImageSize();
        std::cout << "Number of images: " << volimage.volImageNumber() << std::endl;
        std::cout << "Number of bytes required: " << byteSize << std::endl;
        return 0;
    }
    else
    {
        puts("Operation Error - Incorrect Terminal Input!");
        puts("Check README.txt for instructions.");
        return 0;
    }
}
