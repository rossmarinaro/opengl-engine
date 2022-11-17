// #include "../headers/entity.h"

// void Sprite::Render()
// { 
//     if (m_texture1 != NULL)
//     {

//         // glBindTexture(GL_TEXTURE_2D, m_texture1);
//         // m_shader->use();
//         // glBindVertexArray(m_VAO);
//         // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//         if (m_isSpritesheet == true)
//         {
//             if (m_currentFrame > m_frames)
//                 m_currentFrame = 0;
//             m_currentFrameX = m_resourceData["frames"][m_currentFrame]["x"]; 
//         }

//         if (m_isAtlas == true || m_isSpritesheet == true)
//             _SetSubTexture();

//         // else 
//         //     glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_width, m_height, 0, m_renderMode, GL_UNSIGNED_BYTE, m_image1);

       

            
      
//        //render surface as open gl texture (works)
    
//         glBegin(GL_QUADS);
//             glTexCoord2f(0, 1); glVertex3f(m_posX, m_posY, 0);
//             glTexCoord2f(1, 1); glVertex3f(m_posX + m_srcWidth * m_scaleX, m_posY, 0);
//             glTexCoord2f(1, 0); glVertex3f(m_posX + m_srcWidth * m_scaleX, m_posY + m_srcHeight * m_scaleY, 0);
//             glTexCoord2f(0, 0); glVertex3f(m_posX, m_posY + m_srcHeight * m_scaleY, 0); 
//         glEnd();




//         //--------

//         // glActiveTexture(GL_TEXTURE0);
//         // glBindTexture(GL_TEXTURE_2D, m_texture1);
//         // glActiveTexture(GL_TEXTURE1);
//         // glBindTexture(GL_TEXTURE_2D, m_texture2);

//         // m_shader->use(); // don't forget to activate the shader before setting uniforms!  

//         // glUniform1i(glGetUniformLocation(m_shader->ID, "texture1"), 0); // set it manually
//         // m_shader->setInt("texture2", 1); // or with shader class
//         // glBindVertexArray(m_VAO);
//         // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
//         // while(...) 
//         // {
//         //     [...]
//         // }

            

 

//     }

// }


// Image::Image(float x, float y, const char* key[2])
// {

//     // m_shader = new Shader("assets/glsl/vert.vs", "assets/glsl/frag.fs"); 

//     // // set up vertex data (and buffer(s)) and configure vertex attributes
//     // // ------------------------------------------------------------------
//     // float vertices[] = {
//     //     //positions          // colors           // texture coords
//     //     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
//     //     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
//     //    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
//     //    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // top left 
//     // };

//     // unsigned int indices[] = {  
//     //     0, 1, 3, // first triangle
//     //     1, 2, 3  // second triangle
//     // };

//     // glGenVertexArrays(1, &m_VAO);
//     // glGenBuffers(1, &m_VBO);
//     // glGenBuffers(1, &m_EBO);

//     // glBindVertexArray(m_VAO);

//     // glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//     // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//     // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     // // position attribute

//     // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//     // glEnableVertexAttribArray(0);

//     // // color attribute

//     // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//     // glEnableVertexAttribArray(1);

//     // // texture coord attribute

//     // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//     // glEnableVertexAttribArray(2);

//     //---texture
    
//     unsigned int texture1;
//     glGenTextures(1, /* &id */&texture1);
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, /* id */ texture1);

//     // glBindVertexArray(m_VAO);
//     // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//     // stbi_set_flip_vertically_on_load(true);  

//     int ok, w, h, channels;

//     ok = stbi_info(key[1], &w, &h, &channels);

//     m_width = w,
//     m_height = h;

//     m_renderMode = GL_RGB;
    
//     if (channels == 4) 
//     { 
//         m_renderMode = GL_RGBA; 
//         Log::write("rgba enabled"); 
//     }


//     //---------------- set the texture wrapping parameters

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//     // //--------------- set texture filtering parameters

//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     const char* spritesheet = Assets::Spritesheets::GetResource(key[0]); 

//     if (spritesheet != 0) //if spritesheet
//     {
//         std::ifstream data(spritesheet);
//         m_resourceData = json::parse(data);
//         m_frames = m_resourceData["frames"].size() - 1;
//         m_currentFrame = 0;
//         m_currentFrameY = m_resourceData["frames"][m_currentFrame]["y"];
//         m_currentFrameWidth = m_resourceData["frames"][m_currentFrame]["w"];
//         m_currentFrameHeight = m_resourceData["frames"][m_currentFrame]["h"]; 
//         m_isSpritesheet = true;
//     }  

//     m_image1 = stbi_load(key[1], &m_width, &m_height, &channels, 0);  

//     if (!m_image1) 
//         Log::write("Error loading sprite."); 
//     else 
//     { 

//     //render image as opengl texture

//         glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_width, m_height, 0, m_renderMode, GL_UNSIGNED_BYTE, m_image1);
//         glGenerateMipmap(GL_TEXTURE_2D);

//     //Get image dimensions / position

//         SetPosition(-0.5, -0.5);
 
//         m_texture1 = texture1; //id
       
//         Log::write("Sprite instantiated");

//         stbi_image_free(m_image1);
//     }


//     //---tmp
//     // unsigned int  texture2;
//     // glGenTextures(1, &texture2);

//     // glActiveTexture(GL_TEXTURE1);
//     // glBindTexture(GL_TEXTURE_2D, texture2);
 
//     // glBindVertexArray(m_VAO);
//     // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//     // stbi_set_flip_vertically_on_load(true);  


//     // ok = stbi_info("assets/images/swanky_velvet.png", &w, &h, &channels);


//     // //glBindTexture(GL_TEXTURE_2D, texture1);

//     // m_renderMode = GL_RGB;
    
//     // if (channels == 4) 
//     // { 
//     //     m_renderMode = GL_RGBA; 
//     //     Log::write("rgba enabled"); 
//     // }

//     // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     // // set the texture wrapping parameters

//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//     // // set texture filtering parameters

//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


//     // unsigned char* image2 = stbi_load("assets/images/swanky_velvet.png", &m_width, &m_height, &channels, 0);  

//     // if (!image2) 
//     //     Log::write("Error loading sprite."); 
//     // else 
//     // { 

//     // //render image as opengl texture

//     //     glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_width, m_height, 0, m_renderMode, GL_UNSIGNED_BYTE, image2);
//     //     glGenerateMipmap(GL_TEXTURE_2D);

//     //     m_texture2 = texture2;
       
       
//     //     Log::write("Sprite instantiated");


//     //     stbi_image_free(image2);
//     // }



// }


// Image::~Image()
// {

//     Log::write("Sprite Destroyed");
//     glDeleteVertexArrays(1, &m_VAO);
//     glDeleteBuffers(1, &m_VBO);
//     glDeleteBuffers(1, &m_EBO);
//     delete m_shader;
// }