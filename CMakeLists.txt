cmake_minimum_required(VERSION 3.20)

project(HospitalEmergencyTriageSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hospital_system
    main.cpp
    hospital_triage_system.cpp
)

target_include_directories(hospital_system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(hospital_tests
    tests/HospitalTests.cpp
    hospital_triage_system.cpp
)

target_include_directories(hospital_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

enable_testing()

add_test(
    NAME hospital_regression_tests
    COMMAND hospital_tests
)

install(
    TARGETS hospital_system
    RUNTIME DESTINATION .
)

install(
    FILES
        README.md
        LICENSE
	patient.txt
    DESTINATION .
)

set(CPACK_GENERATOR "ZIP")

set(CPACK_PACKAGE_NAME "Hospital Emergency Triage System")
set(CPACK_PACKAGE_VERSION "4.0.0")

set(
    CPACK_PACKAGE_FILE_NAME
    "Hospital-Emergency-Triage-System-v4.0-Windows-x64"
)

set(
    CPACK_PACKAGE_DIRECTORY
    "${CMAKE_BINARY_DIR}/packages"
)

include(CPack)