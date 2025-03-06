#pragma once
#include "hitable.h"

#include <random>
class material {
public :
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, std::mt19937_64& rng, std::uniform_real_distribution<double>& unif) const = 0;
};

vec3 random_in_unit_sphere(std::mt19937_64& rng, std::uniform_real_distribution<double>& unif) {
	vec3 p;
	do {
		p = 2.0 * vec3(unif(rng), unif(rng), unif(rng)) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}