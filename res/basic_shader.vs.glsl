#version 120

attribute vec3 position;
attribute vec2 texture_coordinate;//Lees texture coordinate in die vertex shader in
//nou wil ons tussen vertices interpoleer en vir fragment shader stuur
attribute vec3 normal;

//varying vars word gedeel tussen shaders en word geinterpoleer tussen vertices van 3hoek
varying vec2 texture_coordinate0;
varying vec3 normal0;

uniform mat4 transform_matrix;//variable set deur cpu en get deur gpu
//kry matriks vanaf cpu en pas hom toe op elke posisie

void main()
{
    gl_Position = transform_matrix * vec4(position, 1.0);//die 1 stel voor hoe groot die translasie impak is, 1 is normaal, 0 is niks, 2 is baie
    texture_coordinate0 = texture_coordinate; //Nou het fragment shader toegang tot texture_coordinate
    normal0 = (transform_matrix * vec4(normal, 0.0)).xyz;//lig moenie transleer nie
    //.xyz return xyz vec3 tipe
}