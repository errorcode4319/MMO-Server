#include "message_wrapper.h"


int MessageWrapper::read(size_t offset, uint8_t* pData, size_t size) {
	assert(mpMsg == nullptr);
	size_t body_size = mpMsg->body.data.size();
	if (body_size > offset + size) return -1;
	std::memcpy(pData, mpMsg->body.data.data() + offset, size);
	return 0;
}

int MessageWrapper::write(uint8_t* pData, size_t size) {
	assert(mpMsg == nullptr);
	size_t body_size = mpMsg->body.data.size();
	mpMsg->body.data.resize(body_size + size);
	std::memcpy(mpMsg->body.data.data() + body_size, pData, size);
	mpMsg->header.size = uint32_t(body_size + size);
	return 0;
}

