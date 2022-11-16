    
    
       #version 330 core
        out vec4 FragColor;
        
        in vec3 ourColor;
        in vec2 TexCoord;

        uniform sampler2D ourTexture;

        void main()
        {
            FragColor = texture(ourTexture, TexCoord);
        }

    // #version 330 core

    // uniform sampler2D texture1;
    // uniform sampler2D texture2;

    // void main()
    // {
    //     FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    // }