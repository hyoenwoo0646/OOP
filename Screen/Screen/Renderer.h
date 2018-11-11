#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include "Utils.h"

using namespace std;

class Renderer {

	static const int screenSize = 119;
	char		display[screenSize + 1 + 1];
	Position	origin;

	Renderer() : origin(Borland::wherex(), Borland::wherey()) {
		// 랜덤 숫자 시퀀스의 시드값을 10으로 설정하여 동일한 랜덤 숫자가 생성되도록 유도.
		// 디버깅 목적.
		// release시에는 time(nullptr)로 바꾸어 시드값도 랜덤값으로 설정해야 함.
		srand(10);
	}

public:
	static Renderer& getInstance() {
		static Renderer instance;
		return instance;
	}	

	bool checkRange(const string& shape, int pos)
	{
		int sz = shape.size();
		if (pos < 0) {
			if (pos + sz >= 0) return true;
		}
		else {
			if (pos + sz < screenSize) return true;
		}
		return false;
	}

	bool checkRange(int pos)
	{
		return pos >= 0 && pos < (screenSize - 1);
	}

	void clear()
	{
		memset(display, ' ', screenSize);
		display[screenSize] = '\n';
		display[screenSize + 1] = '\0';
	}

	void draw(const string& shape, int pos)
	{
		int dest_pos = pos;
		if (checkRange(shape, pos) == false) return;

		const char* source = shape.c_str();
		int len = shape.size();
		if (pos < 0) {
			source -= pos;
			len += pos;
			dest_pos = 0;
		}
		else if (pos + shape.size() > screenSize - 1) {
			len = screenSize - pos;
		}
		memcpy(display + dest_pos, source, len);
	}

	void render()
	{
		// make sure it should end with proper ending characters.
		display[screenSize] = '\n';
		display[screenSize + 1] = '\0';

		Borland::gotoxy(&origin);
		cout << display;
		Borland::gotoxy(&origin);
	}

	int getScreenLength() { return screenSize; }
};

#endif 
