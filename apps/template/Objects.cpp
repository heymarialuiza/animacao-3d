#include <graph/SceneObjectBuilder.h>
#include <graph/SceneObjectBuilder.h>

using namespace cg;

struct uint3
{
    unsigned int x;
    unsigned int y;
    unsigned int z;

}; // int3

namespace cubo
{ // begin namespace cubo

    static cg::vec3f translate{ 1.5f, -1.0f, 0.0f };

    static const int nun_vertices = 8;
    static const int nun_faces = 12;

    // Defina os vértices para o cubo
    static const cg::vec4f v[]
    {
        { -1.000f, -1.000f, 1.000f, 1.0f},
        { 1.000f, -1.000f, 1.000f, 1.0f},
        { -1.000f, 1.000f, 1.000f, 1.0f},
        { 1.000f, 1.000f, 1.000f, 1.0f},
        { -1.000f, 1.000f, -1.000f, 1.0f},
        { 1.000f, 1.000f, -1.000f, 1.0f},
        { -1.000f, -1.000f, -1.000f, 1.0f},
        { 1.000f, -1.000f, -1.000f, 1.0f}
    };

    // Defina as cores para cada vértice
    static const cg::Color c[]
    {
        cg::Color{0.0f, 0.0f, 0.0f}, // 0
        cg::Color{1.0f, 0.0f, 0.0f}, // 1
        cg::Color{1.0f, 1.0f, 0.0f}, // 2
        cg::Color{0.0f, 1.0f, 0.0f}, // 3
        cg::Color{0.0f, 0.0f, 1.0f}, // 4
        cg::Color{1.0f, 0.0f, 1.0f}, // 5
        cg::Color{1.0f, 1.0f, 1.0f}, // 6
        cg::Color{0.0f, 1.0f, 1.0f}  // 7
    };

    static const cg::vec3f n[]
    {
        { -0.400f, -0.400f, 0.200f },
        { 0.250f, -0.250f, 0.500f },
        { -0.250f, 0.250f, 0.500f },
        { 0.400f, 0.400f, 0.200f },
        { -0.400f, 0.400f, -0.200f },
        { 0.250f, 0.250f, -0.500f },
        { -0.250f, -0.250f, -0.500f },
        { 0.400f, -0.400f, -0.200f }
    };

    // Defina os índices para criar os triângulos do cubo
    static const uint3 t[]
    {
        { 0, 1, 2 },
        { 2, 1, 3 },
        { 2, 3, 4 },
        { 4, 3, 5 },
        { 4, 5, 6 },
        { 6, 5, 7 },
        { 6, 7, 0 },
        { 0, 7, 1 },
        { 1, 7, 3 },
        { 3, 7, 5 },
        { 6, 0, 4 },
        { 4, 0, 2 }
    };

} // end namespace cubo

namespace losangulo
{ // begin namespace losangulo

    static cg::vec3f translate{ 0.0f, 1.0f, 0.0f };

    static const int nun_vertices = 6;
    static const int nun_faces = 8;

    // Defina os vértices para o losango 3D
    static const cg::vec4f v[]
    {
        { 0.000f, 0.000f, 1.000f, 1.0f},
        { 1.000f, 0.000f, 0.000f, 1.0f},
        { 0.000f, 1.000f, 0.000f, 1.0f},
        { -1.000f, 0.000f, 0.000f, 1.0f},
        { 0.000f, -1.000f, 0.000f, 1.0f},
        { 0.000f, 0.000f, -1.000f, 1.0f}
    };

    // Defina as cores para cada vértice
    static const cg::Color c[]
    {
        cg::Color{1.0f, 0.0f, 0.0f},  // Cor 0 - vermelho
        cg::Color{0.0f, 1.0f, 0.0f},  // Cor 1 - verde
        cg::Color{0.0f, 0.0f, 1.0f},  // Cor 2 - azul
        cg::Color{1.0f, 1.0f, 0.0f},  // Cor 3 - amarelo
        cg::Color{1.0f, 0.0f, 1.0f},  // Cor 4 - magenta
        cg::Color{0.0f, 1.0f, 1.0f}   // Cor 5 - ciano
    };

    static const cg::vec3f n[]
    {
        { 0.000f, 0.000f, 0.577f },
        { 0.577f, 0.000f, 0.000f },
        { 0.000f, 0.577f, 0.000f },
        { -0.577f, 0.000f, 0.000f },
        { 0.000f, -0.577f, 0.000f },
        { 0.000f, 0.000f, -0.577f }
    };

    // Defina os índices para criar os triângulos do losango
    static const uint3 t[]
    {
        { 1, 2, 0 },
        { 2, 3, 0 },
        { 3, 4, 0 },
        { 0, 4, 1 },
        { 5, 2, 1 },
        { 5, 3, 2 },
        { 5, 4, 3 },
        { 5, 1, 4 }
    };

} // end namespace losangulo

namespace piramide
{ //begin namespace piramide
    static cg::vec3f translate{ -1.5f, -1.0f, 0.0f };

    static const int nun_vertices = 5;
    static const int nun_faces = 6;

    // Defina os vértices para o piramide 3D
    static const cg::vec4f v[]
    {
        { 0.000f, -1.000f, -1.000f, 1.0f},
        { -1.000f, -1.000f, -0.000f, 1.0f},
        { -0.000f, -1.000f, 1.000f, 1.0f},
        { 1.000f, -1.000f, 0.000f, 1.0f},
        { 0.000f, 1.000f, 0.000f, 1.0f}
    };

    // Defina as cores para cada vértice
    static const cg::Color c[]
    {
        cg::Color{1.0f, 0.0f, 0.0f},  // Cor 0 - vermelho
        cg::Color{0.0f, 1.0f, 0.0f},  // Cor 1 - verde
        cg::Color{0.0f, 0.0f, 1.0f},  // Cor 2 - azul
        cg::Color{1.0f, 1.0f, 0.0f},  // Cor 3 - amarelo
        cg::Color{1.0f, 0.0f, 1.0f},  // Cor 4 - magenta
    };

    static const cg::vec3f n[]
    {
        { 0.000f, -0.111f, -0.444f },
        { -0.333f, -0.333f, 0.000f },
        { 0.000f, -0.111f, 0.444f },
        { 0.333f, -0.333f, 0.000f },
        { 0.000f, 0.333f, 0.000f }
    };

    // Defina os índices para criar os triângulos da piramide
    static const uint3 t[]
    {
        { 0, 3, 1 },
        { 1, 3, 2 },
        { 0, 1, 4 },
        { 1, 2, 4 },
        { 2, 3, 4 },
        { 3, 0, 4 }
    };
} // end namespace piramide