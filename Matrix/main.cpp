#include "matrix.h"

int main() {
	vec2 v;
	v.resize(3);
	v[0] = { 0,1,2 };
	v[1] = { 12,25,12 };
	v[2] = { 8,34,15 };
	Matrix m(v);
	Matrix inv(m.inverseMatrix());
	m.show(4);
	inv.show(12);
	(m*inv).show(4);

	system("pause");
}