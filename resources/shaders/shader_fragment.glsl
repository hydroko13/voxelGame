#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D tex1;
uniform float drawBlack;

void main() {

  
    vec4 fColor = texture(tex1, TexCoord);


    FragColor = vec4(fColor.rgb * (1.0f - drawBlack), (fColor.a * (1.0f - drawBlack)) + drawBlack);
    

    


} 

