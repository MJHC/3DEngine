//FRAGMENT
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D image;

void main()
{
    //FragColor = texture(face, TexCoord);
    FragColor = texture(image, TexCoord);
    //FragColor =     vec4(1.0, 0.5, 0.31, 1.0);
}