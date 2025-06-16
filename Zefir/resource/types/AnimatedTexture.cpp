#include <resource/types/AnimatedTexture.h>

namespace Zefir
{
	bool AnimatedTexture::Load()
	{
		if (!AnimationDataParser::Parse(m_MetaData, m_Path + ".meta"))
		{
			return false;
		}

		Texture::Load();
	}

	Uint16 AnimatedTexture::GetFrameW() const 
	{ 
		return m_MetaData.frameW; 
	}

	Uint16 AnimatedTexture::GetFrameH() const 
	{ 
		return m_MetaData.frameH; 
	}

	Uint16 AnimatedTexture::GetFrameCount() const 
	{ 
		return m_MetaData.frameCount; 
	}

	float AnimatedTexture::GetFrameTime() const 
	{ 
		return m_MetaData.frameTime; 
	}
}