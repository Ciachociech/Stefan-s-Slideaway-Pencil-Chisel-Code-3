#include <window/WindowInstance.h>

int main()
{
    window::WindowInstance instance(800, 600, "bulonais-3");
    instance.setFrameRate(60);
    return instance.loop();
}