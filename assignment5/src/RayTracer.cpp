#include "ArgsParser.h"
#include "RayTracer.h"
#include "Camera.h"
#include "Ray.h"
#include "Hit.h"
#include "Group.h"
#include "Material.h"
#include "Light.h"

#define EPSILON 0.001

//IMPLEMENT THESE FUNCTIONS
//These function definitions are mere suggestions. Change them as you like.
Vector3f mirrorDirection( const Vector3f& normal, const Vector3f& incoming)
{
  return (incoming - 2 * Vector3f::dot(incoming, normal) * normal).normalized();
}

bool transmittedDirection( const Vector3f& normal, const Vector3f& incoming, 
        float index_n, float index_nt, 
        Vector3f& transmitted)
{
  float dn = Vector3f::dot(incoming, normal);

  if (pow(index_n, 2.0f) * (1 - pow(dn, 2.0f))/pow(index_nt, 2.0f) < 1.0f) {
    transmitted = index_n / index_nt * (incoming - normal * dn) - 
      sqrt(1.0f - pow(index_n, 2.0f) * (1 - pow(dn, 2.0f))/(pow(index_nt, 2.0f))) * normal;
    return true;
  }

  return false;
}

RayTracer::RayTracer(SceneParser* parser, Args args) :
  g(parser->getGroup()),
  sceneParser_(parser),
  args_(args),
  m_maxBounces(args_.maxBounces) {}

RayTracer::~RayTracer()
{
}

Vector3f RayTracer::traceRay( Ray& ray, float tmin, int bounces,
        float refr_index, Hit& hit ) const
{
  if (bounces > m_maxBounces) return Vector3f(0, 0, 0);

  Vector3f ambientLight(sceneParser_->getAmbientLight());
  int numLight = sceneParser_->getNumLights();
  if (this->g->intersect(ray, hit, tmin)) {
    Material* material = hit.getMaterial();
    Vector3f color = material->getDiffuseColor() * ambientLight;

    // Shadow
    for (int k = 0; k < numLight; ++k) {
      Vector3f dirLight;
      Vector3f colorLight;
      float disToLight;
      bool lightHaveEffect = true;
      Light* l = sceneParser_->getLight(k);
      l->getIllumination(ray.pointAtParameter(hit.getT()), dirLight, colorLight, disToLight);
      if (args_.haveShadow) {
        Vector3f hitPoint = ray.pointAtParameter(hit.getT());
        Ray shadowRay(hitPoint, dirLight.normalized());
        Hit hit2 = Hit();
        if (g->intersect(shadowRay, hit2, tmin + EPSILON)) {
          lightHaveEffect = false;
        }
      }
      if (lightHaveEffect) {
         color += (material->Shade(ray, hit, dirLight, colorLight) * material->getDiffuseColor());
      }
    }

    // Reflection
    Vector3f reflectedRayDir = mirrorDirection(hit.getNormal(), ray.getDirection());
    Vector3f hitPoint = ray.pointAtParameter(hit.getT());
    Ray reflectRay(hitPoint, reflectedRayDir);
    Vector3f reflectionColor = traceRay(reflectRay, tmin + EPSILON, bounces + 1, material->getRefractionIndex(), hit) * material->getSpecularColor();

    // Refraction
    Vector3f transmittedRayDir;
    Vector3f refractionColor = Vector3f::ZERO;
    bool haveRefraction = false;

    Vector3f n = hit.getNormal().normalized();
    float nt = material->getRefractionIndex();
    if (nt > 0) {
      if (Vector3f::dot(hit.getNormal(), ray.getDirection()) >=0) {
        nt = 1.0;
        n = -n;
      }

      if (transmittedDirection(n, ray.getDirection(), refr_index, nt, transmittedRayDir)) {
        Ray refractionRay(hitPoint, transmittedRayDir);
        refractionColor = traceRay(refractionRay, tmin + EPSILON, bounces + 1, material->getRefractionIndex(), hit) * material->getSpecularColor();
        haveRefraction = true;
      }

      float r0 = pow((nt - refr_index) / (refr_index + nt), 2.0f);
      float c;
      float r = 1.0f;
      if (haveRefraction) {
        if (nt >= refr_index) {
          c = abs(Vector3f::dot(hit.getNormal().normalized(), ray.getDirection().normalized()));
        } else {
          c = abs(Vector3f::dot(transmittedRayDir.normalized(), hit.getNormal().normalized()));
        }
        r = r0 + (1 - r0) * pow(1 - c, 5.0f);
        color += r * reflectionColor;
        color += (1 - r) * refractionColor;
      } else {
        color += reflectionColor;
      }

    } else {
      color += reflectionColor;
    }

    return color;
  }

  return this->sceneParser_->getBackgroundColor(ray.getDirection());
}
