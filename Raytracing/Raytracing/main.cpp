#include <iostream>
#include <fstream> 
#include "hitableList.h"
#include "float.h"
#include "sphere.h"
#include "camera.h"
#include <random>
#include <chrono>
#include "lambertian.h"
#include "metal.h"



		

vec3 color(const ray& r,hitable *world, int depth,
	std::mt19937_64& rng, std::uniform_real_distribution<double>& unif)
{
	hit_record rec;
	if (world->hit(r,0.001,FLT_MAX,rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered,rng,unif))
		{
			return  attenuation * color(scattered, world, depth + 1,rng,unif);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
	
}

int main() {
	std::ofstream of("output.ppm");
	if (of.is_open())
	{
		int nx = 200;
		int ny = 100;
		int ns = 100;

		camera cam;

		hitable* list[4];
		list[0] = new sphere(vec3(0, 0, -1), 0.5,new lambertian(vec3(0.8,0.3,0.3)));
		list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
		list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
		list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));

		hitable* world = new hitableList(list, 4);

		std::mt19937_64 rng;
		// initialize the random number generator with time-dependent seed
		uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
		rng.seed(ss);
		// initialize a uniform distribution between 0 and 1
		std::uniform_real_distribution<double> unif(0, 1);

		of << "P3\n" << nx << " " << ny << "\n255\n";
		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				vec3 col(0, 0, 0);
				for (int s = 0; s < ns; s++)
				{
					float u = float(i+unif(rng)) / float(nx);
					float v = float(j+unif(rng)) / float(ny);
					ray r = cam.get_ray(u,v);

					vec3 p = r.point_at_parameter(2.0);
					col = col + color(r, world,0,rng,unif);
				}
				
				col = col/ float(ns);
				col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
				int ir = int(255.99 * col[0]);
				int ig = int(255.99 * col[1]);
				int ib = int(255.99 * col[2]);
				of << ir << " " << ig << " " << ib << "\n";
			}
		}
	}
	else
		std::cout << "erreur lors de l'ouverture ";
	
}