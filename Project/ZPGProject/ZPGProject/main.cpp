//Login MAK0065

#include "Application.h"

int main(void)
{
    try {
        Application* app = new Application();
        app->initialization(); //OpenGL inicialization
        app->run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        // You can also log the error, clean up resources, and gracefully exit here
        return 1; // Return a non-zero exit code to indicate an error
    }
}