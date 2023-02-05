#include <stdio.h>

double old_avg = 0.0;
double new_avg = 0.0;

void avg(double a, double b) {
	new_avg = (old_avg * b) + (a * (1 - b));
	old_avg = new_avg;


int main(void)
{
	float b = 0;
	float K = 0.6;

	while (1)
	{
		scanf("%f", &b);
		avg(b, a);
		printf("%f \n", new_avg);
	}
}