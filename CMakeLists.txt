cmake_minimum_required(VERSION 3.16.2)

project(rbtree)

add_definitions("-Wall -g")

add_executable(main main.cpp rbtree.c)