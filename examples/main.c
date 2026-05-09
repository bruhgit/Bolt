#define BOLT_IMPLEMENTATION
#include "..\bolt\bolt.h"

int main(void)
{
    bolt_init("Bolt Engine - Hello World", 1280, 720);
    
    while (!bolt_should_close())
    {
        bolt_update();

        bolt_clear_background(BOLT_BLACK);
    }

    bolt_quit();
    return 0;
}