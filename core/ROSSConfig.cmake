GET_FILENAME_COMPONENT(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
INCLUDE(${SELF_DIR}/ROSS-targets.cmake)
GET_FILENAME_COMPONENT(ROSS_INCLUDE_DIRS "${SELF_DIR}/../include" ABSOLUTE)
