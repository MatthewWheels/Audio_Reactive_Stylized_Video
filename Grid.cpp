//
//  Grid.cpp
//  Grids
//
//  Created by Matthew Wheeler on 1/29/20.
//

#include "Grid.hpp"

void Gridclass::setup(int _y){
   
    
    
//    //-------------------STATIC COLOR----------------
//    //These set the max RGB values of the lowlight color
//    lRed=90;
//    lGreen=0;
//    lBlue=90;
//
//
//
//    //These set the max RGB values of the highlight color
//    hRed=0;
//    hGreen=255;
//    hBlue=255;
//    //---------------------------------------------------
    
    //--------------------DYNAMIC COLORS-------------------
    
       //----LOW COLOR 1-----
    lred1=90;
    lgreen1=0;
    lblue1=90;
    
       //----LOW COLOR 2-----
    lred2=0;
    lgreen2=255;
    lblue2=255;
    
    //----HIGH COLOR 1-----
      hred1=209;
      hgreen1=0;
      hblue1=28;
      
         //----HIGH COLOR 2-----
      hred2=255;
      hgreen2=110;
      hblue2=199;
    
    
   //index is set to -1 so that the first vertex indexed is 0
       index=-1;
    
  
    
    
       glLineWidth(2);
    
    //This creates an array of points to create the triangle strip.
       for(int i=0; i<88; i++){
           
           grid.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
           
           //This set of commands creates 2 vertices starting with one below and then one above before moving along the x axis and repeating.
           //After each individual vertex is added the Index is increased and an index is added for that Vertex.
           
           grid.addVertex(glm::vec3(i*4, _y*4, 0));
           grid.addColor(teal);
           index++;
           grid.addIndex(index);
         grid.addVertex(glm::vec3(i*4, (_y+1)*4, 0));
           index++;
               grid.addColor(teal);
           grid.addIndex(index);
       }
    
}
void Gridclass::update(int _x, ofImage camFrame, float _amp, float _sound, float _truesound){
//            std::cout << "Sound:" << _sound << endl;
    //-------------DYNAMIC COLOR---------------------
    lRed=ofMap(_sound, 0, 255, lred1, lred2);
    lGreen=ofMap(_sound, 0, 255, lgreen1, lgreen2);
    lBlue=ofMap(_sound, 0, 255, lblue1, lblue2);
    
    hRed=ofMap(_sound, 0, 255, hred1, hred2);
    hGreen=ofMap(_sound, 0, 255, hgreen1, hgreen2);
    hBlue=ofMap(_sound, 0, 255, hblue1, hblue2);
    
            //sets the U(pdate)Index to 0
          
             UIndex = 0;
            for(int j =0; j < 88; j++){
                
                
                //Generates the color pixel based on the corresponding color from the webcam.
                    ofColor pixel = camFrame.getColor(((((j* 4)-176)*-1)+176), ((((_x*4)-131)*-1)+131));
          
                
               
                //sets the teal color
                teal.set(ofMap(pixel.getBrightness(), 0, 255, lRed, hRed), ofMap(pixel.getBrightness(), 0, 255, lGreen, hGreen), ofMap(pixel.getBrightness(), 0, 255, lBlue, hBlue));
                
               
               

                
                //Sets the vertex based upon the U(pdate)Index value and the brightness of the pixel color previously generated
                
                grid.setVertex(UIndex, glm::vec3(j * 4, _x*4, pixel.getBrightness()/3*(
                ofMap(_truesound, 0, 255, 1,2))));
                
                
                //sets the color to teal

                  grid.setColor(UIndex,teal);


            
                
                UIndex++;
                
                //this gets the pixel color for the next vertex in the index
                pixel = camFrame.getColor(((((j* 4)-176)*-1)+176), (((((_x+1)*4)-131)*-1)+131));
           
                //sets the vertex and the color of the next vertex in the index
                 grid.setVertex(UIndex, glm::vec3(j * 4, (_x+1)*4, (pixel.getBrightness()/3)*(
                 ofMap(_truesound, 0, 255, 1,2))));
                
                 grid.setColor(UIndex,teal);

                
                UIndex++;
                      
                

         
    }
      
}
void Gridclass::draw(bool _meshState){
    
    
 
    grid.drawWireframe();
    grid.drawVertices();
    if(_meshState==false){
    grid.draw();
    }
    
}
