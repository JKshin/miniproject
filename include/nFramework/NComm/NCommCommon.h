#pragma once
#pragma warning(disable:4251)
#pragma warning(disable:4996)

#ifdef NCOMM_EXPORTS
#define NCOMMDLL_API __declspec(dllexport)
#else
#define NCOMMDLL_API __declspec(dllimport)
#endif

#define defaultBufferSize 65536

#include <iostream>

enum ProtocolType{TCP = 1, UDP = 2};
enum ServerRoleType{SENDER = 1, RECEIVER = 2};
enum CastType{UNICAST = 1, BROADCAST = 2, MULTICAST = 3};
