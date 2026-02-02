cmake_minimum_required(VERSION 3.26)

set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

include_directories(Headers)


add_executable(${MAIN_EXECUTABLE_NAME}
        # Surse
        src/main.cpp
        src/Cat.cpp
        src/CatOverlord.cpp
        src/Actions.cpp
        src/Humanity.cpp
        src/Mission.cpp

        # Headere
        Headers/Cat.h
        Headers/CatOverlord.h
        Headers/Actions.h
        Headers/Humanity.h
        Headers/Mission.h
        Headers/Exceptions.h
        Headers/GameSettings.h
        Headers/GenericTracker.h
        Headers/Utils.h
)

# Activează Sanitizers pentru a prinde erori de memorie/stivă
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

# Copiere fișier de date (Schimbă 'tastatura.txt' în 'cats.txt' dacă așa se numește fișierul tău)
copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()