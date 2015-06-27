#ifndef ISOSURFACELOADER_HPP_
#define ISOSURFACELOADER_HPP_


#include "math/Vec3.hpp"

#include "IntTypes.hpp"
#include "Timer.hpp"
#include "Loader.hpp"

#include <memory>
#include <vector>

class IsoSurfaceLoader: public Loader {
  int _volumeW, _volumeH, _volumeD;
  int _blockW, _blockH, _blockD;
  float _ratioW, _ratioH, _ratioD, _actual;
public:
    IsoSurfaceLoader();

    void suggestedDimensions(int sideLength, int &w, int &h, int &d);

    void setupBlockProcessing(int sideLength, int blockW, int blockH, int blockD,
                                      int volumeW, int volumeH, int volumeD);
    void processBlock(uint32 *data, int x, int y, int z, int w, int h, int d);
    bool isBlockEmpty(int x, int y, int z);
    void teardownBlockProcessing();

    void convertToVolume(const char *path, int maxSize, size_t memoryBudget);
};

#endif
