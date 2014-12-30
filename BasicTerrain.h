
#ifndef BASICTERRAIN_H
#define BASICTERRAIN_H
#include <vector>
using namespace std;

class BasicTerrain
{
    public:
        /*************
        *PUBLIC FUNCTIONS
        **************/
        BasicTerrain(int x,int z);
        void drawTerrain();
        void lineAlgorithm(int n);
        void calculateFaceNormals();

    private:
        /*****************
        *PRIVATE FUNCTIONS
        *****************/
        std::vector<float> normalizedVector(vector<float> a, vector<float> b);
        void calculateVertexNormals();
        /*****************
        *PRIVATE VARIABLES
        ******************/
        int length;
        int width;
        std::vector<vector<float> > heightMap;
        int numberOfLines;
        std::vector<vector<vector<float> > > normalVectors;

};

#endif // BASICTERRAIN_H
