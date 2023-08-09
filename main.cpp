#include "renderer.hpp"

#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <memory>

const int WIDTH = 800;
const int HEIGHT = 600;

class Standalone {
public:
  Standalone()
  {
    surfaceInfo.height = HEIGHT;
    surfaceInfo.width = WIDTH;

    initWindow(surfaceInfo);

    renderer.attach(surfaceInfo);


    // renderer.init();
    // renderer.start();

    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
    renderer.detach();

    glfwDestroyWindow(window);
    glfwTerminate();
  }

private:
  Renderer renderer;
  GLFWwindow *window;
  SurfaceInfo surfaceInfo;

  void initWindow(SurfaceInfo &extent)
  {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(extent.width, extent.height, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    surfaceInfo.hwnd = glfwGetWin32Window(window);
    surfaceInfo.hinstance = GetModuleHandle(nullptr);

    uint32_t glfwExtensionCount;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for (int i = 0; i < glfwExtensionCount; i++) {
      std::cout << glfwExtensions[i] << std::endl;
    }

    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    surfaceInfo.glfwExtensions = extensions;
  }

  static void framebufferResizeCallback(GLFWwindow *window, const int width, const int height)
  {
    Standalone *core = reinterpret_cast<Standalone *>(glfwGetWindowUserPointer(window));
    // core->surfaceInfo->width = width;
    // core->surfaceInfo->height = height;
    core->surfaceInfo.width = 120;
    core->surfaceInfo.height = 64;
    core->surfaceInfo.isResized = true;
  }
};

int main()
{

  try {
    Standalone();
  }
  catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
