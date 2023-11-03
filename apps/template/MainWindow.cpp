//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2022 Paulo Pagliosa.                              |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: MainWindow.cpp
// ========
// Source file for cg template window.
//
// Author: Paulo Pagliosa
// Last revision: 07/11/2022

#include "MainWindow.h"
#define STRINGFY(s) "#version 400\n"#s //é um macro -gera uma string cujo conteudo é o que ta em "" 
static const char* fs=STRINGFY(
  in vec4 color;//entrada do shader -> se ela é entrada, é saída do shader anterior
  out vec4 fragColor;//saída do shader
  void main()
  {
    fragColor=color;
  }
);//shader de fragemento - define a cor do fragmento sendo processado - fragmento é candidato a pixel
struct uint3
{
  unsigned int x;
  unsigned int y;
  unsigned int z;

}; // int3

namespace cubo
{ // begin namespace cube

    static const cg::vec3f translate{ 1.0f, 0.0f, 0.0f };

    static const cg::vec4f v[]
    {
        {-0.5f, -0.5f, -0.5f, 1}, // 0
        {+0.5f, -0.5f, -0.5f, 1}, // 1
        {+0.5f, +0.5f, -0.5f, 1}, // 2
        {-0.5f, +0.5f, -0.5f, 1}, // 3
        {-0.5f, -0.5f, +0.5f, 1}, // 4
        {+0.5f, -0.5f, +0.5f, 1}, // 5
        {+0.5f, +0.5f, +0.5f, 1}, // 6
        {-0.5f, +0.5f, +0.5f, 1}  // 7
    };

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

    static const uint3 t[]
    {
    {0, 3, 1}, {1, 3, 2}, // back
    {4, 5, 7}, {5, 6, 7}, // front
    {0, 4, 3}, {4, 7, 3}, // left
    {1, 2, 5}, {5, 2, 6}, // right
    {0, 1, 4}, {1, 5, 4}, // bottom
    {7, 6, 3}, {6, 2, 3}  // top
    };

} // end namespace cubo

namespace losangulo
{
    static const cg::vec3f translate{ 0.0f, 0.0f, 0.0f };

    // Defina os vértices para o losango 3D
    static const cg::vec4f v[]
    {
        {0.0f, 0.5f, 0.0f, 1},   // Vertice 0 - topo
        {0.5f, 0.0f, 0.0f, 1},   // Vertice 1 - direita
        {0.0f, -0.5f, 0.0f, 1},  // Vertice 2 - fundo
        {-0.5f, 0.0f, 0.0f, 1},  // Vertice 3 - esquerda
        {0.0f, 0.0f, 0.5f, 1},   // Vertice 4 - frente
        {0.0f, 0.0f, -0.5f, 1}   // Vertice 5 - trás
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

    // Defina os índices para criar os triângulos do losango
    static const uint3 t[]
    {
        {0, 1, 4}, {1, 2, 4}, {2, 3, 4}, {3, 0, 4}, // Faces do topo
        {0, 1, 5}, {1, 2, 5}, {2, 3, 5}, {3, 0, 5}  // Faces da base
    };
 
} // end namespace losangulo

namespace piramide
{
    static const cg::vec3f translate{ -1.0f, 0.0f, 0.0f };

    // Defina os vértices para o piramide 3D
    static const cg::vec4f v[]
    {
        {0.0f, -0.802951f, -0.802951f, 1.0f},
        {-0.802951f, -0.802951f, -0.000000f, 1.0f},
        {0.0f, -0.802951f, 0.802951f, 1.0f},    
        {0.8029510000000002f, -0.802951f, 0.000000f, 1.0f},
        {0.0f, 0.802951f, 0.000000f, 1.0f}
    };

    // Defina as cores para cada vértice
    static const cg::Color c[]
    {
        cg::Color{1.0f, 0.0f, 0.0f}, // Red (top vertex)
        cg::Color{1.0f, 1.0f, 0.0f}, // Yellow (vertex 1)
        cg::Color{0.0f, 1.0f, 0.0f}, // Green (vertex 2)
        cg::Color{0.0f, 0.0f, 1.0f}, // Blue (vertex 3)
        cg::Color{1.0f, 0.0f, 1.0f}  // Purple (vertex 4)
    };

    // Defina os índices para criar os triângulos da piramide
    static const uint3 t[]
    {
        {0, 3, 1},
        {0, 1, 4},
        {1, 2, 4},
        {2, 3, 4},
        {3, 0, 4},
        {1, 3, 2}
    };


} // end namespace piramide

//shader de vertice tem q determinar glposition (coordenadas de recorte x,y,z e w)
//rasterizacao determina todos os pixels do triangulo, para cada um deles roda o shader de fragmento
//fragmento pertencente a face da frente vira pixel
//nosso shader de fragmento vai definir a cor e passar p frente
//agora o shader de vertice
static const char* vs=STRINGFY(
  layout(location = 0) in vec4 vertex;
  layout(location = 1) in vec4 vertexColor;
  uniform mat4 transf;
  out vec4 color;

  void main()
  {
    gl_Position = transf * vertex;
    color = vertexColor;
  }
  // uniform vec4 vertices[36]=
  // {
  //   vec4(-0.5f, -0.5f, -0.5f,1),
  //   vec4(-0.5f,0.5f,-0.5f,1),
  //   vec4(0.5f, 0.5f, -0.5f, 1),
  //   vec4(-0.5f, -0.5f, -0.5f,1),
  //   vec4(0.5f, -0.5f, -0.5f, 1),
  //   vec4(0.5f, 0.5f, -0.5f, 1),
  //   //TODO: fazer mais 30 vezes p completar os 36
  // }
  // uniform vec4 colors[36]=
  // {
  //   vec4(0,0,1,1),
  //   vec4(0,1,1,1),
  //   vec4(1, 1, 1, 1),
  //   //continua ate fazer os 36
  // }
  // uniform mat4 transf;

  // out vec4 color;

  // void main()
  // {
  //   gl_Position = transf* vertices[gl_VertexID];
  //   color = colors[gl_VertexID];
  // }
);

/////////////////////////////////////////////////////////////////////
//
// MainWindow implementation
// ==========
MainWindow::MainWindow(int width, int height):
  //Base{"Ds template", width, height}
  Base{"RGB cube", width, height},
  _program{"Cube Drawer"}
{
  // Put your code here. Example:
  /*_lineColor = cg::Color::red;
  _meshColor = cg::Color::blue;
  _radius = 1;
  _speed = 0.01f;*/
}

template <typename T>
inline int
size(int count)
{
  return count * sizeof(T);
}

void
MainWindow::initialize()
{
  // Put your OpenGL initialization code here. Example:
  Base::initialize();
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0f, 1.0f);

  glGenVertexArrays(3, _vao); // (numero de vaos que quero criar, ponteiro que contem os lugares onde vao os vertex array gerados)
  // vao = Dados para o inicio da execução do pipeline
  
  // Gere os buffers para cada objeto e tipo de buffer
  for (int i = 0; i < 3; ++i) {
      glGenBuffers(3, _buffers[i]);
  }

  
  // Adicione os dados do cubo aos buffers
  glBindVertexArray(_vao[0]); 
  glBindBuffer(GL_ARRAY_BUFFER, _buffers[0][0]);
  glBufferData(GL_ARRAY_BUFFER, size<cg::vec4f>(8), cubo::v, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  

  glBindBuffer(GL_ARRAY_BUFFER, _buffers[0][1]);
  glBufferData(GL_ARRAY_BUFFER, size<cg::Color>(8), cubo::c, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[0][2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size<uint3>(12), cubo::t, GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(2);

  // Adicione os dados do losango aos buffers
  glBindVertexArray(_vao[1]);
  glBindBuffer(GL_ARRAY_BUFFER, _buffers[1][0]);
  glBufferData(GL_ARRAY_BUFFER, size<cg::vec4f>(6), losangulo::v, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, _buffers[1][1]);
  glBufferData(GL_ARRAY_BUFFER, size<cg::Color>(6), losangulo::c, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[1][2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size<uint3>(8), losangulo::t, GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(2);
  
  // Adicione os dados da piramide aos buffers
  glBindVertexArray(_vao[2]);
  glBindBuffer(GL_ARRAY_BUFFER, _buffers[2][0]);
  glBufferData(GL_ARRAY_BUFFER, size<cg::vec4f>(5), piramide::v, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, _buffers[2][1]);
  glBufferData(GL_ARRAY_BUFFER, size<cg::Color>(5), piramide::c, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[2][2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size<uint3>(6), piramide::t, GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(2);

  _program.setShaders(vs, fs).use();//vs, fs -> shader de vertice, shader de fragmento
}

void
MainWindow::update()
{
  // Put your scene update code here. Example:
  /*static float time{};

  if (_animate)
    _radius = 1 + cosf(_speed * (time += deltaTime()) * 0.5f);*/
    //_transf.setRotation(cg::vec3f{ 0, 1, 1 }, 100 * glfwGetTime(), cg::vec3f{ 0, 0, 0 });
    //_transf.setRotation(_rotation, _angle, cg::vec3f{ 0, 0, 0 });
    //_program.setUniformMat4("transf", _transf);


}

void
//MainWindow::renderScene()
MainWindow::render()
{
    using namespace cg;
    // Put your scene rendering code here. 
    clear(cg::Color::darkGray);//limpa a tela e coloca darkgray de cor de fundo
    //_program.setUniformMat4("transf", _transf);

    if (_cubo)
    {
        _transf = _transf.TRS(cubo::translate, _rotation, _scale);
        _program.setUniformMat4("transf", _transf);

        glBindVertexArray(_vao[0]);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);  // Renderize o cubo
    }

    if (_losangulo)
    {
        _transf = _transf.TRS(losangulo::translate, _rotation, _scale);
        _program.setUniformMat4("transf", _transf);

        glBindVertexArray(_vao[1]);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);  // Renderize o losangulo
    }

    if (_piramide)
    {

        _transf = _transf.TRS(piramide::translate, _rotation, _scale);
        _program.setUniformMat4("transf", _transf);

        glBindVertexArray(_vao[2]);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);  // Renderize a piramide
    }

    //glDrawElements(GL_LINE_LOOP, 18, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0,36);
    //funcao de desenho da openGl( , 0 ->contador offset - pula tantos e vai até->,numero de vertices) -cada triangulo fornece 3 vertices, vai repetir vertice msm
    //36 pq sao 12 triangulos p fazer um cubo
};

/*bool
MainWindow::keyInputEvent(int key, int action, int mods)
{
  // Put your key event handler code here. Example:
  if (action != GLFW_RELEASE && mods == GLFW_MOD_ALT)
    switch (key)
    {
      case GLFW_KEY_P:
        _animate ^= true;
        return true;
    }
  return Base::keyInputEvent(key, action, mods);
}*/

void
MainWindow::gui()
{
  using namespace cg;
  // Put your gui code here. Example:
  //ImGui::SetNextWindowSize({360, 180});//-> tamanho da janela 360*180
  //ImGui::Begin("Controls");

    ImGui::SetNextWindowSize(ImVec2(240, 240), ImGuiCond_FirstUseEver);
    ImGui::Begin("Inspector");
    ImGui::DragFloat3("Rotation", (float*)&_rotation, 1.0f, 0, 0, "%.2f");
    //ImGui::DragFloat3("Translate", (float*)&_translate, 0.1f, 0, 0, "%.2f");
    //ImGui::SliderFloat("Angle", &_angle, -180.0f, 180.0f);
    ImGui::Checkbox("Cubo", &_cubo);
    ImGui::Checkbox("Losangulo", &_losangulo);
    ImGui::Checkbox("Piramide", &_piramide);
  
  //_transf = mat4f::rotation(quatf::eulerAngles(_rotation), vec3f::null());
  //_program.setUniformMat4("transf", _transf);

  //update();
  //ImGui::End();
  ImGui::End();

   //ImGui::Begin("Template GUI");
   //ImGui::ColorEdit3("Line Color", (float*)&_lineColor);
   //ImGui::ColorEdit3("Mesh Color", (float*)&_meshColor);
   //ImGui::Separator();
   //ImGui::Checkbox("Animate", &_animate);
   //ImGui::SliderFloat("Speed", &_speed, 0.001f, 0.01f);
   //ImGui::Checkbox("Show Ground", &_showGround);
   //ImGui::Separator();
   //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
   //deltaTime(),
   //ImGui::GetIO().Framerate);
   //ImGui::End();//->abre janela que nao tem nada, so tem titulo
}

void
MainWindow::terminate()
{
  glDeleteVertexArrays(1, _vao);
}
