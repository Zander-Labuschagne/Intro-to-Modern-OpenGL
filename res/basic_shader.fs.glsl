#version 120 //GLSL shader language

varying vec2 texture_coordinate0; //variable is shared tussen shaders
varying vec3 normal0;

uniform sampler2D diffuse; //variable waar CPU en GPU toegang het -> CPU skryf, GPU lees| variable is van sampler2D tipe wat texture data is

void main()
{
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); //Pixel sal altyd rooi wees

    //Watter unit, van waar sample ons? x en y coordinates(OpenGL doen koordinate vanaf 0 tot 1:. resolution independant)
    gl_FragColor = texture2D(diffuse, texture_coordinate0); //Die lees een pixel by posisie (0.2, 0.2) vanaf texture en vul die 3hoek daarmee
    //So wat ons eintlik wil doen is texture mapping -> lees pixels vanaf texture posisie afhangend van wat ons posisie is op mesh
    //So wat ons wil se is ons soek aparte texture posisie vir elke vertex en dan moet hy maar tussen hulle interpoleer om die regte texture posisie te kry vir die regte posisie op die mesh

    //wat ons wil doen is die lighting toe pas,:. vat reeds bestaande texture en vermenigvuldig dit met lighting
    //fl_FragColor = gl_FragColor * 1.0; //full on bright is dalk een en half is 0.5 ens.
    vec3 light_direction = vec3(0, 0, 1); //Die kamera maak lig
    gl_FragColor = clamp(gl_FragColor * dot(-light_direction, normal0), 0.0, 1.0); //hoek tussen light direction en normal | punt produk | lambertian lighting vat die negatiewe hoek want -> simulate light reflection
    //Ons clamp want die waarde van die lighting calculation moet binne perke wees anders sien ons weird goed
}