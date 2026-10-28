#pragma once
#include "vulkan-lib/Config.h"
#include "stb_image.h"
#include <filesystem>
#include <glm/glm.hpp>

#include "debug_lib/result.hpp"
#include "vulkan-lib/commands.hpp"
#include "vulkan-lib/GraphicsContext.hpp"
#include <variant>
#include <optional>
namespace fs = std::filesystem;
namespace vkl {
    class Image {
    public:
        struct Source{
            std::variant<fs::path, std::pair<size_t, void*>> source;
        };
        struct CreateInfo {
            std::optional<Source> source = std::nullopt;
			glm::uvec2 dimmensions = {1080,1080};
            vk::Format format = vk::Format::eR32G32B32A32Sfloat;
            uint32_t layers_count = 1;
            vk::ImageUsageFlags usage;
            vk::ImageLayout layout;
            vk::AccessFlags access;
            vk::PipelineStageFlags pipeline_stage;
            GraphicsContext::Type context_type;
            vk::DescriptorSetLayout descriptor_layout;
            vk::DescriptorPool descriptor_pool;
        };

        Image() = delete;
        Image(const CreateInfo& info);
        Image(Image&& moved) noexcept = default;
        ~Image() {};

        auto transition_image_layout(vk::ImageLayout new_layout, vk::CommandPool command_pool, vk::PipelineStageFlags dst_stage, vk::AccessFlags dst_access) -> db::Result<db::EmptyOk>;
        auto transition_image_layout_within_command(vk::ImageLayout new_layout, vk::CommandPool command_pool, vk::CommandBuffer command_buffer, vk::PipelineStageFlags dst_stage, vk::AccessFlags dst_access) -> db::Result<db::EmptyOk>;
		auto get_image_view() const -> vk::ImageView { return m_image_view; }
		auto get_image() const -> vk::Image { return m_image; }
		auto get_descriptor_set() const -> vk::DescriptorSet { return m_descriptor_set; }
		auto get_sampler() const -> vk::Sampler { return m_sampler; }
    private:
        glm::ivec2 m_dimmensions;
        int m_channels;
        GraphicsContext& m_graphics_context;

        vk::Image m_image;
        vk::DeviceMemory m_image_memory;
        vk::ImageView m_image_view;
        vk::Sampler m_sampler;
        vk::Format m_format;
        vk::ImageLayout m_image_layout = vk::ImageLayout::eUndefined;
        vk::AccessFlags m_access_mask = {};
        vk::PipelineStageFlags m_pipeline_stage_flags = vk::PipelineStageFlagBits::eTopOfPipe;

        vk::DescriptorSetLayout m_descriptor_layout;
        vk::DescriptorSet m_descriptor_set;
        vk::DescriptorPool m_descriptor_pool;

        vk::CommandBuffer m_command_buffer;
        vk::CommandPool m_command_pool;
        vk::Queue m_queue;
    };
}