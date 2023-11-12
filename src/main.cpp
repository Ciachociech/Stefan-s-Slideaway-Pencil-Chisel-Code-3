#include <window/WindowInstance.h>

int main()
{
    window::WindowInstance instance(1280, 720, "bulonais-3");
    instance.setFrameRate(60);
    return instance.loop();
}