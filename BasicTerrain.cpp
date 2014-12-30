#include "BasicTerrain.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
using namespace std;

float RandomFloa(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

BasicTerrain::BasicTerrain(int x, int z)
{
    length = x;
    width = z;
    std::vector<vector<float> > height(width,vector<float>(length));
    std::vector<float> rows(length);
    for(int i = 0;i<width;i++){
        height[i] = rows;
        for(int j = 0;j<length;j++){
            height[i][j] = 1;
        }
    }
    heightMap = height;
}

/******************************************
*Sets the heightMap vector to random heights between
*2 numbers
*******************************************/

void BasicTerrain::drawTerrain()
{
    //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    for(int z = 0;z<width-1;z++){
        glBegin(GL_QUAD_STRIP);
            for(int x = 0;x<length-1;x++){
                if(z == width-2){
                    //glColor3f(0,0,1);
                }
                else if(x == length-2){
                    //glColor3f(0,1,0);
                }
                else //glColor3f(1,0,0);

                glNormal3f(normalVectors[z+1][x][0],normalVectors[z+1][x][1],normalVectors[z+1][x][2]);

               // printf("normals of p%d,%d = %f, y = %f, z = %f\n",z,x,normalVectors[z+1][x][0],normalVectors[z+1][x][1],normalVectors[z+1][x][2]);
                glVertex3f(x,heightMap[z+1][x],z+1);

                glNormal3f(normalVectors[z][x][0],normalVectors[z][x][1],normalVectors[z][x][2]);
                glVertex3f(x,heightMap[z][x],z);
            }
        glEnd();
    }
}
void BasicTerrain::lineAlgorithm(int n)
{
    numberOfLines = n;
    float v,a,b,c;
    float d = sqrt(width*width + length*length);
    float increment = 1;
    for(int k = 0;k<numberOfLines;k++){
        v = rand();
        a = sin(v);
        b = cos(v);
        c = RandomFloa(-d/2,d/2);
        for (int z = 0;z<width;z++){
            for(int x = 0;x<length;x++){
                if (a*x + b*z - c > 0)
                    heightMap[z][x] += increment;

                else
                    heightMap[z][x] -= increment;
                }
        }
    }
}
/**
Returns the normalized cross product of two vectors.
Source:http://www.lighthouse3d.com/opengl/terrain/index.php3?normals
*/
std::vector<float> BasicTerrain::normalizedVector(vector<float> a, vector<float> b)
{
    //remember the first indice of a point is the z value, the second is the y, the third is the x.
    std::vector<float> v1(3);
    std::vector<float> v2(3);
    for(int i = 0;i<a.size();i++){
        v1[i] = a[i];
        v2[i] = b[i];
    }

    float vx = v1[1]*v2[0] - v1[0]*v2[1];
    float vy = v1[0]*v2[2] - v1[2]*v2[0];
    float vz = v1[2]*v2[1] - v1[1]*v2[2];

    float length = sqrt(vx*vx+vy*vy+vz*vz);
    std::vector<float> normalizedV(3);
    normalizedV[0] = vz/length;
    normalizedV[1] = vy/length;
    normalizedV[2] = vx/length;
    return normalizedV;
}
/******************************************
*Calculates 1 normal per polygon face by averaging the surrounding vertex normals.
*This is a cheap solution but results in poor lighting.
*Source:
*******************************************/
void BasicTerrain::calculateFaceNormals()
{
    std::vector<vector<vector <float> > > normals(width,vector<vector<float> >(length));
    std::vector<vector<float> > row(length,vector<float> (3));
    std::vector<float> points(3);
    std::vector<float> v1(3);
    std::vector<float> v2(3);

    for(int z = 0;z<width;z++){
        normals[z] = row;
        for(int x = 0;x<length;x++){
            normals[z][x] = points;
            if(x == length-1){
                v1[0] = x-1 - x;
                v1[2] = heightMap[z][x-1] - heightMap[z][x];
                v1[2] = z - z;
            }
            else {
                v1[0] = x+1 - x;
                v1[1] = heightMap[z][x+1] - heightMap[z][x];
                v1[2] = z - z;
            }
            if(z == width-1){
                v2[0] = x-x;
                v2[1] = heightMap[z-1][x] - heightMap[z][x];
                v2[2] = z-1 - z;
            }
            else{
                v2[0] = x - x;
                v2[1] = heightMap[z+1][x] - heightMap[z][x];
                v2[2] = z+1 - z;
            }

            normals[z][x] = normalizedVector(v1,v2);
            printf("normals of p%d,%d = %f, y = %f, z = %d\n",z,x,normals[z][x][0],normals[z][x][1],normals[z][x][2]);
        }
    }
    normalVectors = normals;

}
void BasicTerrain::calculateVertexNormals()
{


}
