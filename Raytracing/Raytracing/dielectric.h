#pragma once
#include "material.h"
class dielectric :
    public material
{
    protected:
        bool refract(const  vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) const
        {
            vec3 uv = unit_vector(v);
            float dt = dot(uv, n);
            float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.f - dt * dt);
            if (discriminant > 0)
            {
                refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
                return true;
            }
            else
                return false;
        }
        float schlick(float cosine, float ref_idx) const {
            float r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }
    public:
        dielectric(float ri) : ref_idx(ri) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, std::mt19937_64& rng, std::uniform_real_distribution<double>& unif) const override {
            vec3 outward_normal;
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            float ni_over_nt;
            attenuation = vec3(1.0, 1.0, 1.0);
            vec3 refracted;
            float reflect_prob;
            float cosine;
            if (dot(r_in.direction(), rec.normal) > 0) {
                outward_normal = -rec.normal;
                ni_over_nt = ref_idx;
                cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
            }

            else {
                outward_normal = rec.normal;
                ni_over_nt = 1.0 / ref_idx;
                cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
            }

            if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
                reflect_prob = schlick(cosine,ref_idx);
            }
            else {
                scattered = ray(rec.p, reflected);
                reflect_prob = 1.0;
            }
            if (unif(rng) < reflect_prob)
            {
                scattered = ray(rec.p, reflected);
            }
            else {
                scattered = ray(rec.p, refracted);
            }
            return true;
        }
        float ref_idx;

};

