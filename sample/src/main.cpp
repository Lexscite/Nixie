// This file is part of Voodoo Engine.
//
// Voodoo Engine is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Voodoo Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Voodoo Engine.  If not, see <https://www.gnu.org/licenses/>.

#include <voodoo/engine.h>
#include <voodoo/image_manager.h>
#include <voodoo/mesh_manager.h>

// Components
#include <voodoo/camera.h>
#include <voodoo/mesh_filter.h>
#include <voodoo/renderer.h>
#include <voodoo/text.h>
#include <voodoo/transform.h>

#include "rotatable.h"

std::shared_ptr<voodoo::Scene> CreateScene(voodoo::Engine engine) {
  using namespace std;
  using namespace voodoo;
  auto scene = std::make_shared<Scene>();

  auto default_shader = make_shared<Shader>(
      engine.GetGraphicsAPI()->GetDevice(),
      engine.GetGraphicsAPI()->GetDeviceContext());
  default_shader->Init(
      "../assets/shaders/default_vs.cso",
      "../assets/shaders/default_ps.cso",
      true);

  // Camera
  auto camera = scene->AddGameObject("Camera");
  camera->AddComponent<Camera>();
  camera->GetTransform()->SetPosition(3.75f, 5, 3.75f);
  camera->GetTransform()->SetRotationByDegrees(45, 225, 0);
  scene->SetCamera(camera->GetComponent<Camera>());

  // Cube
  auto cube = scene->AddGameObject("Cube");
  cube->AddComponent<Renderer>();

  auto cube_mesh_filter = cube->AddComponent<MeshFilter>();
  auto cube_mesh = MeshManager::Get().Retrieve("../assets/meshes/cube.mesh");
  cube_mesh_filter->SetMesh(cube_mesh);
  auto cube_texture = make_shared<Texture>(
      engine.GetGraphicsAPI()->GetDevice(),
      ImageManager::Get().Retrieve("../assets/textures/placeholder_blue.jpg"));
  auto cube_material = make_shared<Material>(default_shader, cube_texture);
  cube_mesh_filter->SetMaterial(cube_material);
  cube->GetTransform()->SetPosition(-1, 0, 0);

  // Mario
  auto mario = scene->AddGameObject("Mario");
  mario->AddComponent<Rotatable>();
  mario->AddComponent<Renderer>();

  auto mario_mesh_filter = mario->AddComponent<MeshFilter>();
  auto mario_mesh = MeshManager::Get().Retrieve("../assets/meshes/mario.mesh");
  mario_mesh_filter->SetMesh(mario_mesh);
  auto mario_texture = make_shared<Texture>(
      engine.GetGraphicsAPI()->GetDevice(),
      ImageManager::Get().Retrieve("../assets/textures/checker.jpg"));
  auto mario_material = make_shared<Material>(default_shader, mario_texture);
  mario_mesh_filter->SetMaterial(mario_material);
  mario->GetTransform()->SetPosition(1, 0, 0);

  // Text
  auto text = scene->AddGameObject("Text");
  text->AddComponent<Renderer>();

  auto text_text = text->AddComponent<Text>();
  text_text->SetText("Voodoo");
  text_text->SetFont(make_shared<Font>());

  auto text_shader = make_shared<Shader>(
      engine.GetGraphicsAPI()->GetDevice(),
      engine.GetGraphicsAPI()->GetDeviceContext());
  text_shader->Init(
      "../assets/shaders/font_vs.cso",
      "../assets/shaders/font_ps.cso",
      false);
  auto text_texture = make_shared<Texture>(
      engine.GetGraphicsAPI()->GetDevice(),
      ImageManager::Get().Retrieve("../assets/textures/fonts/consolas.png"));
  auto text_material = make_shared<Material>(text_shader, text_texture);
  text_text->SetMaterial(text_material);
  text->GetTransform()->SetPosition(1.0f, 0, 1.0f);
  text->GetTransform()->SetScale(0.01f);

  return scene;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int cmd_show) {
  using namespace voodoo;
  int exit_code = 1;

  auto engine = Engine();
  if (engine.Init(instance, L"Voodoo Sample")) {
    if (engine.LoadScene(CreateScene(engine))) {
      exit_code = engine.Run();
    }
  }

  engine.Release();

  return exit_code;
}