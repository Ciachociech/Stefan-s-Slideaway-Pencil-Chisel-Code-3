#include <window/WindowInstance.h>

int main()
{
    window::WindowInstance instance(1280, 720, "Stefan's Slideaway - Pencil, Chisel, Code! #3 game");
    instance.setFrameRate(60);
    return instance.loop();
}