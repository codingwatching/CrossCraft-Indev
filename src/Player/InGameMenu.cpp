#include <Player/InGameMenu.hpp>
#include <Utilities/Input.hpp>
#include <World/World.hpp>
#include <GLFW/glfw3.h>

namespace GI {
    extern GLFWwindow *window;
}

namespace CrossCraft {
    using namespace Stardust_Celeste;
    using namespace Stardust_Celeste::Utilities;

    InGameMenu::InGameMenu() {
        open = false;

        background_rectangle = create_refptr<Rendering::Primitive::Rectangle>(
                Rendering::Rectangle{{0, 0}, {480, 272}},
                Rendering::Color{0, 0, 0, 128}, 4);

        font_render = create_refptr<FontRender>();

        button_disabled = create_refptr<Graphics::G2D::Sprite>(
                ResourcePack::get().get_texture("gui_common"),
                Rendering::Rectangle{{-100, -10}, {200, 20}}, Rendering::Rectangle{{0.0f, 46.0f / 256.0f}, {200.0f / 256.0f, 20.0f / 256.0f}});

        button_unselected = create_refptr<Graphics::G2D::Sprite>(
                ResourcePack::get().get_texture("gui_common"),
                Rendering::Rectangle{{-100, -10}, {200, 20}}, Rendering::Rectangle{{0.0f, 66.0f / 256.0f}, {200.0f / 256.0f, 20.0f / 256.0f}});

        button_selected = create_refptr<Graphics::G2D::Sprite>(
                ResourcePack::get().get_texture("gui_common"),
                Rendering::Rectangle{{-100, -10}, {200, 20}}, Rendering::Rectangle{{0.0f, 86.0f / 256.0f}, {200.0f / 256.0f, 20.0f / 256.0f}});
    }

    InGameMenu::~InGameMenu() {

    }

    void InGameMenu::update(double dt) {

    }

    InGameMenu* internal_state;

    auto InGameMenu::init() -> void {
        internal_state = new InGameMenu();
    }

    auto InGameMenu::get() -> InGameMenu& {
        return *internal_state;
    }


    auto InGameMenu::left_click_command(std::any p) -> void {
        auto cX = Input::get_axis("Mouse", "X");
        auto cY = Input::get_axis("Mouse", "Y");
        auto mousePos = Math::Vector2<float>(cX, cY);

        Math::Vector2<float> windowSize(480, 272);
        auto mouseVec = mousePos * windowSize;
        mouseVec.y = windowSize.y - mouseVec.y;

        SC_APP_INFO("Mouse: {0}, {1}", mouseVec.x, mouseVec.y);

        if(mouseVec.x >= 190 && mouseVec.x <= 290 && mouseVec.y >= 130 && mouseVec.y <= 150) {
            get().toggle();
        } else if (mouseVec.x >= 190 && mouseVec.x <= 290 && mouseVec.y >= 106 && mouseVec.y <= 126) {
            SC_APP_INFO("Unimplemented");
        } else if (mouseVec.x >= 190 && mouseVec.x <= 290 && mouseVec.y >= 82 && mouseVec.y <= 102) {
            World::save(p);
        }
    }

    auto InGameMenu::right_click_command(std::any p) -> void {

    }

    auto InGameMenu::draw_button(Math::Vector2<float> mousePos, Math::Vector2<float> pos, std::string text, bool disabled) -> void {
        Math::Vector2<float> windowSize(480, 272);
        auto mouseVec = mousePos * windowSize;
        mouseVec.y = windowSize.y - mouseVec.y;

        Rendering::RenderContext::get().matrix_clear();
        Rendering::RenderContext::get().matrix_translate(Math::Vector3<float>(pos.x, pos.y, 6));

        if(disabled) {
            button_disabled->draw();
            pos.y -= 4;
            font_render->draw_text_aligned(CC_TEXT_COLOR_GRAY, CC_TEXT_ALIGN_CENTER, text, pos, 7.0f);
        } else {
            if(mouseVec.x >= pos.x - 100 && mouseVec.x <= pos.x + 100 && mouseVec.y >= pos.y - 10 && mouseVec.y <= pos.y + 10) {
                button_selected->draw();
                pos.y -= 4;
                font_render->draw_text_aligned(CC_TEXT_COLOR_SELECT, CC_TEXT_ALIGN_CENTER, text, pos, 7.0f);
            } else {
                button_unselected->draw();
                pos.y -= 4;
                font_render->draw_text_aligned(CC_TEXT_COLOR_WHITE, CC_TEXT_ALIGN_CENTER, text, pos, 7.0f);
            }
        }

    }

    void InGameMenu::draw(double dt) {
        if(!open)
            return;

        auto cX = Input::get_axis("Mouse", "X");
        auto cY = Input::get_axis("Mouse", "Y");
        auto mouseVec = Math::Vector2<float>(cX, cY);

        background_rectangle->draw();

        font_render->clear();
        font_render->draw_text_aligned(CC_TEXT_COLOR_WHITE, CC_TEXT_ALIGN_CENTER, "Game Menu", Math::Vector2<float>(240, 216), 5.0f);

        draw_button(mouseVec, Math::Vector2<float>(240, 140), "Back to Game", false);
        draw_button(mouseVec, Math::Vector2<float>(240, 116), "Options", true);
        draw_button(mouseVec, Math::Vector2<float>(240, 92), "Save Game", false);

        font_render->build();
        Rendering::RenderContext::get().matrix_clear();
        font_render->draw();
    }

    void InGameMenu::toggle() {
        open = !open;

        if(open) {
            glfwSetInputMode(GI::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            Input::set_differential_mode("Mouse", false);
        } else {
            Input::set_cursor_center();
            glfwSetInputMode(GI::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            Input::set_differential_mode("Mouse", true);
        }
    }
}