
#ifndef PCH_H
#define PCH_H

//----------------------------------
// ����ͷ�ļ�
//----------------------------------
#define WIN32_LEAN_AND_MEAN
// Windows ͷ�ļ�
#include <windows.h>
// C++��׼�� ͷ�ļ�
#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <map>
#include <set>
#include <utility>
// ΢�� Detours �� ͷ�ļ�
#include "./Detours/include/detours.h"
//----------------------------------
// �������Ͷ���
//----------------------------------
using VA = unsigned __int64;
using RVA = unsigned int;
template<typename Type>
using Ptr = Type*;

#endif //PCH_H

