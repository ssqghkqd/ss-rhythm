# 编译器设置
message(STATUS "C编译器：${CMAKE_C_COMPILER}")
message(STATUS "C++编译器：${CMAKE_CXX_COMPILER}")

# 编译器警告配置
function(set_target_warnings target)
        target_compile_options(${target} PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Wno-gnu-statement-expression   # 新增：放过 GNU 语句表达式
                -Wshadow
                -Wunused
                -Werror
        )
endfunction()

function(set_linker target)
        target_link_options(${target} PRIVATE 
                -fuse-ld=lld
                $<$<CONFIG:Release>:-flto>
        )

endfunction()

function(set_fast_options target)
    target_compile_options(${target} PRIVATE
            -march=native
            -ffast-math
    )
endfunction()

# C++标准配置
function(set_cpp_standard target standard)
    set_target_properties(${target} PROPERTIES
            CXX_STANDARD ${standard}
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
    )
endfunction()