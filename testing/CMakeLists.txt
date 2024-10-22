project(testing)

set(includes ./ ../quant_fi/)
set(exe_1 equities)
set(exe_2 forex)
set(exe_3 interest_rates)
set(exe_4 credit_risk)

add_executable(${exe_1} ${exe_1}.cpp)
target_include_directories(${exe_1} PUBLIC ${includes})
target_link_libraries(${exe_1} PUBLIC quant_fi)

add_executable(${exe_2} ${exe_2}.cpp)
target_include_directories(${exe_2} PUBLIC ${includes})
target_link_libraries(${exe_2} PUBLIC quant_fi)

add_executable(${exe_3} ${exe_3}.cpp)
target_include_directories(${exe_3} PUBLIC ${includes})
target_link_libraries(${exe_3} PUBLIC quant_fi)

add_executable(${exe_4} ${exe_4}.cpp)
target_include_directories(${exe_4} PUBLIC ${includes})
target_link_libraries(${exe_4} PUBLIC quant_fi)
