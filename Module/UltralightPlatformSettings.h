#pragma once

namespace CryUltralight
{

class CUltralightPlatformSettings
{
public:
	void Initial(int width, int height);

	inline int width() { return m_width; }
	inline int height() { return m_height; }
private:
	int m_width = 0;
	int m_height = 0;
};

}
