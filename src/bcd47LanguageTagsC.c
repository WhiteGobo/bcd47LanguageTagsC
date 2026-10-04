#include <stdio.h>
#include <string.h>
#include "bcd47LanguageTagsC.h"

// uses `https://github.com/wooorm/bcp-47-match`_ as reference

/*
typedef struct s_qq {
    language: null,
    script: null,
    region: null,
    variants: []
    extensions: [],

    extendedLanguageSubtags: [],
    irregular: null,
    privateuse: [],
    regular: null,
} qq
*/


bool basic_match_language_tag(const char* filter, const char* lang){
	size_t l_filter, l_lang;
	if (filter == NULL || lang == NULL){
		return false;
	}
	if (0 == strcmp(filter, "*")){
		return true;
	}
	if (0 == strcmp(filter, lang)){
		return true;
	}
	// filter+'-' in lang
	l_filter = strlen(filter);
	l_lang = strlen(lang);
	for(int i = 0; i<l_lang-l_filter-1; i++){
		if (0 == memcmp(filter, lang+i, l_filter)){
			if(lang[i+l_filter] == '-'){
				return true;
			}
		}
	}
	return false;
}

typedef struct s_LangPart{
	const char* x;
	size_t l;
} LangPart;

static bool LangPart_equal(LangPart left, LangPart right){
	if (left.l != right.l){
		return false;
	}
	return 0 == memcmp(left.x, right.x, left.l);
}

static bool LangPart_is_wildcard(LangPart x){
	if (x.l == 0){
		return false;
	}
	return x.x[0] == '*';
}

static bool qq(LangPart* filter, size_t filter_l, LangPart* lang, size_t lang_l)
{
	size_t filter_i = 0, lang_i = 0;
	while(
			filter_i < filter_l
			&& lang_i < lang_l
			&& !(filter[filter_i].x == NULL)
	){
		if(LangPart_is_wildcard(filter[filter_i])){
			filter_i++;
		} else if (lang[lang_i].x == NULL){
			return false;
		} else if (LangPart_equal(filter[filter_i], lang[lang_i])){
			lang_i++;
			filter_i++;
		} else if (lang[lang_i].l == 1){
			return false;
		} else {
			lang_i++;
		}
	}
	return true;
}

static int part_lang_tag(const char* tag, LangPart* dst, size_t dst_l){
	size_t i = 0, j=0;
	const char* tmp;
	tmp = tag;
	while(tag[i] != '\0'){
		if(tag[i] == '-'){
			dst[j].x = tmp;
			dst[j].l = tag + i - tmp;
			tmp = tag + i + 1;
			j++;
			if (j>=dst_l){
				return 1;
			}
		}
		i++;
	}
	dst[j].x = tmp;
	dst[j].l = tag + i - tmp;
	return 0;
}

bool extended_match_language_tag(const char* filter, const char* lang){
	int err;
	LangPart filter_parts[6] = {
		{NULL,0},{NULL,0},{NULL,0},{NULL,0},{NULL,0},{NULL,0}
	};
	LangPart lang_parts[6] = {
		{NULL,0},{NULL,0},{NULL,0},{NULL,0},{NULL,0},{NULL,0}
	};

	err = part_lang_tag(filter, filter_parts, 6);
	if (err != 0){
		return false;
	}
	err = part_lang_tag(lang, lang_parts, 6);
	if (err != 0){
		return false;
	}
	return qq(filter_parts, 6, lang_parts, 6);
}
