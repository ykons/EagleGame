cmake_minimum_required(VERSION 3.28)
project(EagleGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main
    src/main.cpp
    src/Application.cpp
    src/World.cpp
    src/Entity.cpp
    src/SceneNode.cpp
    src/SpriteNode.cpp
    src/Aircraft.cpp
    src/Command.cpp
    src/CommandQueue.cpp
    src/Player.cpp
    src/State.cpp
    src/StateStack.cpp
    src/TitleState.cpp
    src/MenuState.cpp
    src/GameState.cpp
    src/LoadingState.cpp
    src/PauseState.cpp
    src/SettingsState.cpp
    src/Utility.cpp
    src/Container.cpp
    src/Component.cpp
    src/Button.cpp
    src/Label.cpp
    src/ParallelTask.cpp
    src/TextNode.cpp
    src/DataTables.cpp
    src/GameOverState.cpp
    src/Pickup.cpp
    src/Projectile.cpp
    src/ParticleNode.cpp
    src/Animation.cpp
    src/BloomEffect.cpp
    src/EmitterNode.cpp
    src/PostEffect.cpp
    )
target_include_directories(main PRIVATE include)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

add_custom_command(TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${CMAKE_SOURCE_DIR}/assets"
  "$<TARGET_FILE_DIR:main>/assets"
)
