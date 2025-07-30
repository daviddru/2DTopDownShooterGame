cmake_minimum_required(VERSION 3.16)
project(TwinStickShooter)

set(CMAKE_CXX_STANDARD 20)

# Tell CMake where to find SFMLConfig.cmake
set(SFML_DIR "D:/Libraries/SFML-2.6.1/lib/cmake/SFML")  # <- adjust path if needed

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_executable(TwinStickShooter main.cpp
        model/Player.cpp
        model/Player.h
        model/Bullet.cpp
        model/Bullet.h
        model/SoundManager.cpp
        model/SoundManager.h
        model/Zombie.cpp
        model/Zombie.h)

# Add include dir and link SFML
target_include_directories(TwinStickShooter PRIVATE "D:/Libraries/SFML-2.6.1/include")
target_link_libraries(TwinStickShooter PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
