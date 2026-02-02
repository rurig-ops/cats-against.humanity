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

# Spunem compilatorului să caute headerele în folderul Headers
include_directories(Headers)

# Adăugăm TOATE fișierele .cpp din src.
# Scoatem main.cpp și clase.cpp din rădăcină dacă le-ai mutat deja în src.
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        src/Cat.cpp
        src/CatOverlord.cpp
        src/Actions.cpp
        src/Humanity.cpp
        src/Mission.cpp
        # Headerele sunt listate aici pentru a fi vizibile în CLion
        Headers/Exceptions.h
        Headers/Cat.h
        Headers/Actions.h
        Headers/Humanity.h
        Headers/Mission.h
        Headers/CatOverlord.h
        src/CatOverlord.cpp
        src/Mission.cpp
        src/Actions.cpp
        src/Humanity.cpp
        Headers/GameSettings.h
        Headers/GenericTracker.h
        Headers/Utils.h
)

set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})