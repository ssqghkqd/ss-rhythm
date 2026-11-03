target_sources(${PROJECT_NAME}
        PRIVATE
        file_utils.cpp
        maths.cpp
        log/log.cpp
)

target_precompile_headers(${PROJECT_NAME} PRIVATE
log/log_marco.hpp
)