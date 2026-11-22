#include <cmath>
#include <memory>

#include "core/crema.hpp"
#include "core/ecs/components.hpp"
#include "core/engine.hpp"
#include "core/project/scene.hpp"
#include "graphics/geometry/geometry_3d.hpp"
#include "graphics/material/material.hpp"
#include "graphics/model_primitive/model_primitive.hpp"
#include "maths/unit_conversions.hpp"

class HelloCubeScene : public Scene
{
public:
    void onInit() override
    {
        ECS& ecs = getECS();
        Geometry3D* geometry = Geometry3D::get();

        cameraEntity = ecs.createEntity();
        Transform cameraTransform;
        cameraTransform.position = {10.0f, 10.0f, 10.0f};
        cameraTransform.rotation = {-30.0f*DEG_TO_RAD, 45.0f*DEG_TO_RAD, 0.0f};
        ecs.addComponent<Transform>(cameraEntity, cameraTransform);
        Camera camera;
        camera.fov = 45.0f;
        camera.farPlane = 1000.0f;
        ecs.addComponent<Camera>(cameraEntity, camera);

        const Entity cubeEntity = ecs.createEntity();
        ecs.addComponent<Transform>(cubeEntity);
        std::shared_ptr<Material> cubeMaterial = std::make_shared<Material>();
        cubeMaterial->setAlbedo(Colour(220, 80, 75));
        std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>(geometry->cube(2.0f));
        Model cube;
        cube.primitives.emplace_back(cubeMesh, cubeMaterial);
        ecs.addComponent<Model>(cubeEntity, cube);

        const Entity gridEntity = ecs.createEntity();
        ecs.addComponent<Transform>(gridEntity);
        std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
        gridMaterial->setAlbedo(Colour(120, 130, 140));
        Model grid;
        for (int i = -10; i <= 10; ++i) {
            std::shared_ptr<Mesh> xLine = std::make_shared<Mesh>(geometry->line({(float)i, -1.0f, -10.0f}, {(float)i, -1.0f, 10.0f}));
            std::shared_ptr<Mesh> zLine = std::make_shared<Mesh>(geometry->line({-10.0f, -1.0f, (float)i}, {10.0f, -1.0f, (float)i}));
            grid.primitives.emplace_back(xLine, gridMaterial);
            grid.primitives.emplace_back(zLine, gridMaterial);
        }
        ecs.addComponent<Model>(gridEntity, grid);
    }

    void onUpdate() override
    {
        Engine& engine = Engine::get();
        InputSystem& input = engine.inputSystem;
        Transform& cameraTransform = getECS().getComponent<Transform>(cameraEntity);
        const float deltaTime = engine.time.deltaTime;

        const float pitch = cameraTransform.rotation.x;
        const float yaw = cameraTransform.rotation.y;
        const glm::vec3 forward = glm::normalize(glm::vec3(
            -std::sin(yaw) * std::cos(pitch),
            std::sin(pitch),
            -std::cos(yaw) * std::cos(pitch)));
        const glm::vec3 up(0.0f, 1.0f, 0.0f);
        const glm::vec3 right = glm::normalize(glm::cross(forward, up));
        const float movementSpeed = input.isKeyDown(KeyboardKey::KEY_LEFT_SHIFT) ? 10.0f : 5.0f;
        const float movement = movementSpeed * deltaTime;

        if (input.isKeyDown(KeyboardKey::KEY_W)) cameraTransform.position += forward * movement;
        if (input.isKeyDown(KeyboardKey::KEY_A)) cameraTransform.position -= right * movement;
        if (input.isKeyDown(KeyboardKey::KEY_S)) cameraTransform.position -= forward * movement;
        if (input.isKeyDown(KeyboardKey::KEY_D)) cameraTransform.position += right * movement;
        if (input.isKeyDown(KeyboardKey::KEY_SPACE)) cameraTransform.position += up * movement;
        if (input.isKeyDown(KeyboardKey::KEY_LEFT_CONTROL)) cameraTransform.position -= up * movement;

        if (input.isMouseButtonDown(MouseButton::BUTTON_RIGHT)) {
            input.setMouseVisibility(false);
            const glm::vec2 mouseDelta = input.getMousePosition() - input.getPreviousMousePosition();
            constexpr float mouseSensitivity = 0.1f;
            cameraTransform.rotation.x -= mouseDelta.y*mouseSensitivity*DEG_TO_RAD;
            cameraTransform.rotation.y -= mouseDelta.x*mouseSensitivity*DEG_TO_RAD;
        } else {
            input.setMouseVisibility(true);
        }
    }

private:
    Entity cameraEntity = 0;
};

int main()
{
    Window window;
    window.title = "3D Example - Hello Cube";
    window.windowSize = glm::vec2(1280.0f, 720.0f);

    Crema crema(window);
    crema.setTargetFPS(60);
    crema.loadScene(std::make_unique<HelloCubeScene>());
    crema.run();
    return 0;
}
