set(includepath ${CMAKE_CURRENT_SOURCE_DIR})

add_library(bcd47LanguageTagsC
	bcd47LanguageTagsC.c
	bcd47LanguageTagsC.h
)

target_include_directories(bcd47LanguageTagsC PUBLIC
	"${includepath}/"
)

#target_link_libraries(bcd47LanguageTagsC PUBLIC
#)
