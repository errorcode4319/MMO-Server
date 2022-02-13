#pragma once
#include "msg_types.h"

class MessageQueue {

public:
	MessageQueue() {

	}
	~MessageQueue() {

	}
	msg_t pop() {
		std::scoped_lock lock(mMsgQMut);
		auto t = std::move(mMsgQ.front());
		mMsgQ.pop_front();
		return t;
	}
	std::vector<msg_t> pop_all() {
		std::vector<msg_t> msg_list;
		std::scoped_lock lock(mMsgQMut);
		for (int i = 0, len = mMsgQ.size(); i < len; i++) {
			msg_list.emplace_back(std::move(mMsgQ[i]));
		}
		mMsgQ.clear();
		return msg_list;
	}
	void push(const msg_t& msg) {
		std::scoped_lock lock(mMsgQMut);
		mMsgQ.emplace_back(std::move(msg));	
	}
	size_t size() {
		std::scoped_lock lock(mMsgQMut);
		return mMsgQ.size();
	}

protected:
	std::mutex			mMsgQMut;
	std::deque<msg_t>	mMsgQ;
};