#define STRINGFY(s) "#version 400\n"#s
static const char* fs = STRINGFY(
in vec4 color;      //entrada do shader
in vec4 normal;
in vec3 fragPos;
out vec4 fragColor; //sa�da do shader

uniform vec3 ambientLight;
uniform vec3 lightColor;
uniform vec3 lightPos;// = vec3(1, 1, 1);
uniform int n;
uniform vec3 camPos;
uniform bool luzAmbiente;
uniform bool luzEspecular;
uniform bool luzDifusa;
uniform float ka;
uniform float ks;
uniform float kd;
uniform bool colorido;
uniform vec3 cor;


void main()
{
    vec4 ambiente = vec4(0, 0, 0, 1);
    vec4 difusa = vec4(0, 0, 0, 1);
    vec4 especular = vec4(0, 0, 0, 1);

    //Ambiente
    if (luzAmbiente) {
        vec4 ambientColor = vec4(ambientLight, 1.0);
        ambiente = ka * ambientColor;
    }

    //Difusa
    vec4 difuseColor = vec4(lightColor, 1.0);
    vec4 ligthDir = normalize(vec4(lightPos - fragPos, 1.0));
    float cosTeta = clamp(dot(normalize(normal), ligthDir), 0., 1.);

    if (luzDifusa) {
        difusa = difuseColor * kd * cosTeta;
    }

    //Especular
    
    vec4 specularColor = vec4(lightColor, 1.0);
    vec4 reflex = 2 * normalize(normal) * cosTeta - normalize(vec4(lightPos, 1.0));
    float cosAlfa = clamp(dot(reflex, vec4(camPos, 1.0)),0.,1.);

    if (luzEspecular) {
        especular = specularColor*ks*pow(cosAlfa,n);
    }

    float dist = length(lightPos - fragPos);
    float atenuacao = 1.0 / (1 + 0.09 * dist + 0.032 * dist * dist);

    //Phong
    if (colorido)
        fragColor = (ambiente + (difusa + especular) * atenuacao) * color;
    else
        fragColor = (ambiente + (difusa + especular) * atenuacao) * vec4(cor,1.0);
}
);

static const char* vs = STRINGFY(
layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec3 vertexNormal;
out vec4 color;
out vec4 normal;
out vec3 fragPos;

uniform mat4 view; // Matriz de visualiza��o
uniform mat4 projection; // Matriz de proje��o
uniform vec3 rotation;
uniform vec3 translate;

mat4 TR(vec3 rotation, vec3 translate) {
    float cosX = cos(radians(rotation.x));
    float sinX = sin(radians(rotation.x));
    float cosY = cos(radians(rotation.y));
    float sinY = sin(radians(rotation.y));
    float cosZ = cos(radians(rotation.z));
    float sinZ = sin(radians(rotation.z));

    mat4 rotationX = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cosX, -sinX, 0.0,
        0.0, sinX, cosX, 0.0,
        0.0, 0.0, 0.0, 1.0);

    mat4 rotationY = mat4(
        cosY, 0.0, sinY, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sinY, 0.0, cosY, 0.0,
        0.0, 0.0, 0.0, 1.0);

    mat4 rotationZ = mat4(
        cosZ, -sinZ, 0.0, 0.0,
        sinZ, cosZ, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0);

    mat4 mTranslate = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        translate.x, translate.y, translate.z, 1.0);

    return mTranslate * rotationZ * rotationY * rotationX;
}

void main()
{
    mat4 rotateTranslate = TR(rotation, translate);

    gl_Position = projection * view * rotateTranslate * vertex;

    color = vertexColor;
    
    normal = transpose(inverse(view * rotateTranslate)) * vec4(vertexNormal, 1.0);//vec4(rotateTranslate * vec4(vertexNormal, 1.0));

    vec4 transform = rotateTranslate * vertex;
    fragPos = vec3(transform);
}
);