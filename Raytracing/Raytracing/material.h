#pragma once

#include "hitable.h"

#include <random>
class material {
public :
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, std::mt19937_64& rng, std::uniform_real_distribution<double>& unif) const = 0;
protected :
	vec3 randomInUnitSphere(std::mt19937_64& rng, std::uniform_real_distribution<double>& unif) const {
		vec3 res;
		do {
			res = 2.0 * vec3(unif(rng), unif(rng), unif(rng)) - vec3(1, 1, 1);
		} while (res.squared_length() >= 1.0);
		return res;
	}
};

