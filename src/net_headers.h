#pragma once

// C++ STD
#include<iostream>
#include<thread>
#include<vector>
#include<queue>
#include<chrono>
#include<cstdint>
#include<memory>
#include<cassert>


// BOOST ASIO
#ifdef _WIN32
#define _WIN32_WINNT_0x0A00
#endif 
#include<boost/asio.hpp>
#include<boost/asio/ts/internet.hpp>
#include<boost/asio/ts/buffer.hpp>