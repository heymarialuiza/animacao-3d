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
	GLuint _buffers[3][3];

	mat4f _transf{ 1.0f };
	mat4f _view{ 1.0f };
	mat4f _projection{ 1.0f };

	vec3f _eye{ 0.0f, 0.0f, 5.0f };
	vec3f _center{ 0.0f, 0.0f, 1.0f };
	vec3f _up{0.0f, 1.0f, 0.0f };

	float _fovy{ 25.0 };
	float _aspect{ 1.0 };
	float _zNear{ 100.0 };
	float _zFar{ 1.0 };

	vec3f _rotation{ 0.0f };
	vec3f _scale{ 1.0f };

	vec4f _ambientLight{ 1.0f, 1.0f, 1.0f, 1.0f };
	vec4f _specularLight{ 1.0f, 1.0f, 1.0f, 1.0f };
	vec4f _difuseLight{ 1.0f, 1.0f, 1.0f, 1.0f };

	bool _animate{ false };
	bool _cubo{ true };
	bool _losangulo{ true };
	bool _piramide{ true };

	// Overridden method examples
	void initialize() override;
	void update() override;
	void render() override;
	void gui() override;
	void terminate() override;

	void reset() {
		_eye = { 0.0f, 0.0f, 5.0f };
		_center = { 0.0f, 0.0f, 1.0f };
		_up = { 0.0f, 1.0f, 0.0f };

		_fovy = 25.0;
		_aspect = 1.0;
		_zNear = 100.0;
		_zFar = 1.0;

		_rotation = { 0.0f, 0.0f, 0.0f };

		_ambientLight = { 1.0f, 1.0f, 1.0f, 1.0f };
		_specularLight = { 1.0f, 1.0f, 1.0f, 1.0f };
		_difuseLight = { 1.0f, 1.0f, 1.0f, 1.0f };

		_animate = false;
		_cubo = true;
		_losangulo = true;
		_piramide = true;
	}

	void DoubleSpacing() {
		ImGui::Spacing();
		ImGui::Spacing();
	}

}; // MainWindow

#endif // __MainWindow_h
