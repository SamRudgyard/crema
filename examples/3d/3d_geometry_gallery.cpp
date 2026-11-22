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

class GeometryGalleryScene : public Scene
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

        const Entity capsuleEntity = ecs.createEntity();
        Transform capsuleTransform;
        capsuleTransform.position = {5.0f, 0.0f, -10.0f};
        ecs.addComponent<Transform>(capsuleEntity, capsuleTransform);
        std::shared_ptr<Material> capsuleMaterial = std::make_shared<Material>();
        capsuleMaterial->setAlbedo(Colour(158, 1, 66));
        std::shared_ptr<Mesh> capsuleMesh = std::make_shared<Mesh>(geometry->capsule(1.0f, 3.0f, 16, 16));
        Model capsule;
        capsule.primitives.emplace_back(capsuleMesh, capsuleMaterial);
        ecs.addComponent<Model>(capsuleEntity, capsule);

        const Entity coneEntity = ecs.createEntity();
        Transform coneTransform;
        coneTransform.position = {5.0f, 0.0f, -5.0f};
        ecs.addComponent<Transform>(coneEntity, coneTransform);
        std::shared_ptr<Material> coneMaterial = std::make_shared<Material>();
        coneMaterial->setAlbedo(Colour(213, 62, 79));
        std::shared_ptr<Mesh> coneMesh = std::make_shared<Mesh>(geometry->cone(1.0f, 3.0f, 32));
        Model cone;
        cone.primitives.emplace_back(coneMesh, coneMaterial);
        ecs.addComponent<Model>(coneEntity, cone);

        const Entity cylinderEntity = ecs.createEntity();
        Transform cylinderTransform;
        cylinderTransform.position = {5.0f, 0.0f, 0.0f};
        ecs.addComponent<Transform>(cylinderEntity, cylinderTransform);
        std::shared_ptr<Material> cylinderMaterial = std::make_shared<Material>();
        cylinderMaterial->setAlbedo(Colour(244, 109, 67));
        std::shared_ptr<Mesh> cylinderMesh = std::make_shared<Mesh>(geometry->cylinder(1.0f, 1.0f, 3.0f, 32));
        Model cylinder;
        cylinder.primitives.emplace_back(cylinderMesh, cylinderMaterial);
        ecs.addComponent<Model>(cylinderEntity, cylinder);

        const Entity cubeEntity = ecs.createEntity();
        Transform cubeTransform;
        cubeTransform.position = {5.0f, 0.0f, 5.0f};
        ecs.addComponent<Transform>(cubeEntity, cubeTransform);
        std::shared_ptr<Material> cubeMaterial = std::make_shared<Material>();
        cubeMaterial->setAlbedo(Colour(253, 174, 97));
        std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>(geometry->cube(2.0f));
        Model cube;
        cube.primitives.emplace_back(cubeMesh, cubeMaterial);
        ecs.addComponent<Model>(cubeEntity, cube);

        const Entity cuboidEntity = ecs.createEntity();
        Transform cuboidTransform;
        cuboidTransform.position = {5.0f, 0.0f, 10.0f};
        ecs.addComponent<Transform>(cuboidEntity, cuboidTransform);
        std::shared_ptr<Material> cuboidMaterial = std::make_shared<Material>();
        cuboidMaterial->setAlbedo(Colour(254, 224, 140));
        std::shared_ptr<Mesh> cuboidMesh = std::make_shared<Mesh>(geometry->cuboid(1.0f, 2.0f, 2.5f));
        Model cuboid;
        cuboid.primitives.emplace_back(cuboidMesh, cuboidMaterial);
        ecs.addComponent<Model>(cuboidEntity, cuboid);

        const Entity lineEntity = ecs.createEntity();
        Transform lineTransform;
        lineTransform.position = {-5.0f, 0.0f, -10.0f};
        ecs.addComponent<Transform>(lineEntity, lineTransform);
        std::shared_ptr<Material> lineMaterial = std::make_shared<Material>();
        lineMaterial->setAlbedo(Colour(230, 245, 152));
        std::shared_ptr<Mesh> lineMesh = std::make_shared<Mesh>(geometry->line({-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}));
        Model line;
        line.primitives.emplace_back(lineMesh, lineMaterial);
        ecs.addComponent<Model>(lineEntity, line);

        const Entity planeEntity = ecs.createEntity();
        Transform planeTransform;
        planeTransform.position = {-5.0f, 0.0f, -5.0f};
        ecs.addComponent<Transform>(planeEntity, planeTransform);
        std::shared_ptr<Material> planeMaterial = std::make_shared<Material>();
        planeMaterial->setAlbedo(Colour(171, 221, 164));
        std::shared_ptr<Mesh> planeMesh = std::make_shared<Mesh>(geometry->plane(2.0f, 2.0f));
        Model plane;
        plane.primitives.emplace_back(planeMesh, planeMaterial);
        ecs.addComponent<Model>(planeEntity, plane);

        const Entity pyramidEntity = ecs.createEntity();
        Transform pyramidTransform;
        pyramidTransform.position = {-5.0f, 0.0f, 0.0f};
        ecs.addComponent<Transform>(pyramidEntity, pyramidTransform);
        std::shared_ptr<Material> pyramidMaterial = std::make_shared<Material>();
        pyramidMaterial->setAlbedo(Colour(102, 194, 165));
        std::shared_ptr<Mesh> pyramidMesh = std::make_shared<Mesh>(geometry->pyramidSquare(2.0f, 2.0f));
        Model pyramid;
        pyramid.primitives.emplace_back(pyramidMesh, pyramidMaterial);
        ecs.addComponent<Model>(pyramidEntity, pyramid);

        const Entity sphereUVEntity = ecs.createEntity();
        Transform sphereUVTransform;
        sphereUVTransform.position = {-5.0f, 0.0f, 5.0f};
        ecs.addComponent<Transform>(sphereUVEntity, sphereUVTransform);
        std::shared_ptr<Material> sphereUVMaterial = std::make_shared<Material>();
        sphereUVMaterial->setAlbedo(Colour(50, 136, 189));
        std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>(geometry->sphereUV(1.0f, 32, 8));
        Model sphereUV;
        sphereUV.primitives.emplace_back(sphereMesh, sphereUVMaterial);
        ecs.addComponent<Model>(sphereUVEntity, sphereUV);

        const Entity icosphereEntity = ecs.createEntity();
        Transform icosphereTransform;
        icosphereTransform.position = {-5.0f, 0.0f, 10.0f};
        ecs.addComponent<Transform>(icosphereEntity, icosphereTransform);
        std::shared_ptr<Material> icosphereMaterial = std::make_shared<Material>();
        icosphereMaterial->setAlbedo(Colour(94, 79, 162));
        std::shared_ptr<Mesh> icosphereMesh = std::make_shared<Mesh>(geometry->sphereIcosphere(1.0f, 1));
        Model icosphere;
        icosphere.primitives.emplace_back(icosphereMesh, icosphereMaterial);
        ecs.addComponent<Model>(icosphereEntity, icosphere);
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
    window.title = "3D Example - Geometry Gallery";
    window.windowSize = glm::vec2(1280.0f, 720.0f);

    Crema crema(window);
    crema.setTargetFPS(60);
    crema.loadScene(std::make_unique<GeometryGalleryScene>());
    crema.run();
    return 0;
}
