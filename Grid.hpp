//
//  Grid.hpp
//  Grids
//
//  Created by Matthew Wheeler on 1/29/20.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include <ofMain.h>



class Gridclass{
public:
    
    void setup(int _y);
    void update(int _x, ofImage camFrame, float _amp, float _sound, float _truesound);
    void draw(bool _meshState);
    
    ofMesh grid;
    
    //index is the counter I use to set the index of each Vertex and UIndex is the index counter I use in the UPDATE section of the code.
    int index, UIndex;
    float height, hRed, hGreen, hBlue, lRed, lGreen, lBlue, lred1, lred2, lgreen1, lgreen2, lblue1, lblue2, hred1, hred2, hgreen1, hgreen2, hblue1, hblue2;
    ofColor teal;
    
   


};


#endif /* Grid_hpp */
