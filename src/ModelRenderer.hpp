#pragma once
#include <Utilities/Singleton.hpp>
#include <Rendering/Texture.hpp>
#include <Graphics/2D/Sprite.hpp>
#include <mathfu/vector.h>

namespace CrossCraft{
    using namespace Stardust_Celeste;

    class ModelRenderer {
        public:
        ModelRenderer();
        ~ModelRenderer();

        static auto init() -> void;
        static auto get() -> ModelRenderer&;

        auto draw_block_outline() -> void;
        auto draw_break() -> void;
        auto draw_block(uint8_t id, mathfu::Vector<float, 3> position, mathfu::Vector<float, 3> rotation) -> void;
        auto draw_item(uint16_t id, mathfu::Vector<float, 3> position, mathfu::Vector<float, 3> rotation) -> void;

        auto draw_block_hand(uint8_t id, mathfu::Vector<float, 3> position, mathfu::Vector<float, 2> rotation) -> void;
        auto draw_item_hand(uint16_t id, mathfu::Vector<float, 3> position, mathfu::Vector<float, 2> rotation) -> void;

        auto draw_block_isometric(uint8_t id, mathfu::Vector<float, 3> position) -> void;
        auto draw_item_isometric(uint16_t id, mathfu::Vector<float, 3> position) -> void;

        private:
        
        uint32_t terrainTexID;
        uint32_t itemsTexID;

        ScopePtr<Rendering::Mesh<Rendering::Vertex>> blockModels[63];
        ScopePtr<Graphics::G2D::Sprite> itemModels[66];

        ScopePtr<Rendering::Mesh<Rendering::Vertex>> breakModels[11];
    };
}
