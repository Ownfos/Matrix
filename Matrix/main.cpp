#include "matrix.h"

int main() {
	Matrix m(
		{
			{1, 2, 3},
			{3, 2, 1},
			{2, 3, 1}
		}
	);
	m.show();

	Matrix inv(m.inverseMatrix());
	inv.show(10);

	(m*inv).show();

	system("pause");
}