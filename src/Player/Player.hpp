#pragma once
#include <Stardust-Celeste.hpp>
#include <World/World.hpp>
#include <Rendering/Camera.hpp>
#include <Graphics/2D/Sprite.hpp>
#include <Player/Hud.hpp>
#include <mathfu/vector.h>

namespace CrossCraft {

    using namespace Stardust_Celeste;

    class Player;
    struct HealthUpdate {
        Player* player;
        uint16_t health;
    };

    class Player {
    public:
        Player();
        ~Player();

        void update(double dt);
        void draw(double dt);

        static auto move_forward(std::any p) -> void;
        static auto move_backward(std::any p) -> void;
        static auto move_left(std::any p) -> void;
        static auto move_right(std::any p) -> void;

        static auto jump(std::any p) -> void;

        static auto break_block(std::any p) -> void;
        static auto place_block(std::any p) -> void;

        static auto handle_health_update(std::any p) -> void;

        mathfu::Vector<float, 3> position;
        mathfu::Vector<float, 3> velocity;
        mathfu::Vector<float, 2> rotation;
    private:
        static mathfu::Vector<float, 3> size;

        float horizInput;
        float vertInput;

        bool on_ground;
        bool in_water;
        bool water_face;

        uint16_t health;
        uint16_t air;

        void do_rotate(double dt);
        void do_move(double dt);
        void calculate_velocity(double dt);
        void test_collide(double dt);
        void perform_checks();

        bool safety_check_place(mathfu::Vector<int, 3> position);

        Rendering::Camera camera;
        ScopePtr<Graphics::G2D::Sprite> water_sprite, crosshair;
        ScopePtr<HUD> hud;
    };

}