add_executable(test_jacobian test_jacobian.cpp)
target_link_libraries(test_jacobian PRIVATE miso Eigen3::Eigen)
add_executable(test_rational test_rational.cpp)
target_link_libraries(test_rational PRIVATE miso Eigen3::Eigen)
