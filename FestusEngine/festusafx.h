// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <assert.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stdarg.h>
#include <mutex>
#include <fstream>

using std::string;

#include <glew.h>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bimap.hpp>

#include "FreeImage.h"

#include "json/json.h"

#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/OpenGL/GL3Renderer.h"

#include "Math/FestusMath.h"
#include "Debug.h"
#include "Transform.h"
#include "MappedValues.h"
#include "TypeID.h"
#include "Event.h"

#include "FestusTime.h"
#include "Input.h"
#include "ResourceManager.h"
#include "FileManager.h"
#include "Window.h"
#include "RenderingEngine.h"
#include "EventSystem.h"
#include "GUI.h"
#include "CoreEngine.h"
#include "SaveManager.h"


#include "Globals.h"


typedef std::int8_t I8;
typedef std::int16_t I16;
typedef std::int32_t I32;
typedef std::int64_t I64;

typedef std::uint8_t U8;
typedef std::uint16_t U16;
typedef std::uint32_t U32;
typedef std::uint64_t U64;

typedef std::float_t F32;
typedef std::double_t F64;
// TODO: reference additional headers your program requires here

