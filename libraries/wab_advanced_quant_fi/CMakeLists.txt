project(wab_advanced_quant_fi)

set(includes includes/)
set(sources src/linalg.cpp
            src/random.cpp
            src/equity.cpp
            src/fx.cpp
            src/rates.cpp
            src/credit.cpp
)

add_library(${PROJECT_NAME} SHARED ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
    $<INSTALL_INTERFACE:include>
)

# Set proper install name for macOS
set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_NAME_DIR "@rpath"
)

install(TARGETS wab_advanced_quant_fi
    EXPORT wab_advanced_quant_fi-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY includes/
    DESTINATION include/wab_advanced_quant_fi
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)