﻿#ifndef COLOR_H
#define COLOR_H

#include <Windows.h>

#include <d3dx9.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 色保存するための構造体
	/// </summary>
	struct Color
	{
	public:
		/// <summary>
		/// 色の構成要素
		/// </summary>
		enum class COMPONENTS
		{
			ALPHA,
			RED,
			GREEN,
			BLUE,
		};
		
		/// <remarks>
		/// 初期値は非透明の白0xFFFFFFFF
		/// </remarks>
		Color() {};
		Color(DWORD colorCode) 
		{
			(*this) = colorCode;
		}

		Color(BYTE alpha, BYTE red, BYTE green, BYTE blue)
			:m_alpha(alpha), m_red(red), m_green(green), m_blue(blue)
		{};
		
		inline DWORD GetColorCode() const
		{
			return D3DCOLOR_ARGB(m_alpha, m_red, m_green, m_blue);
		}

		BYTE m_alpha = 255;
		BYTE m_red   = 255;
		BYTE m_green = 255;
		BYTE m_blue  = 255;
		
		/// <summary>
		/// 添え字でアクセスできる色を変える
		/// </summary>
		/// <param name="colorComponent">アクセスする色のCOMPONENTS</param>
		/// <returns>アクセスした色の参照</returns>>
		BYTE& operator[](COMPONENTS colorComponent)
		{
			switch (colorComponent)
			{
			case COMPONENTS::ALPHA:
				return m_alpha;

			case COMPONENTS::RED:
				return m_red;

			case COMPONENTS::GREEN:
				return m_green;

			case COMPONENTS::BLUE:
				return m_blue;

			default:
				return m_blue;
			}
		}
		
		/// <summary>
		/// カラーコードを分解し保存する
		/// </summary>
		/// <param name="colorCode">代入するカラーコード</param>
		/// <returns>thisの参照</returns>
		Color& operator=(DWORD colorCode)
		{
			const int COLOR_COMPONENTS_NUM_MAX = 4;
			const COLOR_COMPONENTS colorComponents[COLOR_COMPONENTS_NUM_MAX] =
			{
				COLOR_COMPONENTS::ALPHA,
				COLOR_COMPONENTS::RED,
				COLOR_COMPONENTS::GREEN,
				COLOR_COMPONENTS::BLUE
			};

			const int ONE_COLOR_BITS = 8;

			for (int i = 0; i < COLOR_COMPONENTS_NUM_MAX; ++i)
			{
				(*this)[colorComponents[i]] = (colorCode & 0xFF000000) >> ONE_COLOR_BITS * (COLOR_COMPONENTS_NUM_MAX - 1 - i);
			}

			return *this;
		}

		/// <summary>
		/// 引数の色と自身の色を足しその値を返す
		/// </summary>
		/// <param name="rhs">自身と足すColor構造体</param>
		/// <returns>足した結果のColor構造体</returns>
		const Color operator+(const Color& rhs) const
		{
			return Color(m_alpha + rhs.m_alpha, m_red + rhs.m_red, m_green + rhs.m_green, m_blue + rhs.m_blue);
		}

		const Color operator+(DWORD rhs) const
		{
			Color rhsColor(GetColorCode());

			return Color((*this) + rhsColor);
		}

		/// <summary>
		/// 引数の色と自身の色を引きその値を返す
		/// </summary>
		/// <param name="rhs">自身と引くColor構造体</param>
		/// <returns>引いた結果のColor構造体</returns>
		const Color operator-(const Color& rhs) const
		{
			return Color(m_alpha - rhs.m_alpha, m_red - rhs.m_red, m_green - rhs.m_green, m_blue - rhs.m_blue);
		}

		const Color operator-(DWORD rhs) const
		{
			Color rhsColor(GetColorCode());

			return Color((*this) - rhsColor);
		}

		/// <summary>
		/// 引数の色と自身の色を足しその値を代入する
		/// </summary>
		/// <param name="rhs">自身と足すColor構造体</param>
		/// <returns>thisの参照</returns>
		const Color operator+=(const Color& rhs)
		{
			(*this) = (*this) + rhs;

			return *this;
		}

		const Color operator+=(DWORD rhs)
		{
			(*this) = (*this) + rhs;

			return *this;
		}

		/// <summary>
		/// 引数の色と自身の色を引きその値を代入する
		/// </summary>
		/// <param name="rhs">自身と引くColor構造体</param>
		/// <returns>thisの参照</returns>
		const Color operator-=(const Color& rhs)
		{
			(*this) = (*this) - rhs;

			return *this;
		}

		const Color operator-=(DWORD rhs)
		{
			(*this) = (*this) - rhs;

			return *this;
		}

		/// <summary>
		/// 引数の値でメンバを掛ける
		/// </summary>
		/// <param name="rhs">掛ける際の値</param>
		/// <returns>掛けた後の結果のColor構造体</returns>
		const Color operator*(float rhs) const
		{
			return Color(
				static_cast<BYTE>(m_alpha * rhs), 
				static_cast<BYTE>(m_red * rhs), 
				static_cast<BYTE>(m_green * rhs), 
				static_cast<BYTE>(m_blue * rhs));
		}

		/// <summary>
		/// 引数の値でメンバを掛けその値を代入する
		/// </summary>
		/// <param name="rhs">掛ける際の値</param>
		/// <returns>thisの参照</returns>
		Color& operator*=(float rhs)
		{
			(*this) = (*this) * rhs;

			return *this;
		}

		/// <summary>
		/// 引数の値でメンバを割る
		/// </summary>
		/// <param name="rhs">割る際の値</param>
		/// <returns>割った後の結果のColor構造体</returns>
		const Color operator/(int rhs) const
		{
			return Color(
				static_cast<BYTE>(m_alpha / rhs),
				static_cast<BYTE>(m_red / rhs),
				static_cast<BYTE>(m_green / rhs),
				static_cast<BYTE>(m_blue / rhs));
		}

		/// <summary>
		/// 引数の値でメンバを割りその値を代入する
		/// </summary>
		/// <param name="rhs">割る際の値</param>
		/// <returns>thisの参照</returns>
		Color& operator/=(int rhs)
		{
			(*this) = (*this) / rhs;

			return *this;
		}
	};
}

#endif //! COLOR_H
