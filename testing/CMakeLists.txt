project(testing)

set(includes ./ ../quant_fi/)
set(exe_1 equities)
# set(exe_2 explicit_program)
# set(exe_3 main_date)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} PUBLIC quant_fi)
