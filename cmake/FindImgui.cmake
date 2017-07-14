#
# Try to find imgui library and include path.
# Once done this will define
#
# IMGUI_FOUND
# IMGUI_INCLUDE_DIR
# IMGUI_LIBRARY
# 

SET(IMGUI_SEARCH_PATHS
	$ENV{IMGUI_ROOT}
	${DEPENDENCIES_ROOT}
	/usr/local
	/usr)

FIND_PATH(IMGUI_INCLUDE_DIR
    NAMES
        imgui.h
    PATHS
        ${IMGUI_SEARCH_PATHS}
    PATH_SUFFIXES
        include
    DOC
        "The directory where imgui/imgui.h resides"
)

FIND_LIBRARY(IMGUI_LIBRARY
    NAMES
       imgui.lib
    PATHS
        ${IMGUI_SEARCH_PATHS}
    PATH_SUFFIXES
        lib
    DOC
        "The directory where imgui.lib resides"
)

SET(IMGUI_FOUND "NO")
IF (IMGUI_INCLUDE_DIR AND IMGUI_LIBRARY)
    SET(IMGUI_LIBRARIES ${IMGUI_LIBRARY})
    SET(IMGUI_FOUND "YES")
ENDIF (IMGUI_INCLUDE_DIR AND IMGUI_LIBRARY)
