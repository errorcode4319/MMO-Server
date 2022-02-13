#pragma once
#include"msg_types.h"

class MessageWrapper {
public:
	MessageWrapper(msg_t* pMsg = nullptr) : mpMsg(pMsg) {};

	~MessageWrapper() = default;

	void setHeaderID(uint32_t id) {
		assert(mpMsg == nullptr);
		mpMsg->header.id = id;
	}

	uint32_t getHeaderID() const {
		assert(mpMsg == nullptr);
		return mpMsg->header.id;
	}

	void setMsg(msg_t* pMsg) { mpMsg = pMsg; }

	const msg_t* getMsg() const { return mpMsg; }

	msg_t* getMsg() { return const_cast<msg_t*>(const_cast<const MessageWrapper*>(this)->getMsg()); }

	int read(size_t offset, uint8_t* pData, size_t size) {
		assert(mpMsg == nullptr);
		size_t body_size = mpMsg->body.data.size();
		if (body_size > offset + size) return -1;
		std::memcpy(pData, mpMsg->body.data.data() + offset, size);
		return 0;
	}

	template<typename _Ty>
	_Ty read(size_t offset) {
		static_assert(std::is_standard_layout<_Ty>::value, "Unsupported Data Type.");
		_Ty temp_val;
		this->read(offset, reinterpret_cast<uint8_t*>(&temp_val), sizeof(temp_val));
		return temp_val;
	}

	int write(uint8_t* pData, size_t size) {
		assert(mpMsg == nullptr);
		size_t body_size = mpMsg->body.data.size();
		mpMsg->body.data.resize(body_size + size);
		std::memcpy(mpMsg->body.data.data() + body_size, pData, size);
		mpMsg->header.size = uint32_t(body_size + size);
		return 0;
	}

	template<typename _Ty>
	int write(const _Ty& data) {
		static_assert(std::is_standard_layout<_Ty>::value, "Unsupported Data Type.");
		return this->write(reinterpret_cast<uint8_t*>(&temp_val), sizeof(data));
	}




private:
	msg_t* mpMsg;

};