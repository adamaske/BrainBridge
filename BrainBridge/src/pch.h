#pragma once
//Avoid redefinition errors
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <map>
#include <memory>
#include <future>
#include <windows.h>
#include <winsock2.h>
#include <mstcpip.h	>
#include <ws2tcpip.h>
#include <rpc.h		>
#include <ntdsapi.h	>
#include <cstdlib>
#include <functional>
#include <thread>
#include "Core/BBGUID.h";
#include <algorithm>
#define BB_ERROR            (-1)

