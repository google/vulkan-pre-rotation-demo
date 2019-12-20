cmake_minimum_required(VERSION 3.4.1)


add_library(vkdemo SHARED
            src/main/cpp/main.cpp
            src/main/cpp/Engine.cpp
            src/main/cpp/Renderer.cpp
            src/main/cpp/VkHelper.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_library(native_app_glue STATIC
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
target_include_directories(vkdemo PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)

add_subdirectory(../third_party third_party)

add_definitions("-DVK_USE_PLATFORM_ANDROID_KHR")

target_link_libraries(vkdemo android native_app_glue vulkan glm stb log)
