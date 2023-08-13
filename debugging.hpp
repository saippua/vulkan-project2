#pragma once
#ifndef DEBUGGING_HH
#define DEBUGGING_HH

#include <vector>
#include <iostream>
#include <vulkan/vulkan.hpp>

#include "interop.h"

namespace vdb {

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char *> validationLayers = {
  // "VK_LAYER_LUNARG_standard_validation"
  "VK_LAYER_KHRONOS_validation"
};

inline static DebugCallback externalDebugCallback = nullptr;

inline VkDebugUtilsMessengerEXT callback;

inline void debugOutput(const char *msg)
{
  std::cerr << msg << std::endl;
  if (externalDebugCallback) {
    externalDebugCallback(msg);
  }
}

inline static bool checkValidationLayerSupport()

{
  auto availableLayers = vk::enumerateInstanceLayerProperties();
  for (const char *layerName : validationLayers) {
    bool layerFound = false;

    for (const auto &layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}

inline VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pCallback
)
{
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pCallback);
  }
  else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

inline void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT callback,
    const VkAllocationCallbacks *pAllocator
)
{
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, callback, pAllocator);
  }
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData
)
{

  std::cerr << "validation layer: ";
  debugOutput(pCallbackData->pMessage);

  return VK_FALSE;
}

inline void setupDebugCallback(vk::Instance instance)
{
  if (!enableValidationLayers)
    return;

  auto createInfo = vk::DebugUtilsMessengerCreateInfoEXT(
      vk::DebugUtilsMessengerCreateFlagsEXT(),
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
          vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
      vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
          vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
      debugCallback,
      nullptr
  );

  // NOTE: Vulkan-hpp has methods for this, but they trigger linking errors...
  // instance.createDebugUtilsMessengerEXT(createInfo);
  // instance.createDebugUtilsMessengerEXTUnique(createInfo);

  // NOTE: reinterpret_cast is also used by vulkan.hpp internally for all
  // these structs
  if (CreateDebugUtilsMessengerEXT(
          instance,
          reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT *>(&createInfo),
          nullptr,
          &callback
      ) != VK_SUCCESS) {
    throw std::runtime_error("failed to set up debug callback!");
  }
}

} // namespace Debugging

#endif