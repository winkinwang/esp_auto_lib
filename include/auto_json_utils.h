/*********************************************************************/
/* Filename:    auto_json_utils.h                                                                             */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: the header of json parser utils of ESP8266                                           */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*   Create:   2017-02-19                                                           		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2017-02-19    wangyunjin  Created                                                             */
/*     email:wyj0617mail@aliyun.com                                                                  */
/*********************************************************************/

#ifndef _AUTO_JSON_PARSER_H_
#define _AUTO_JSON_PARSER_H_

enum{
    AUTO_JSON_TYPE_NUMBER,
    AUTO_JSON_TYPE_STRING,
    AUTO_JSON_TYPE_SUBJSON,
    AUTO_JSON_TYPE_ARRAYJSON,
    AUTO_JSON_TYPE_MAX
};

typedef void* JSONHANDLE; 
typedef void* JSONPAIRHANDLE; 


JSONHANDLE AIH_json_parse_init(char *jsonStr, int32_t len);

void AIH_json_parse_deinit(JSONHANDLE *pJsonHandle);

JSONPAIRHANDLE AIH_json_parse_get_root_json_pair(JSONHANDLE jsonHandle);

int32_t AIH_json_parse_get_pair_num(JSONPAIRHANDLE jsonPairHandle);

int32_t AIH_json_parse_get_keyword(JSONPAIRHANDLE jsonPairHandle, int32_t id, char *outKeyWord, int32_t maxLen);

int32_t AIH_json_parse_get_id_by_keyword(JSONPAIRHANDLE jsonPairHandle, const char *keyWord, int32_t keyWordLen);

int32_t AIH_json_parse_get_type(JSONPAIRHANDLE jsonPairHandle, int32_t id, int32_t *outType);

int32_t AIH_json_parse_get_int_value(JSONPAIRHANDLE jsonPairHandle, int32_t id, int32_t *outIntValue);

int32_t AIH_json_parse_get_string_value(JSONPAIRHANDLE jsonPairHandle, int32_t id, char *outValue, int32_t maxLen);

JSONPAIRHANDLE AIH_json_parse_get_sub_json(JSONPAIRHANDLE jsonPairHandle, int32_t id);

int32_t AIH_json_parse_get_sub_array_size(JSONPAIRHANDLE jsonPairHandle, int32_t id);

JSONPAIRHANDLE AIH_json_parse_get_sub_array(JSONPAIRHANDLE jsonPairHandle, int32_t id, int32_t subId);

const uint8_t *AIH_json_pair_get_string(JSONPAIRHANDLE jsonPairHandle);

#endif

