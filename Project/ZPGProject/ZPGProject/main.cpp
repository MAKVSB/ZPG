#include <cstdlib>

#include "Application.h"

int main()
{
    try {  
        Application app = Application();
        app.initialization(); //OpenGL inicialization
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}