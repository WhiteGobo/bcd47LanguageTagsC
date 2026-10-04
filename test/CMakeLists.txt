include(CTest)

add_executable(test_match_language
	test_match_language.c
)

target_link_libraries(test_match_language
	bcd47LanguageTagsC
)

set(testsuffix "bcd47LanguageTagsC::")
add_test(NAME "${testsuffix}test01" COMMAND test_match_language
	"--lang" "de-de" "--range" "de-*"
)
add_test(NAME "${testsuffix}test02" COMMAND test_match_language
	"--lang" "en-GB" "--range" "*"
)
add_test(NAME "${testsuffix}test03" COMMAND test_match_language
	"--lang" "de" "--range" "*"
)
add_test(NAME "${testsuffix}test04" COMMAND test_match_language
	"--lang" "en-GB" "--range" "en"
)
add_test(NAME "${testsuffix}test05" COMMAND test_match_language
	"--lang" "en" "--range" "en"
)
add_test(NAME "${testsuffix}test06" COMMAND test_match_language
	"--lang" "de" "--range" "en" "-i"
)
add_test(NAME "${testsuffix}test07" COMMAND test_match_language
	"--lang" "en-GB" "--range" "*-GB" "--extended"
)
add_test(NAME "${testsuffix}test08" COMMAND test_match_language
	"--lang" "en" "--range" "*-GB" "-i" "--extended"
)
add_test(NAME "${testsuffix}test09" COMMAND test_match_language
	"--lang" "en-GB" "--range" "en-*" "--extended"
)
