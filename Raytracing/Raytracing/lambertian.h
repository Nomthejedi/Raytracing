#pragma once
#include "material.h"



class lambertian : public material {
public:
	lambertian(const vec3 a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, std::mt19937_64& rng, std::uniform_real_distribution<double>& unif) const override {
		vec3 target = rec.p + rec.normal + randomInUnitSphere(rng,unif);
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};

