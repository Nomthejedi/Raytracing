#pragma once
#include "hitable.h"
class sphere :
    public hitable
{
    public:
        sphere() {};
        sphere(vec3 cen, float r,material* mat) : center(cen), radius(r),material(mat) {};
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        vec3 center;
        float radius;
        material* material;
};

