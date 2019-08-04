#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"
///TODO:
///Implement Shade function that uses ambient, diffuse, specular and texture
class Material
{
public:
	
 Material( const Vector3f& d_color ,const Vector3f& s_color=Vector3f::ZERO, float s=0):
  diffuseColor_( d_color),
  specularColor_(s_color),
  shininess_(s) {
    std::cout << "Material: " << d_color[0] << d_color[1] << d_color[2] << std::endl; 
  }

  virtual ~Material() {}

  virtual Vector3f getDiffuseColor() const 
  { 
    return  diffuseColor_;
  }
    

  Vector3f Shade( const Ray& ray, const Hit& hit,
                  const Vector3f& dirToLight, const Vector3f& lightColor );

  void loadTexture(const char * filename){
    t_.load(filename);
  }
 protected:
  Vector3f diffuseColor_;
  Vector3f specularColor_;
  float shininess_;
  Texture t_;
};



#endif // MATERIAL_H
