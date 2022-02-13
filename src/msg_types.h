#pragma once
#include "net_headers.h"

#pragma pack(push, 1)
struct msg_header_t {
	uint32_t id	= 0;
	uint32_t size = 0;
};

struct msg_body_t {
	std::vector<uint8_t> data;
};

struct msg_t {
	msg_header_t	header;
	msg_body_t		body;
};
#pragma pack(pop)

