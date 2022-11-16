#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "./renderer.h"
#include "./inputs.h"

#include "../vendors/nlohmann/json.hpp" 
#include "./shader.h"
#include <iostream>

using string = std::string;
using json = nlohmann::json;

namespace Entities {

	class Sprite {

		public:  

			Shader* m_shader;
			
		    unsigned int m_VBO, m_VAO, m_EBO, m_texture1, m_texture2;

			unsigned char* m_image1;

			bool m_isSpritesheet = false;
			bool m_isAtlas = false;

			int m_frames, 
				m_width,
				m_height,
				m_currentFrame;

			float 
				m_posX, 	
				m_posY,
				m_srcWidth = 1, 
				m_srcHeight = 1,
				m_scaleX = 1,
				m_scaleY = 1,
				m_degrees = 0; 

			std::int64_t 
				m_currentFrameX,
				m_currentFrameY,
				m_currentFrameWidth,
				m_currentFrameHeight;

			json m_resourceData;

			void Render();
			void SetColor(Uint8 red, Uint8 green, Uint8 blue);
			void SetAlpha(Uint8 alpha);
			void SetScale(float scaleX, float scaleY)
			{
				m_scaleX = scaleX;
				m_scaleY = scaleY;
			}
			void SetRotation(float degrees)
			{
				m_degrees = degrees;
			}
			void SetPosition(float x, float y)
			{
				m_posX = x;//-x * 0.001;
				m_posY = y;//-y * 0.001;
			}

			Sprite(GLuint &id, float x, float y, const char* key[2]);
		   ~Sprite();

		private:

			int m_renderMode;
			GLuint m_inst;
			void _SetSubTexture();
	};


	class Player : public Sprite {

		public:

			void Update();
			void Animate(string animKey);

			Player(GLuint &id, float x, float y, const char* key[2]) : Sprite(id, x, y, key){};
			~Player() = default;
	};


	class TileSprite : public Sprite {

		private:

			int m_type;
			GLsizei m_tileWidth = 64,
					m_tileHeight = 64;

			void ShowTile();
			int GetType();

		public:
			
			TileSprite (
				GLuint &id, 
				//std::tuple<int, int> tileType, 
				float posX, 
				float posY, 
				int64_t frameX, 
				int64_t frameY, 
				const char* key[2]
			) 
			:Sprite(id, posX, posY, key)
			{
				SetScale(0.1f, 0.1f);

				m_currentFrameX = frameX; 
				m_currentFrameY = frameY;
                m_currentFrameWidth = m_tileWidth; 
                m_currentFrameHeight = m_tileHeight; 
				m_isAtlas = true;
		        
      
			}
			~TileSprite() = default;
	};
}