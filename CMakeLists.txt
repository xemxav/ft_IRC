cmake_minimum_required(VERSION 3.9)
project(ft_IRC)

set(CMAKE_C99_STANDARD 17)

# Rigourous Error management
set(CMAKE_C_FLAGS "-Wall -Werror -Wall")

add_compile_options(-Wall -Werror -Wall)
# Including *.c and *.h project files
FILE(GLOB_RECURSE SHARED_SOURCE
        src/shared/*.c)

FILE(GLOB_RECURSE SERVEUR_SOURCE
        src/serveur_files/*.c
        includes/*.h)

FILE(GLOB_RECURSE CLIENT_SOURCE
        src/client_files/*.c
        includes/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "~/ft_IRC")
# Build executable
add_executable(serveur ${SERVEUR_SOURCE} ${SHARED_SOURCE})

add_executable(client ${CLIENT_SOURCE} ${SHARED_SOURCE})

find_library(LIBFT ft libft)

target_link_libraries(serveur LINK_PUBLIC ${LIBFT})
target_link_libraries(client LINK_PUBLIC ${LIBFT})

