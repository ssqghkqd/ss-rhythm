# src/CMakeLists.txt

add_executable(${PROJECT_NAME})

add_subdirectory(core)
add_subdirectory(render)
add_subdirectory(resources)
add_subdirectory(thirdparty_impl)
add_subdirectory(utils)
add_subdirectory(defs)

target_sources(${PROJECT_NAME}
        PRIVATE
        main.cpp
)

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        # $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/thirdparty>
)

# 编译器配置
set_target_warnings(${PROJECT_NAME})
set_cpp_standard(${PROJECT_NAME} 23)
set_linker(${PROJECT_NAME})
set_fast_options(${PROJECT_NAME})


# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
        #Python3::Python
        SDL3::SDL3

        yaml-cpp::yaml-cpp
        glm::glm
        spdlog::spdlog
        EnTT::EnTT
        miniaudio

        bgfx::bx 
        bgfx::bgfx
        bgfx::bimg
        bgfx::bimg_decode

        
)

target_precompile_headers(${PROJECT_NAME} PRIVATE
        <vector>
        <string>
        <memory>
        <spdlog/spdlog.h>
        <entt/entt.hpp>
        <glm/glm.hpp>
)







