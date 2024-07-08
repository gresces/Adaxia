################################
# @file: module/CMakeLists.txt #
# @author: Gresces             #
# @date: 2024-6-30             #
################################

# Log
add_library(AdaxiaLog STATIC
    ${MODULE_DIR}/Log/log.cc
)
# Config
add_library(AdaxiaConfig STATIC
    ${MODULE_DIR}/Config/config.cc
)
target_link_libraries(AdaxiaConfig AdaxiaLog)
