project(wab_advanced_qf_py)

set(includes ../wab_advanced_quant_fi/includes/)
set(sources src/pybind_wrapper.cpp)

message(STATUS "[===] Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message(STATUS "[===] Python3_LIBRARIES: ${Python3_LIBRARIES}")
message(STATUS "[===] Python3_EXECUTABLE: ${Python3_EXECUTABLE}")

# Create Python module named 'wab_advanced_qf_py' (matches PYBIND11_MODULE name)
pybind11_add_module(wab_advanced_qf_py ${sources})
target_include_directories(wab_advanced_qf_py PUBLIC ${includes} ${Python3_INCLUDE_DIRS})
target_link_libraries(wab_advanced_qf_py PUBLIC wab_advanced_quant_fi ${Python3_LIBRARIES})

# Get Python site-packages directory
execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_path('purelib'))"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Install Python module to python/ directory in install prefix for easy PYTHONPATH setup
install(TARGETS wab_advanced_qf_py
    COMPONENT python
    LIBRARY DESTINATION python
)

# Also create a setup helper script
install(CODE "
    message(STATUS \"========================================\")
    message(STATUS \"Python module installed to: ${CMAKE_INSTALL_PREFIX}/python\")
    message(STATUS \"To use the module, add to your PYTHONPATH:\")
    message(STATUS \"  export PYTHONPATH=${CMAKE_INSTALL_PREFIX}/python:\$PYTHONPATH\")
    message(STATUS \"Or from Python:\")
    message(STATUS \"  import sys\")
    message(STATUS \"  sys.path.insert(0, '${CMAKE_INSTALL_PREFIX}/python')\")
    message(STATUS \"Then: import wab_advanced_qf_py\")
    message(STATUS \"========================================\")
")