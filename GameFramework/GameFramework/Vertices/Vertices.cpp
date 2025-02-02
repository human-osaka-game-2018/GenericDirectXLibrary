﻿#include "Vertices.h"

namespace gameframework
{
	Vertices::Vertices()
	{
		DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDevice);
	}

	Vertices::Vertices(const D3DXVECTOR3& center, const RectSize& size)
	{
		SetCenterAndSize(center, size);
	}

	Vertices::Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color)
	{
		SetCenterAndSizeAndColor(center, size, color);
	}

	Vertices::Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs)
	{
		SetCenterAndSizeAndColorAndTextureUVs(center, size, color, textureUVs);
	}

	Vertices::Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs,
		const Degree& rotationX_deg, const Degree& rotationY_deg, const Degree& rotationZ_deg)
	{
		SetCenterAndSizeAndColorAndTextureUVs(center, size, color, textureUVs);

		SetRotationX(rotationX_deg);
		SetRotationY(rotationY_deg);
		SetRotationZ(rotationZ_deg);
	}

	Vertices::~Vertices() {};

	void Vertices::SetPosByTopLeft(const D3DXVECTOR3& topLeft, const RectSize& size)
	{
		m_center.x = topLeft.x + 0.5f * size.m_width;
		m_center.y = topLeft.y + 0.5f * size.m_height;

		m_baseSize = size;
	}

	void Vertices::SetPosBybottomLeft(const D3DXVECTOR3& bottomLeft, const RectSize& size)
	{
		m_center.x = bottomLeft.x + 0.5f * size.m_width;
		m_center.y = bottomLeft.y - 0.5f * size.m_height;

		m_baseSize = size;
	}

	void Vertices::SetPosByTopRight(const D3DXVECTOR3& topRight, const RectSize& size)
	{
		m_center.x = topRight.x - 0.5f * size.m_width;
		m_center.y = topRight.y + 0.5f * size.m_height;

		m_baseSize = size;
	}

	void Vertices::SetPosBybottomRight(const D3DXVECTOR3& bottomRight, const RectSize& size)
	{
		m_center.x = bottomRight.x - 0.5f * size.m_width;
		m_center.y = bottomRight.y - 0.5f * size.m_height;

		m_baseSize = size;
	}

	void Vertices::SetCenterAndSize(const D3DXVECTOR3& center, const RectSize& size)
	{
		SetCenter(center);
		SetSize(size);
	}

	void Vertices::SetCenterAndSizeAndColor(const D3DXVECTOR3& center, const RectSize& size, const Color& color)
	{
		SetCenterAndSize(center, size);
		SetColor(color);
	}

	void Vertices::SetCenterAndSizeAndColorAndTextureUVs(const D3DXVECTOR3& center, const RectSize& size, const Color& color,
		const TextureUVs& textureUVs)
	{
		SetCenterAndSizeAndColor(center, size, color);
		SetTextureUVs(textureUVs);
	}

	void Vertices::Flash(int flashFrameMax, BYTE alphaMin, BYTE alphaMax)
	{
		m_color.m_alpha = static_cast<BYTE>(algorithm::SwitchMinBetweenMax(m_flashFrameCount, flashFrameMax, alphaMin, alphaMax));
		algorithm::CountUp(&m_flashFrameCount, flashFrameMax);
	}

	void Vertices::FadeIn(int fadeInFrameMax, BYTE orginAlpha, BYTE destAlpha)
	{
		m_color.m_alpha = static_cast<BYTE>(algorithm::MinToMaxByRatio(m_fadeInFrameCount, fadeInFrameMax, orginAlpha, destAlpha));
		algorithm::CountUp(&m_fadeInFrameCount, fadeInFrameMax);
	}

	void Vertices::FadeOut(int fadeOutFrameMax, BYTE orginAlpha, BYTE destAlpha)
	{
		m_color.m_alpha = static_cast<BYTE>(algorithm::MinToMaxByRatio(m_fadeOutFrameCount, fadeOutFrameMax, orginAlpha, destAlpha));
		algorithm::CountUp(&m_fadeOutFrameCount, fadeOutFrameMax);
	}

	void Vertices::Scaling(int scalingFrameMax, float scaleRateMin, float scaleRateMax)
	{
		float scaleRate = algorithm::SwitchMinBetweenMax(m_additionalScaleFrameCount, scalingFrameMax, scaleRateMin, scaleRateMax);
		algorithm::CountUp(&m_additionalScaleFrameCount, scalingFrameMax);

		m_sizeForRender = m_baseSize * scaleRate;

		m_hasUpdatedSize = true;
	}

	void Vertices::ScalingX(int scalingFrameMax, float scaleRateMin, float scaleRateMax)
	{
		float scaleRate = algorithm::SwitchMinBetweenMax(m_additionalScaleFrameCount, scalingFrameMax, scaleRateMin, scaleRateMax);
		algorithm::CountUp(&m_additionalScaleFrameCount, scalingFrameMax);

		m_sizeForRender.m_width = m_baseSize.m_width * scaleRate;

		m_hasUpdatedSize = true;
	}

	void Vertices::ScalingY(int scalingFrameMax, float scaleRateMin, float scaleRateMax)
	{
		float scaleRate = algorithm::SwitchMinBetweenMax(m_additionalScaleFrameCount, scalingFrameMax, scaleRateMin, scaleRateMax);
		algorithm::CountUp(&m_additionalScaleFrameCount, scalingFrameMax);

		m_sizeForRender.m_height = m_baseSize.m_height * scaleRate;

		m_hasUpdatedSize = true;
	}
}
