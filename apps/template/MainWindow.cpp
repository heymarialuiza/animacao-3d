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
#include <graph/SceneObjectBuilder.h>
#include <graph/SceneObjectBuilder.h>
#include "Objects.cpp"
#include "Fragments.cpp"

/////////////////////////////////////////////////////////////////////
// Função para processar a movimentação do mouse
void
MainWindow::processMouseMovement(double mouseX, double mouseY)
{
    double xOffset = (mouseX - _lastMouseX) * _sensitivity;
    double yOffset = (_lastMouseY - mouseY) * _sensitivity;

    _yaw += xOffset;
    _pitch += yOffset;


    // Limitar o pitch para evitar inversões da câmera
    _pitch = std::max(std::min(_pitch, 90.0), -90.0);

    _lastMouseX = mouseX;
    _lastMouseY = mouseY;
}

// Função para atualizar a direção da câmera com base nos ângulos yaw e pitch
void
MainWindow::updateCameraDirection()
{
    _cameraFront.x = cos(math::toRadians(_yaw)) * cos(math::toRadians(_pitch));
    _cameraFront.y = sin(math::toRadians(_pitch));
    _cameraFront.z = sin(math::toRadians(_yaw)) * cos(math::toRadians(_pitch));
    _cameraFront = _cameraFront.normalize();
    _cameraTarget = _cameraPosition + _cameraFront;
}

// Função para atualizar a posição da camera com uso do WASDQE
void 
MainWindow::processKeyboardInput()
{
    if (isKeyPressed(GLFW_KEY_W)){
        _cameraPosition += _cameraSpeed * _cameraFront;
    }
    if (isKeyPressed(GLFW_KEY_S)){
        _cameraPosition -= _cameraSpeed * _cameraFront;
    }
    if (isKeyPressed(GLFW_KEY_A)){
        _cameraPosition -= _cameraFront.cross(_cameraUp).normalize() * _cameraSpeed;
    }
    if (isKeyPressed(GLFW_KEY_D)){
        _cameraPosition += _cameraFront.cross(_cameraUp).normalize() * _cameraSpeed;
    }
    if (isKeyPressed(GLFW_KEY_Q)){
        _cameraPosition -= _cameraSpeed * _cameraUp;
    }
    if (isKeyPressed(GLFW_KEY_E)){
        _cameraPosition += _cameraSpeed * _cameraUp;
    }
}


/////////////////////////////////////////////////////////////////////
//
// MainWindow implementation
// ==========
MainWindow::MainWindow(int width, int height):
  Base{"RGB cube", width, height},
  _program{"Cube Drawer"}
{
    reset();
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
    // Put your OpenGL initialization code here. Example
    Base::initialize();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);

    glGenVertexArrays(3, _vao);
  
    // Gere os buffers para cada objeto e tipo de buffer
    for (int i = 0; i < 3; ++i) {
        glGenBuffers(4, _buffers[i]);
    }
  
    // Adicione os dados do cubo aos buffers
    glBindVertexArray(_vao[0]); 
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[0][0]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::vec4f>(cubo::nun_vertices), cubo::v, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[0][1]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::Color>(cubo::nun_vertices), cubo::c, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[0][2]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::vec3f>(cubo::nun_vertices), cubo::n, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[0][3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size<uint3>(cubo::nun_faces), cubo::t, GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);

    // Adicione os dados do losango aos buffers
    glBindVertexArray(_vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[1][0]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::vec4f>(losangulo::nun_vertices), losangulo::v, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[1][1]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::Color>(losangulo::nun_vertices), losangulo::c, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[1][2]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::vec3f>(losangulo::nun_vertices), losangulo::n, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[1][3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size<uint3>(losangulo::nun_faces), losangulo::t, GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
  
    // Adicione os dados da piramide aos buffers
    glBindVertexArray(_vao[2]);
    glBindBuffer(GL_ARRAY_BUFFER, _buffers[2][0]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::vec4f>(piramide::nun_vertices), piramide::v, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[2][1]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::Color>(piramide::nun_vertices), piramide::c, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _buffers[2][2]);
    glBufferData(GL_ARRAY_BUFFER, size<cg::vec3f>(piramide::nun_vertices), piramide::n, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[2][3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size<uint3>(piramide::nun_faces), piramide::t, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);

    _program.setShaders(vs, fs).use();//vs, fs -> shader de vertice, shader de fragmento
}

void
MainWindow::update()
{ }

void
MainWindow::render()
{
    using namespace cg;
    // Put your scene rendering code here. 
    clear(cg::Color::black);//limpa a tela e coloca darkgray de cor de fundo

    processKeyboardInput();
    
    if (isKeyPressed(GLFW_KEY_LEFT_ALT)) {
        double MouseX, MouseY;
        Base::cursorPosition(MouseX, MouseY);
        processMouseMovement(MouseX, MouseY);
    }
    Base::cursorPosition(_lastMouseX, _lastMouseY);
    updateCameraDirection();

    //_program.setUniform("angulo", _angle);


    // Atualizar a matriz de visualização ou a direção da câmera
    _view = mat4f::lookAt(_cameraPosition, _cameraTarget, _cameraUp);
    _program.setUniformMat4("view", _view);
    _program.setUniformVec3("camPos", _cameraPosition);

    _projection = cg::mat4f::perspective(_fov, _aspectRatio, _nearPlane, _farPlane);
    _program.setUniformMat4("projection", _projection);
    
    _program.setUniformVec4("ambientLight", _ambientLight);
    _program.setUniformVec4("lightColor", _lightColor);
    _program.setUniformVec3("lightPos", _lightPos);
    _program.setUniform("n", _n);

    if (_animate)
        _rotation = _rotation + vec3f{ 0.0f, 0.1f, 0.0f };

    _program.setUniformVec3("rotation", _rotation);

    if (_cubo)
    {
        //_transf = _transf.TRS(cubo::translate, _rotation, _scale);
        _program.setUniformVec3("translate", cubo::translate);

        glBindVertexArray(_vao[0]);
        if (_line)
            glDrawElements(GL_LINE_STRIP, cubo::nun_faces * 3, GL_UNSIGNED_INT, 0);  // Renderize a piramide
        else
            glDrawElements(GL_TRIANGLES, cubo::nun_faces * 3, GL_UNSIGNED_INT, 0);  // Renderize o cubo
    }

    if (_losangulo)
    {
        //_transf = _transf.TRS(losangulo::translate, _rotation, _scale);
        //_program.setUniformMat4("transf", _transf);
        _program.setUniformVec3("translate", losangulo::translate);

        glBindVertexArray(_vao[1]);
        if (_line)
            glDrawElements(GL_LINE_STRIP, losangulo::nun_faces * 3, GL_UNSIGNED_INT, 0);  // Renderize a piramide
        else
            glDrawElements(GL_TRIANGLES, losangulo::nun_faces * 3, GL_UNSIGNED_INT, 0);  // Renderize o losangulo
    }

    if (_piramide)
    {
        //_transf = _transf.TRS(piramide::translate, _rotation, _scale);
        //_program.setUniformMat4("transf", _transf);
        _program.setUniformVec3("translate", piramide::translate);

        glBindVertexArray(_vao[2]);
        if(_line)
            glDrawElements(GL_LINE_STRIP, piramide::nun_faces * 3, GL_UNSIGNED_INT, 0);  // Renderize a piramide
        else
            glDrawElements(GL_TRIANGLES, piramide::nun_faces * 3, GL_UNSIGNED_INT, 0);  // Renderize a piramide
    }
};

void
MainWindow::gui()
{
    using namespace cg;
    ImGui::SetNextWindowSize(ImVec2(240, 240), ImGuiCond_FirstUseEver);
    ImGui::Begin("Inspector");

    if (ImGui::Button("RESET")) {
        reset();
    }
    DoubleSpacing();
    ImGui::Checkbox("Animate", &_animate);
    DoubleSpacing();

    if (!_animate) {
        ImGui::Separator();
        ImGui::Text("Controles dos Objetos");
        DoubleSpacing();
        //ImGui::DragFloat3("Rotação", (float*)&_rotation, 1.0f, 0, 0, "%.2f");
        ImGui::DragFloat3("Rotação", (float*)&_rotation, 0.1f, -5, 5, "%.2f");
        DoubleSpacing();
        ImGui::DragFloat3("CUBO", (float*)&cubo::translate, 1.0f, 0, 0, "%.2f");
        ImGui::DragFloat3("LOSANGULO", (float*)&losangulo::translate, 1.0f, 0, 0, "%.2f");
        ImGui::DragFloat3("PIRAMIDE", (float*)&piramide::translate, 1.0f, 0, 0, "%.2f");
        DoubleSpacing();
        ImGui::Checkbox("Cubo", &_cubo);
        ImGui::Checkbox("Losangulo", &_losangulo);
        ImGui::Checkbox("Piramide", &_piramide);
        ImGui::Checkbox("LINE", &_line);
    }

    ImGui::Separator();
    ImGui::Text("Controles das Luz");
    DoubleSpacing();
    ImGui::DragFloat4("Luz Ambiente", (float*)&_ambientLight, 0.01f, 0, 1, "%.2f");
    ImGui::DragFloat4("Cor da Luz", (float*)&_lightColor, 0.01f, 0, 1, "%.2f");
    ImGui::DragFloat3("Posição da Luz", (float*)&_lightPos, 1.0f, -100, 100, "%.2f");
    ImGui::DragInt("N", &_n, 1, 0, 100);

    ImGui::Separator();
    ImGui::Text("Controles da Câmera");
    DoubleSpacing();
    ImGui::DragFloat3("Posição", (float*)&_cameraPosition, 1.0f, 0, 0, "%.2f");
    ImGui::DragFloat3("Alvo", (float*)&_cameraTarget, 1.0f, 0, 0, "%.2f");
    ImGui::DragFloat3("CameraFront", (float*)&_cameraFront, 1.0f, 0, 0, "%.2f");
    ImGui::DragFloat3("CameraUP", (float*)&_cameraUp, 1.0f, 0, 0, "%.2f");
    DoubleSpacing();
    ImGui::DragFloat("Fov", (float*)&_fov, 1.0f, 0, 0, "%.2f");
    ImGui::DragFloat("Aspect", (float*)&_aspectRatio, 1.0f, 0, 0, "%.2f");
    ImGui::DragFloat("NearPlane", (float*)&_nearPlane, 1.0f, 0, 0, "%.2f");
    ImGui::DragFloat("FarPlane", (float*)&_farPlane, 1.0f, 0, 0, "%.2f");
    ImGui::End();
}

void
MainWindow::terminate()
{
    glDeleteVertexArrays(1, _vao);
}
