cmake_minimum_required(VERSION 3.22)

# Pull components from the parent project so tests can live next to the code
# they cover (components/<name>/test/).
set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../components")

# Only pull in the components that are actually needed to build the test
# harness; keeps host-target (linux) builds fast and free of dependencies
# that may not support the linux target.
set(COMPONENTS main counter unity)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(faetter_BR-project-tests)
