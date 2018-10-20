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

// Components
#include <voodoo/camera.h>
#include <voodoo/model.h>
#include <voodoo/renderer.h>
#include <voodoo/text.h>
#include <voodoo/transform.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {
  using namespace voodoo;
  int exit_code = 1;

  auto engine = Engine();
  if (engine.Init(hInstance, L"Voodoo Sample")) {
    auto scene = std::make_shared<Scene>();

    auto camera = scene->AddGameObject("Camera");
    camera->AddComponent<Camera>();
    camera->GetTransform()->SetPosition(3.75f, 5, 3.75f);
    camera->GetTransform()->SetRotationByDegrees(45, 225, 0);
    scene->SetCamera(camera->GetComponent<Camera>());

    auto cube = scene->AddGameObject("Cube");
    cube->AddComponent<Renderer>(
        engine.GetGraphicsAPI()->GetDevice(),
        engine.GetGraphicsAPI()->GetDeviceContext());
    cube->AddComponent<Model>(
        "../assets/meshes/cube.mesh",
        "../assets/shaders/default_vs.cso",
        "../assets/shaders/default_ps.cso",
        "../assets/textures/placeholder.png");
    cube->GetTransform()->SetPosition(0, 0, 0);

    auto text = scene->AddGameObject("Text");
    text->AddComponent<Renderer>(
        engine.GetGraphicsAPI()->GetDevice(),
        engine.GetGraphicsAPI()->GetDeviceContext());
    text->AddComponent<Text>(
        "Hello World",
        "../assets/shaders/font_vs.cso",
        "../assets/shaders/font_ps.cso",
        "../assets/textures/fonts/consolas.png");
    text->GetTransform()->SetPosition(1, 1, 1);
    text->GetTransform()->SetScale(0.005f);

    if (engine.LoadScene(scene))
      exit_code = engine.Run();
  }

  engine.Release();

  return exit_code;
}