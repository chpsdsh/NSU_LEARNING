cmake_minimum_required(VERSION 3.26)
project(NSU_LEARNING C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab6-0
        Lab6-0/lab6-0.c
        Lab6-0/avltree.h
        )
add_executable(Lab9
        Lab9/main.c
        Lab9/graph.c
        Lab9/graph.h
        Lab9/dijkstra.c
        Lab9/dijkstra.h
)
add_executable(Lab8-0
        Lab8-0/main.c
        Lab8-0/graph.c
        Lab8-0/graph.h
        Lab8-0/kruskal.c
        Lab8-0/kruskal.h
)
add_executable(Lab8-1
        Lab8-1/main.c
        Lab8-1/graph.c
        Lab8-1/graph.h
)
add_executable(Lab7
        Lab7/main.c
        Lab7/graph.c
        Lab7/graph.h
)
add_executable(Kosaraju kosaraju/main.c
        kosaraju/main.c
        kosaraju/graph.c
        kosaraju/graph.h
        kosaraju/stack.c
        kosaraju/stack.h
)
