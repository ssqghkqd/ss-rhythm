
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

list(APPEND CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/x64-linux")

find_package(SDL3 CONFIG REQUIRED)
message(STATUS "找到了SDL3")
find_package(EnTT CONFIG REQUIRED)
message(STATUS "找到了entt")
find_package(glm CONFIG REQUIRED)
message(STATUS "找到了glm")
find_package(spdlog CONFIG REQUIRED)
message(STATUS "找到了spdlog")


find_package(yaml-cpp CONFIG REQUIRED)
message(STATUS "找到了yaml-cpp")

# find_package(Python3 REQUIRED COMPONENTS Development)
# message(STATUS "找到了python")

find_package(bgfx CONFIG REQUIRED)
message(STATUS "找到bgfx")


