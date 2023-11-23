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
// OVERVIEW: MainWindow.h
// ========
// Class definition for cg template window.
//
// Author: Paulo Pagliosa
// Last revision: 07/11/2022

#ifndef __MainWindow_h
#define __MainWindow_h

#include "graphics/GLWindow.h"
#include "graphics/GLRenderWindow3.h"
#include "graphics/Application.h"


/////////////////////////////////////////////////////////////////////
//
// MainWindow: template main window class
// ==========
using namespace cg;


class MainWindow final: public cg::GLWindow
{
public:
	MainWindow(int width, int height);

private:
	using Base = cg::GLWindow;
  
	// Attribute examples
	GLSL::Program _program;
	GLuint _vao[3]{};
	GLuint _buffers[3][4];

	mat4f _view{ 1.0f };
	mat4f _projection{ 1.0f };

	vec3f _cameraPosition{};
	vec3f _cameraTarget{};
	vec3f _cameraUp{};

	float _fov{};
	float _aspectRatio{};
	float _nearPlane{};
	float _farPlane{};

	vec3f _rotation{};
	vec3f _scale{ 1.0f };
	bool _colorido{};
	vec3f _cor{};

	bool _luzAmbiente{};
	vec3f _ambientLight{};
	bool _luzEspecular{};
	bool _luzDifusa{};
	vec3f _lightColor{};
	vec3f _lightPos{};
	float _ka{};
	float _ks{};
	float _kd{};
	int _n;

	bool _animate{};
	bool _cubo{};
	bool _losangulo{};
	bool _piramide{};

	/////////////////////////////
	int _lastMouseX = 0;
	int _lastMouseY = 0;
	double _yaw = -89.9;   // Rotação em torno do eixo y
	double _pitch = 0.1; // Rotação em torno do eixo x
	double _sensitivity = 0.1;
	float _cameraSpeed = 0.05f;
	vec3f _cameraFront{};

	//////////////////////////////

	void processMouseMovement(double, double);
	void updateCameraDirection();
	void processKeyboardInput();

	// Overridden method examples
	void initialize() override;
	void update() override;
	void render() override;
	void gui() override;
	void terminate() override;

	void reset() {
		_cameraPosition = { 0.0f, 0.0f, 5.0f };
		_cameraTarget = { 0.0f, 0.0f, 4.0f };
		_cameraUp = { 0.0f, 1.0f, 0.0f };

		_fov = 75.0f;
		_aspectRatio = 1.0f;
		_nearPlane = 0.1f;
		_farPlane = 1000.0f;

		_rotation = { 0.0f, 0.0f, 0.0f };
		_colorido = false;
		_cor = { 0.7f, 0.7f, 0.7f };

		_luzAmbiente = true;
		_ambientLight = { 1.0f, 1.0f, 0.0f};
		_luzEspecular = true;
		_luzDifusa = true;
		_lightColor = { 1.0f, 1.0f, 0.0f};
		_lightPos = { 0.0f, 0.0f, 0.0f};
		_ka = 0.23;
		_ks = 0.77;
		_kd = 0.27;
		_n = 30;

		_animate = true;
		_cubo = true;
		_losangulo = true;
		_piramide = true;

		_yaw = -89.9;
		_pitch = 0.1;
		_cameraFront = { 0.0f, 0.0f, -1.0f };
	}

	void DoubleSpacing() {
		ImGui::Spacing();
		ImGui::Spacing();
	}

}; // MainWindow

#endif // __MainWindow_h
