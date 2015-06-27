#include "IsoSurfaceLoader.hpp"
#include <stdio.h>
#include <iostream>
#include "Util.hpp"

float eval(Vec3 pos) {
    float r = .25;
    return pos.length() - r;
}

IsoSurfaceLoader::IsoSurfaceLoader() {
    std::cout << "building...\n";


}

void IsoSurfaceLoader::suggestedDimensions(int sideLength, int &w, int &h, int &d) {
  w = sideLength;
  h = sideLength;
  d = sideLength;
  printf("dims: %i\n", sideLength);
}

void IsoSurfaceLoader::setupBlockProcessing(int sideLength, int blockW, int blockH, int blockD,
                                            int volumeW, int volumeH, int volumeD) {
    _blockW = blockW;
    _blockH = blockH;
    _blockD = blockD;
    _volumeW = volumeW;
    _volumeH = volumeH;
    _volumeD = volumeD;


    // TODO: volume vs block size
    _actual = 2.0/sideLength;

    _ratioH = 2.0/volumeH;
    _ratioD = 2.0/volumeD;
}

void IsoSurfaceLoader::processBlock(uint32 *data, int x, int y, int z, int w, int h, int d) {
    printf("block pos (%i, %i, %i)\n", x,y,z);

    int i = 0;
    for (int pz = 0; pz < d; ++pz) {
        for (int py = 0; py < h; ++py) {
            for (int px = 0; px < w; ++px) {
                Vec3 n(px * _actual - 1.0, py * _actual - 1.0, pz * _actual - 1.0);
                float d = eval(n);
                if (d<=0){
                    i = px + h * (py + w * pz);
                    data[i] = compressMaterial(n, .5);//0xFFFFFFFFu;
                }
            }
        }
    }
    
    
//    for (uint32 i = 0; i<l; i++) {
//        Vec3 n(x * _actual - 1.0, y * _actual - 1.0, z * _actual - 1.0);
//        float d = eval(n);
//        if (d<=0){
//            
//            data[i] = compressMaterial(n, .5);//0xFFFFFFFFu;
//        }
//    }
}

bool IsoSurfaceLoader::isBlockEmpty(int x, int y, int z) {
  Vec3 v(x * _actual - 1.0, y * _actual - 1.0, z * _actual - 1.0);
  return eval(v) <= 0;
}

void IsoSurfaceLoader::teardownBlockProcessing() {

}

void IsoSurfaceLoader::convertToVolume(const char *path, int maxSize, size_t memoryBudget) {

}
