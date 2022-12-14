#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "./renderer.h"
#include "./inputs.h"
#include "./resources/manager.h"

#include "../vendors/nlohmann/json.hpp" 

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using string = std::string;
using json = nlohmann::json;

namespace Entities {


	class Sprite {

		public:  

		    unsigned int m_id;

			unsigned char* m_image;

			bool m_isSpritesheet = false,
				 m_isAtlas = false,
				 m_isLoaded = false;

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

			void Render (
				glm::vec2 position, 
				glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, 
				glm::vec3 color = glm::vec3(1.0f)
			);
    
			glm::vec2 m_position;
		    Sprite(glm::vec2 position, std::string name);
		   ~Sprite();

		private:

			Texture2D m_texture;
      		Shader m_shader; 

			int m_renderMode;
        	unsigned int quadVAO;
        	void initRenderData();
		
	};


	class Player : public Sprite {

		public:

			void Update();
			void Animate(string animKey);

			// Player(float x, float y, const char* key[2]) : Sprite(x, y, key)
			// {
			// //	this->SetScale(0.325f, 0.75f);
			// };
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
			
			// TileSprite (
			// 	//std::tuple<int, int> tileType, 
			// 	float posX, 
			// 	float posY, 
			// 	int64_t frameX, 
			// 	int64_t frameY, 
			// 	const char* key[2]
			// ) 
			// :Sprite(posX, posY, key)
			// {
			// 	SetScale(0.1f, 0.1f);

			// 	m_currentFrameX = frameX; 
			// 	m_currentFrameY = frameY;
            //     m_currentFrameWidth = m_tileWidth; 
            //     m_currentFrameHeight = m_tileHeight; 
			// 	m_isAtlas = true;
		        
      
			// }
			~TileSprite() = default;
	};
}