cmake_minimum_required(VERSION 3.5)

set(Boost_INCLUDE_DIR $ENV{Boost_INCLUDE_DIR})

configure_file(./config.hpp.in ./config.hpp)

find_package(Boost REQUIRED COMPONENTS program_options)

set(TARGET soup)
set(SOURCES
        main.cpp
        models/account.hpp
        models/account.cpp
        persistence/persistence.hpp
        persistence/persistence.cpp
        persistence/account.hpp
        persistence/account.cpp
        manager.hpp
        manager.cpp
)

add_executable(
    ${TARGET}
    ${SOURCES}
)

target_link_libraries(${TARGET} PRIVATE Boost::boost Boost::program_options)
