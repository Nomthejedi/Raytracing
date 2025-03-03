#pragma once
#include "hitable.h"
class hitableList : public hitable
{
public:
	hitableList() {}
	hitableList(hitable** l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	hitable** list;
	int list_size;
};
