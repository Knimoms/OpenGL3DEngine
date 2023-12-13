#include "Application3D.h"

int main(void)
{
	Application3D app("Knimoms fancy 3D Engine", 1920, 1080, 45.f, 0.1f, 100.f);
	app.Run();
	return 0;
}