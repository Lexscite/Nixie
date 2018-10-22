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

std::shared_ptr<voodoo::Scene> CreateScene(voodoo::Engine engine) {
  using namespace voodoo;
  auto scene = std::make_shared<Scene>();

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

  auto cube_shader = std::make_shared<Shader>(
      engine.GetGraphicsAPI()->GetDevice(),
      engine.GetGraphicsAPI()->GetDeviceContext());
  cube_shader->Init(
      "../assets/shaders/default_vs.cso",
      "../assets/shaders/default_ps.cso",
      true);
  auto cube_texture = std::make_shared<Texture>(
      engine.GetGraphicsAPI()->GetDevice(),
      ImageManager::Get().Retrieve("../assets/textures/placeholder.png"));
  auto cube_material = std::make_shared<Material>(cube_shader, cube_texture);
  cube_mesh_filter->SetMaterial(cube_material);
  cube->GetTransform()->SetPosition(0, 0, 0);

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