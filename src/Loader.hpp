#ifndef LOADER_HPP_
#define LOADER_HPP_

class Loader {
public:
    virtual void suggestedDimensions(int sideLength, int &w, int &h, int &d) = 0;

    virtual size_t blockMemRequirement(int w, int h, int d) {
        size_t elementCost = sizeof(uint8);
        return elementCost*size_t(w)*size_t(h)*size_t(d);
    };

    virtual void setupBlockProcessing(int sideLength, int blockW, int blockH, int blockD,
                                      int volumeW, int volumeH, int volumeD) = 0;
    virtual void processBlock(uint32 *data, int x, int y, int z, int w, int h, int d) = 0;
    virtual bool isBlockEmpty(int x, int y, int z) = 0;
    virtual void teardownBlockProcessing() = 0;

    virtual void convertToVolume(const char *path, int maxSize, size_t memoryBudget) = 0;
};

#endif
